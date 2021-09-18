// thumb mode ����bit[0]��ֵΪ1 
#define SET_BIT0(addr)		(addr | 1)
// arm mode ����bit[0]��ֵΪ0
#define CLEAR_BIT0(addr)	(addr & 0xFFFFFFFE)
// ����bit[0]��ֵ����Ϊ1�򷵻��棬��Ϊ0�򷵻ؼ�
#define TEST_BIT0(addr)		(addr & 1)

typedef unsignedt short int uint16_t;

struct Item {
        unsigned int target_addr;
        unsigned int new_addr;
};

//LDR PC, [PC, #-4]��Ӧ�Ļ�����Ϊ��0xE51FF004
BYTE szLdrPCOpcodes[8] = {0x04, 0xF0, 0x1F, 0xE5};
//��Ŀ�ĵ�ַ��������תָ���·���4 Bytes��

void hook_old_func(void)
{
        printf("hello old wrold\n");
}

void hook_stub_func(void)
{
        printf("hello new wrold\n");
}

void hook_init(void * pJumpAddress)
{       
        memcpy(szLdrPCOpcodes + 4, pJumpAddress, 4);
}

void insert_stub_func(struct Item * item)
{
        // Thumb Mode
        if (TEST_BIT0(item->target_addr)) {
        	int i;
        	i = 0;
        	if (CLEAR_BIT0(item->target_addr) % 4 != 0) {
                /*
bit[0]��ֵ���㣬����ֵ4�ֽڲ����룬
�����һ��2�ֽڵ�NOPָ�
ʹ�ú�����ָ��4�ֽڶ��롣
������Ϊ��Thumb32ָ���У�
����ָ���PC�Ĵ�����ֵ�������޸ģ�
���ָ�������4�ֽڶ���ģ�����Ϊ�Ƿ�ָ��
                */
        		((uint16_t *) CLEAR_BIT0(item->target_addr))[i++] = 0xBF00;  // NOP
        	}
        	((uint16_t *) CLEAR_BIT0(item->target_addr))[i++] = 0xF8DF;
        	((uint16_t *) CLEAR_BIT0(item->target_addr))[i++] = 0xF000;	// LDR.W PC, [PC]
        	((uint16_t *) CLEAR_BIT0(item->target_addr))[i++] = item->new_addr & 0xFFFF;
        	((uint16_t *) CLEAR_BIT0(item->target_addr))[i++] = item->new_addr >> 16;
        }
        //  ARM Mode
        else {
        	((uint32_t *) (item->target_addr))[0] = 0xe51ff004;	// LDR PC, [PC, #-4]
        	((uint32_t *) (item->target_addr))[1] = item->new_addr;
        }

}


int main(void)
{
        struct Item item;

        hook_old_func();
        item.target_addr = (unsigned int)hook_old_func;;
        item.new_addr = (unsigned int)hook_stub_func;
        insert_stub_func(item);
        hook_old_func();
}

