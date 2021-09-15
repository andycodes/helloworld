

//4.got �� hook ����(hook fopen����Ϊ��)
//4.1 ��ȡ��̬��Ļ���ַ
void *base_addr = get_model_base(getpid(), "libnative-lib.so");  // ��ȡmap�ļ������ж�ȡ�ָ�ƥ�䣬��ȡso��Ӧ���ڴ����ַ

//4.2 ����SO�� program head table�ĵ�ַ
int get_program_head_table()
{

  Elf32_Ehdr *header = (Elf32_Ehdr *) (base_addr);
    if (memcmp(header->e_ident, "\177ELF", 4) != 0) {  // �ж�Ϊelf�ļ�
        LOGD("[Error!] not  elf file ");  
        return 0;
    }

    Elf32_Phdr *phdr_table = (Elf32_Phdr *) (base_addr + header->e_phoff);  // ����ͷ����ĵ�ַ
    if (phdr_table == 0) {
        LOGD("[error !] phdr_table address : 0 ");
        return 0;
    }
    size_t phr_count = header->e_phnum;  // ����ͷ�������
}

//4.3 ��������ͷ������ȡ��̬�ε�ַ
//���� program head table���ҵ�p_type Ϊdynameic�ģ�
//��ȡ��p_offset
get_dynamicAddr()
{
    unsigned long dynamicAddr;  // ��̬�ڵ� ��ַ
    unsigned int dynamicSize;  // ��̬�� ��С
    for (int j = 0; j < phr_count; j++) {
        if (phdr_table[j].p_type == PT_DYNAMIC) {
            dynamicAddr = phdr_table[j].p_vaddr + base_addr;
            dynamicSize = phdr_table[j].p_memsz;
            break;
        }
    }


}

//4.4 ������̬�Σ��ҵ�got���ַ
//��ʼ����dynamic�νᣬd_tagΪ6��ΪGOT���ַ
get_got_addr()
{
    int symbolTableAddr = 0;  // ���ű��ַ
    Elf32_Dyn *dynamic_table = (Elf32_Dyn *) dynamicAddr;
    for (i = 0; i < dynamicSize / 8; i++) {
        int val = dynamic_table[i].d_un.d_val;
        if (dynamic_table[i].d_tag == 6) {
            symbolTableAddr = val + base_addr;
            break;
        }
    }
}

//4.5 �޸��ڴ�����Ϊ��д
modify_memory_attr()
{
uint32_t page_size = getpagesize(); // ��ȡ�ڴ��ҳ����ʼ��ַ����Ҫ�ڴ���룩
mprotect((uint32_t) mem_page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
}

//4.6 ����got���޸�Ҫ�滻��fopen����
for_got_to_find_func()
{
int oldFunc = fopen - (int) base_addr; // ԭĿ�꺯�� ��ַ
int newFunc = fakeFunc;  // �滻��hook������ƫ�Ƶ�ַ
 while (1) {
        if (symTab[i].st_value == oldFunc) {
            symTab[i].st_value = newFunc;  // st_value �������ƫ�Ƶ�ַ
            break;
        }
        i++;
    }
}

//4.7 �ָ�������Ϊ�ɶ���ִ��

mprotect((uint32_t) mem_page_start, page_size, PROT_READ | PROT_EXEC);

