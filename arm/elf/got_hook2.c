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
ͨ������program header table����got��������Ӧ�ڶ�̬
���Ӷ�.got.plt��DT_PLTGOT��ָ�򴦣�����ÿ�����Ϣ�Ǻ�
GOT���еı����Ӧ�ģ���ˣ��ڽ�����̬���Ӷ�ʱ��
��Ҫ����DT_JMPREL��DT_SYMTAB��ǰ��ָ����ÿһ�������
�����ƫ�Ƶ�ַ�������Ϣ��������GOT����ƫ�ƣ�
����ΪGOT��
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

    // ��ʽ���ַ����õ� "/proc/pid/maps"
    if(pid < 0){
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }else{
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }

    // ���ļ�/proc/pid/maps����ȡָ��pid���̼��ص��ڴ�ģ����Ϣ
    fp = fopen(filename, "r");
    if(fp != NULL){
        // ÿ��һ�У���ȡ�ļ� /proc/pid/maps������
        while(fgets(line, sizeof(line), fp)){
            // ����ָ����soģ��
            if(strstr(line, module_name)){
                // �ָ��ַ���
                pch = strtok(line, "-");
                // �ַ���ת������
                addr = strtoul(pch, NULL, 16);

                // �����ڴ��ַ�Ĵ���
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

    // ��ȡĿ��pid������"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"ģ��ļ��ص�ַ
    void* base_addr = get_module_base(getpid(), LIB_PATH);
    LOGD("[+] libvivosgmain.so address = %p \n", base_addr);

    // ���汻Hook��Ŀ�꺯����ԭʼ���õ�ַ
    old_fopen = fopen;
    LOGD("[+] Orig fopen = %p\n", old_fopen);

    //����program header tableʵ�ʵ�ַ
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


    //����program header table��ptype����PT_DYNAMIC��Ϊdynameic����ȡ��p_offset
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
    //��������Ҫhook�ĵ��뺯����������fopen��ʾ��
    for(i=0;i < pltRelSz / 8;i++)
    {
        int number = (rel_table[i].r_info >> 8) & 0xffffff;
        Elf32_Sym* symTableIndex = (Elf32_Sym*)(number*16 + symTabOff + base_addr);
        char* funcName = (char*)(symTableIndex->st_name + strTabOff + base_addr);
        //LOGD("[+] Func Name : %s",funcName);
        if(memcmp(funcName, "fopen", 5) == 0)
        {
            // ��ȡ��ǰ�ڴ��ҳ�Ĵ�С
            uint32_t page_size = getpagesize();
            // ��ȡ�ڴ��ҳ����ʼ��ַ����Ҫ�ڴ���룩
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