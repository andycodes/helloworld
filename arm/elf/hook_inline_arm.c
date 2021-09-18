// thumb mode 设置bit[0]的值为1 
#define SET_BIT0(addr)		(addr | 1)
// arm mode 设置bit[0]的值为0
#define CLEAR_BIT0(addr)	(addr & 0xFFFFFFFE)
// 测试bit[0]的值，若为1则返回真，若为0则返回假
#define TEST_BIT0(addr)		(addr & 1)

typedef unsignedt short int uint16_t;

struct Item {
        unsigned int target_addr;
        unsigned int new_addr;
};

//LDR PC, [PC, #-4]对应的机器码为：0xE51FF004
BYTE szLdrPCOpcodes[8] = {0x04, 0xF0, 0x1F, 0xE5};
//将目的地址拷贝到跳转指令下方的4 Bytes中

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
bit[0]的值清零，若其值4字节不对齐，
则添加一个2字节的NOP指令，
使得后续的指令4字节对齐。
这是因为在Thumb32指令中，
若该指令对PC寄存器的值进行了修改，
则该指令必须是4字节对齐的，否则为非法指令
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

