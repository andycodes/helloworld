#define GPKCON (volatile unsigned long*)0xA0008820
#define GPKDAT (volatile unsigned long*)0xA0008824

/*
 * 用于段描述符的一些宏定义
 */
#define MMU_FULL_ACCESS     (3 << 10)   /* 段的访问权限 AP*/
#define MMU_DOMAIN          (0 << 5)    /* 属于哪个域 */
#define MMU_SPECIAL         (1 << 4)    /* 必须是1 */
#define MMU_CACHEABLE       (1 << 3)    /* cacheable 快速访问*/
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable 缓冲区 */
#define MMU_SECTION         (2)         /* 表示这是段描述符 */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)


void create_page_table(void)
/*
1. 建立页表
2. 写入TTB （cp15 c2）
3. 使能MMU
*/
{
    unsigned long *ttb = (unsigned long *)0x50000000;
    unsigned long vaddr, paddr;

    vaddr = 0xA0000000;
    paddr = 0x7f000000;
    *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC;

    vaddr = 0x50000000; /* 映射内存 */
    paddr = 0x50000000;
    while (vaddr < 0x54000000)
    {
        *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC_WB;
        vaddr += 0x100000;  /* 每一个表项只能映射1M */
        paddr += 0x100000;
    }

}


void mmu_init()
{
   __asm__(

    /*设置TTB 写入cp15的c2中*/
    "ldr    r0, =0x50000000\n"
    "mcr    p15, 0, r0, c2, c0, 0\n"

    /*不进行权限检查 域的访问权限取决于cp15的c3寄存器*/
    "mvn    r0, #0\n"
    "mcr    p15, 0, r0, c3, c0, 0\n"


   /*使能MMU*/
    "mrc    p15, 0, r0, c1, c0, 0\n"
    "orr    r0, r0, #0x0001\n"
    "mcr    p15, 0, r0, c1, c0, 0\n"
    :
    :
  );
}

int gboot_main()
{
    create_page_table();
    mmu_init();

    *(GPKCON) = 0x1111;
    *(GPKDAT) = 0xe;

    return 0;
}