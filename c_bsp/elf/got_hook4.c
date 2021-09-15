#include <jni.h>
#include <dlfcn.h>
#include <elf.h>
#include <android/log.h> 
#include <sys/mman.h>
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "ror_got_hook", __VA_ARGS__))

#define MEM_PAGE_SIZE 4096
#define MEM_PAGE_MASK (MEM_PAGE_SIZE-1)
#define MEM_PAGE_START(x)  ((x) & ~MEM_PAGE_MASK)
#define MEM_PAGE_END(x)    MEM_PAGE_START((x) + (MEM_PAGE_SIZE-1))
#define ElfW(type) Elf32_ ## type


JNIEXPORT jint JNICALL ReturnGiveValue(int val)
{
    return val;
}

JNIEXPORT jint JNICALL ReturnFakeValue(int val)
{
    return val * 100;
}


int __attribute__((constructor))  gothook()
{
    //获取动态库基值
    void* testlib = dlopen("/data/data/com.test.test/libtest.so",RTLD_LAZY);
    int nBase = *(int*)(testlib+0x8C);
    LOGD("nBase : %x",nBase);

    //计算program header table实际地址
    ElfW(Ehdr) *header = (ElfW(Ehdr)*)(nBase);
    if (memcmp(header->e_ident, "\177ELF", 4) != 0) {
        return 0;
    }

    int phOffset = header->e_phoff;
    int phNumber = header->e_phnum;
    int phPhyAddr = phOffset + nBase;
    LOGD("phOffset  : %x",phOffset);
    LOGD("phNumber  : %x",phNumber);
    LOGD("phPhyAddr : %x",phPhyAddr);
    int i = 0;

    ElfW(Phdr)* phdr_table = (ElfW(Phdr)*)(nBase + phOffset);
    if (phdr_table == 0)
    {
        LOGD("phdr_table address : 0");
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
    //遍历program header table，ptype等于2即为dynameic，获取到p_offset
    unsigned long dynamicAddr = 0;
    unsigned int dynamicSize = 0;
    for (int i = 0; i < phNumber; i++)
    {
        if (phdr_table[i].p_type == PT_DYNAMIC)
        {
            dynamicAddr = phdr_table[i].p_vaddr + nBase;
            dynamicSize = phdr_table[i].p_memsz;
            break;
        }
    }
    LOGD("Dynamic Addr : %x",dynamicAddr);
    LOGD("Dynamic Size : %x",dynamicSize);

/*
typedef struct dynamic {
    Elf32_Sword d_tag;
    union {
    Elf32_Sword d_val;
    Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;
*/
    //开始遍历dynamic段结构，d_tag为6即为GOT表地址
    int systemTableAddr = 0;
    ElfW(Dyn)* dynamic_table = (ElfW(Dyn)*)(dynamicAddr);

    for(i=0;i < dynamicSize / 8;i ++)
    {
        int val = dynamic_table[i].d_un.d_val;
        if (dynamic_table[i].d_tag == 6)
        {
            systemTableAddr = val + nBase;
            break;
        }
    }
    LOGD("System Table Addr : %x",systemTableAddr);

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
    //遍历GOT表，查找GOT表中标记的ReturnGiveValue函数地址，替换为ReturnFakeValue的地址
    int giveValuePtr = 0;
    int fakeValuePtr = 0;
    int fakeFunc = (int)ReturnFakeValue - nBase;
    int giveFunc = (int)ReturnGiveValue - nBase;
    i = 0;
    LOGD("fakeFunc Addr : %x",fakeFunc);
    LOGD("giveFunc Addr : %x",giveFunc);

    void* pstart = (void*)MEM_PAGE_START(((ElfW(Addr))systemTableAddr));
    mprotect(pstart,MEM_PAGE_SIZE,PROT_READ | PROT_WRITE | PROT_EXEC);
    ElfW(Sym)* symTab = (ElfW(Sym)*)(systemTableAddr);
    while(1)
    {
        LOGD("func Addr : %x",symTab[i].st_value);
        if(symTab[i].st_value == giveFunc)
        {
            symTab[i].st_value = fakeFunc;
            LOGD("New Give func Addr : %x",symTab[i].st_value);
            break;
        }
        i ++;
    }
    mprotect(pstart,MEM_PAGE_SIZE,PROT_READ | PROT_EXEC);

    return 0;
}