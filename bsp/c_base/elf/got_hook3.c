#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <elf.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <sys/mman.h>

#define LOG_TAG "INJECT"
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)


int (*old_check_signatures)();
int new_check_signatures(){
    LOGD("[+] New call check_signatures.\n");
    if(old_check_signatures == -1){
        LOGD("error.\n");
    }
    return old_check_signatures();
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
int hook_check_signatures(){

    // ��ȡĿ��pid������"/data/app-lib/com.bbk.appstore-2/libvivosgmain.so"ģ��ļ��ص�ַ
    void* base_addr = get_module_base(getpid(), LIB_PATH);
    LOGD("[+] libvivosgmain.so address = %p \n", base_addr);

    //����program header tableʵ�ʵ�ַ
    Elf32_Ehdr *header = (Elf32_Ehdr*)(base_addr);
    if (memcmp(header->e_ident, "\177ELF", 4) != 0) {
        return 0;
    }

    void* handle = dlopen("/data/app-lib/com.bbk.appstore-2/libvivosgmain.so", RTLD_LAZY);
    //��ȡԭ������ַ
    void* funcaddr = dlsym(handle, "check_signatures");
    LOGD("[+] libvivosgmain.so check_signatures address = %p \n", (int)funcaddr);

    int phOffset = header->e_phoff;
    int phNumber = header->e_phnum;
    int phPhyAddr = phOffset + base_addr;
    LOGD("[+] phOffset  : %x", phOffset);
    LOGD("[+] phNumber  : %x", phNumber);
    LOGD("[+] phPhyAddr : %x", phPhyAddr);
    int i = 0;

    Elf32_Phdr* phdr_table = (Elf32_Phdr*)(base_addr + phOffset);
    if (phdr_table == 0)
    {
        LOGD("[+] phdr_table address : 0");
        return 0;
    }

    /*
    // Program header for ELF32.
    struct Elf32_Phdr {
      Elf32_Word p_type;   // Type of segment
      Elf32_Off  p_offset; // File offset where segment is located, in bytes
      Elf32_Addr p_vaddr;  // Virtual address of beginning of segment
      Elf32_Addr p_paddr;  // Physical address of beginning of segment (OS-specific)
      Elf32_Word p_filesz; // Num. of bytes in file image of segment (may be zero)
      Elf32_Word p_memsz;  // Num. of bytes in mem image of segment (may be zero)
      Elf32_Word p_flags;  // Segment flags
      Elf32_Word p_align;  // Segment alignment constraint
    };
    */
    //����program header table��ptype����2��Ϊdynamic����ȡ��p_offset
    unsigned long dynamicAddr = 0;
    unsigned int dynamicSize = 0;

    for (i = 0; i < phNumber; i++)
    {
        if (phdr_table[i].p_type == PT_DYNAMIC)
        {
            dynamicAddr = phdr_table[i].p_vaddr + base_addr;
            dynamicSize = phdr_table[i].p_memsz;
            break;
        }
    }
    LOGD("[+] Dynamic Addr : %x", dynamicAddr);
    LOGD("[+] Dynamic Size : %x", dynamicSize);

    /*
    typedef struct dynamic {
        Elf32_Sword d_tag;
        union {
        Elf32_Sword d_val;
        Elf32_Addr d_ptr;
        } d_un;
    } Elf32_Dyn;
    */
    //��ʼ����dynamic�νṹ��d_tagΪ6��ΪGOT���ַ
    int symbolTableAddr = 0;
    Elf32_Dyn* dynamic_table = (Elf32_Dyn*)(dynamicAddr);

    for(i=0; i < dynamicSize / 8; i++)
    {
        int val = dynamic_table[i].d_un.d_val;
        if (dynamic_table[i].d_tag == 6)
        {
            symbolTableAddr = val + base_addr;
            break;
        }
    }
    LOGD("Symbol Table Addr : %x", symbolTableAddr);

    /*
    typedef struct elf32_sym {
        Elf32_Word st_name;
        Elf32_Addr st_value;
        Elf32_Word st_size;
        unsigned char st_info;
        unsigned char st_other;
        Elf32_Half st_shndx;
    } Elf32_Sym;
    */
    //����GOT������GOT���б�ǵ�check_signatures������ַ���滻Ϊnew_check_signatures�ĵ�ַ
    int giveValuePtr = 0;
    int fakeValuePtr = 0;
    int newFunc = (int)new_check_signatures - (int)base_addr;
    int oldFunc = (int)funcaddr - (int)base_addr;
    i = 0;
    LOGD("[+] newFunc Addr : %x", newFunc);
    LOGD("[+] oldFunc Addr : %x", oldFunc);

    // ��ȡ��ǰ�ڴ��ҳ�Ĵ�С
    uint32_t page_size = getpagesize();
    // ��ȡ�ڴ��ҳ����ʼ��ַ����Ҫ�ڴ���룩
    uint32_t mem_page_start = (uint32_t)(((Elf32_Addr)symbolTableAddr)) & (~(page_size - 1));
    LOGD("[+] mem_page_start = %lx, page size = %lx\n", mem_page_start, page_size);
    mprotect((uint32_t)mem_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
    Elf32_Sym* symTab = (Elf32_Sym*)(symbolTableAddr);
    while(1)
    {
        //LOGD("[+] func Addr : %x", symTab[i].st_value);
        if(symTab[i].st_value == oldFunc)
        {
            //st_value �������ƫ�Ƶ�ַ
            symTab[i].st_value = newFunc;
            LOGD("[+] New Give func Addr : %x", symTab[i].st_value);
            break;
        }
        i++;
    }
    mprotect((uint32_t)mem_page_start, page_size, PROT_READ | PROT_EXEC);

    return 0;
}

int hook_entry(char* a){
    LOGD("[+] Start hooking.\n");
    hook_check_signatures();
    return 0;
}