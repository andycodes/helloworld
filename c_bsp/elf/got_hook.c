

//4.got 表 hook 流程(hook fopen函数为例)
//4.1 获取动态库的基地址
void *base_addr = get_model_base(getpid(), "libnative-lib.so");  // 读取map文件，按行读取分割匹配，获取so对应的内存基地址

//4.2 计算SO中 program head table的地址
int get_program_head_table()
{

  Elf32_Ehdr *header = (Elf32_Ehdr *) (base_addr);
    if (memcmp(header->e_ident, "\177ELF", 4) != 0) {  // 判断为elf文件
        LOGD("[Error!] not  elf file ");  
        return 0;
    }

    Elf32_Phdr *phdr_table = (Elf32_Phdr *) (base_addr + header->e_phoff);  // 程序头部表的地址
    if (phdr_table == 0) {
        LOGD("[error !] phdr_table address : 0 ");
        return 0;
    }
    size_t phr_count = header->e_phnum;  // 程序头表项个数
}

//4.3 遍历程序头部表，获取动态段地址
//遍历 program head table，找到p_type 为dynameic的，
//获取到p_offset
get_dynamicAddr()
{
    unsigned long dynamicAddr;  // 动态节的 地址
    unsigned int dynamicSize;  // 动态段 大小
    for (int j = 0; j < phr_count; j++) {
        if (phdr_table[j].p_type == PT_DYNAMIC) {
            dynamicAddr = phdr_table[j].p_vaddr + base_addr;
            dynamicSize = phdr_table[j].p_memsz;
            break;
        }
    }


}

//4.4 遍历动态段，找到got表地址
//开始遍历dynamic段结，d_tag为6即为GOT表地址
get_got_addr()
{
    int symbolTableAddr = 0;  // 符号表地址
    Elf32_Dyn *dynamic_table = (Elf32_Dyn *) dynamicAddr;
    for (i = 0; i < dynamicSize / 8; i++) {
        int val = dynamic_table[i].d_un.d_val;
        if (dynamic_table[i].d_tag == 6) {
            symbolTableAddr = val + base_addr;
            break;
        }
    }
}

//4.5 修改内存属性为可写
modify_memory_attr()
{
uint32_t page_size = getpagesize(); // 获取内存分页的起始地址（需要内存对齐）
mprotect((uint32_t) mem_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
}

//4.6 遍历got表，修改要替换的fopen函数
for_got_to_find_func()
{
int oldFunc = fopen - (int) base_addr; // 原目标函数 地址
int newFunc = fakeFunc;  // 替换的hook函数的偏移地址
 while (1) {
        if (symTab[i].st_value == oldFunc) {
            symTab[i].st_value = newFunc;  // st_value 保存的是偏移地址
            break;
        }
        i++;
    }
}

//4.7 恢复存属性为可读可执行

mprotect((uint32_t) mem_page_start, page_size, PROT_READ | PROT_EXEC);

