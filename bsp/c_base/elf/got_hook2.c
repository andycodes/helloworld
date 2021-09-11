#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LOG_TAG "INJECT"
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)

/*
通过分析program header table查找got表。导入表对应在动态
链接段.got.plt（DT_PLTGOT）指向处，但是每项的信息是和
GOT表中的表项对应的，因此，在解析动态链接段时，
需要解析DT_JMPREL、DT_SYMTAB，前者指向了每一个导入表
表项的偏移地址和相关信息，包括在GOT表中偏移，
后者为GOT表。
*/

//FILE *fopen(const char *filename, const char *modes)
FILE* (*old_fopen)(const char *filename, const char *modes);
FILE* new_fopen(const char *filename, const char *modes){
    LOGD("[+] New call fopen.\n");
    if(old_fopen == -1){
        LOGD("error.\n");
    }
    return old_fopen(filename, modes);
}

void* get_module_base(pid_t pid, const char* module_name){
    FILE* fp;
    long addr = 0;
    char* pch;
    char filename[32];
    char line[1024];

    // 格式化字符串得到 "/proc/pid/maps"
    if(pid < 0){
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }else{
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }

    // 打开文件/proc/pid/maps，获取指定pid进程加载的内存模块信息
    fp = fopen(filename, "r");
    if(fp != NULL){
        // 每次一行，读取文件 /proc/pid/maps中内容
        while(fgets(line, sizeof(line), fp)){
            // 查找指定的so模块
            if(strstr(line, module_name)){
                // 分割字符串
                pch = strtok(line, "-");
                // 字符串转长整形
                addr = strtoul(pch, NULL, 16);

                // 特殊内存地址的处理
                if(addr == 0x8000){
                    addr = 0;
                }
                break;
            }
        }
    }
    fclose(fp);
    return (void*)addr;
}

#define LIB_PATH "/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"
int hook_fopen(){

    // 获取目标pid进程中"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"模块的加载地址
    void* base_addr = get_module_base(getpid(), LIB_PATH);
    LOGD("[+] libvivosgmain.so address = %p \n", base_addr);

    // 保存被Hook的目标函数的原始调用地址
    old_fopen = fopen;
    LOGD("[+] Orig fopen = %p\n", old_fopen);

    //计算program header table实际地址
    Elf32_Ehdr *header = (Elf32_Ehdr*)(base_addr);
    if (memcmp(header->e_ident, "\177ELF", 4) != 0) {
        return 0;
    }

    Elf32_Phdr* phdr_table = (Elf32_Phdr*)(base_addr + header->e_phoff);
    if (phdr_table == 0)
    {
        LOGD("[+] phdr_table address : 0");
        return 0;
    }
    size_t phdr_count = header->e_phnum;
    LOGD("[+] phdr_count : %d", phdr_count);


    //遍历program header table，ptype等于PT_DYNAMIC即为dynameic，获取到p_offset
    unsigned long dynamicAddr = 0;
    unsigned int dynamicSize = 0;
    int j = 0;
    for (j = 0; j < phdr_count; j++)
    {
        if (phdr_table[j].p_type == PT_DYNAMIC)
        {
            dynamicAddr = phdr_table[j].p_vaddr + base_addr;
            dynamicSize = phdr_table[j].p_memsz;
            break;
        }
    }
    LOGD("[+] Dynamic Addr : %x",dynamicAddr);
    LOGD("[+] Dynamic Size : %x",dynamicSize);

/*
typedef struct dynamic {
    Elf32_Sword d_tag;
    union {
    Elf32_Sword d_val;
    Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;
*/
    Elf32_Dyn* dynamic_table = (Elf32_Dyn*)(dynamicAddr);
    unsigned long jmpRelOff = 0;
    unsigned long strTabOff = 0;
    unsigned long pltRelSz = 0;
    unsigned long symTabOff = 0;
    int i;
    for(i=0;i < dynamicSize / 8;i ++)
    {
        int val = dynamic_table[i].d_un.d_val;
        if (dynamic_table[i].d_tag == DT_JMPREL)
        {
            jmpRelOff = val;
        }
        if (dynamic_table[i].d_tag == DT_STRTAB)
        {
            strTabOff = val;
        }
        if (dynamic_table[i].d_tag == DT_PLTRELSZ)
        {
            pltRelSz = val;
        }
        if (dynamic_table[i].d_tag == DT_SYMTAB)
        {
            symTabOff = val;
        }
    }

    Elf32_Rel* rel_table = (Elf32_Rel*)(jmpRelOff + base_addr);
    LOGD("[+] jmpRelOff : %x",jmpRelOff);
    LOGD("[+] strTabOff : %x",strTabOff);
    LOGD("[+] symTabOff : %x",symTabOff);
    //遍历查找要hook的导入函数，这里以fopen做示例
    for(i=0;i < pltRelSz / 8;i++)
    {
        int number = (rel_table[i].r_info >> 8) & 0xffffff;
        Elf32_Sym* symTableIndex = (Elf32_Sym*)(number*16 + symTabOff + base_addr);
        char* funcName = (char*)(symTableIndex->st_name + strTabOff + base_addr);
        //LOGD("[+] Func Name : %s",funcName);
        if(memcmp(funcName, "fopen", 5) == 0)
        {
            // 获取当前内存分页的大小
            uint32_t page_size = getpagesize();
            // 获取内存分页的起始地址（需要内存对齐）
            uint32_t mem_page_start = (uint32_t)(((Elf32_Addr)rel_table[i].r_offset + base_addr)) & (~(page_size - 1));
            LOGD("[+] mem_page_start = %lx, page size = %lx\n", mem_page_start, page_size);
            //void* pstart = (void*)MEM_PAGE_START(((Elf32_Addr)rel_table[i].r_offset + base_addr));
            mprotect((uint32_t)mem_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
            LOGD("[+] r_off : %x",rel_table[i].r_offset + base_addr);
            LOGD("[+] new_fopen : %x",new_fopen);
            *(unsigned int*)(rel_table[i].r_offset + base_addr) = new_fopen;
        }
    }

    return 0;
}

int hook_entry(char* a){
    LOGD("[+] Start hooking.\n");
    hook_fopen();
    return 0;
}