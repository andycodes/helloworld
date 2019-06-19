#define GPKCON (volatile unsigned long*)0xA0008820
#define GPKDAT (volatile unsigned long*)0xA0008824

/*
 * ���ڶ���������һЩ�궨��
 */
#define MMU_FULL_ACCESS     (3 << 10)   /* �εķ���Ȩ�� AP*/
#define MMU_DOMAIN          (0 << 5)    /* �����ĸ��� */
#define MMU_SPECIAL         (1 << 4)    /* ������1 */
#define MMU_CACHEABLE       (1 << 3)    /* cacheable ���ٷ���*/
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable ������ */
#define MMU_SECTION         (2)         /* ��ʾ���Ƕ������� */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)


void create_page_table(void)
/*
1. ����ҳ��
2. д��TTB ��cp15 c2��
3. ʹ��MMU
*/
{
    unsigned long *ttb = (unsigned long *)0x50000000;
    unsigned long vaddr, paddr;

    vaddr = 0xA0000000;
    paddr = 0x7f000000;
    *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC;

    vaddr = 0x50000000; /* ӳ���ڴ� */
    paddr = 0x50000000;
    while (vaddr < 0x54000000)
    {
        *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC_WB;
        vaddr += 0x100000;  /* ÿһ������ֻ��ӳ��1M */
        paddr += 0x100000;
    }

}


void mmu_init()
{
   __asm__(

    /*����TTB д��cp15��c2��*/
    "ldr    r0, =0x50000000\n"
    "mcr    p15, 0, r0, c2, c0, 0\n"

    /*������Ȩ�޼�� ��ķ���Ȩ��ȡ����cp15��c3�Ĵ���*/
    "mvn    r0, #0\n"
    "mcr    p15, 0, r0, c3, c0, 0\n"


   /*ʹ��MMU*/
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