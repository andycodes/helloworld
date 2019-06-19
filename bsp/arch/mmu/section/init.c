/*
JZ2440V3��SDRAM�����ַ��Χ����0x30000000~0x33FFFFFF,S3C2440�ļĴ�����ַ��Χ������0x48000000~0x5FFFFFFF����ǰ�棬ͨ����GPBCON��GPBDAT�������Ĵ����������ַ0x56000010��0x56000014д���ض�������������4��LED
����MMU�����������ַ�ռ�0xA0000000~0xA0100000ӳ�䵽�����ַ�ռ�0x56000000~0x56100000�ϣ������Ϳ���ͨ��������ַ0xA0000010��0xA0000014���ﵽ������4��LED��ͬ��Ч��
���⣬�������ַ�ռ�0xB0000000~0xB3FFFFFFӳ�䵽�����ַ�ռ�0x30000000~0x33FFFFFF�ϣ�����������ʱ��һ���ִ�������е�ַָ��Ϊ0xB0004000�������ܷ��������ת��0xB0004000(��0x30004000)��ִ��
��������ֻʹ��һ��ҳ���Զεķ�ʽ���е�ַӳ�䡣32λCPU�������ַ�ռ�ﵽ4GB��һ��ҳ����ʹ��4096������������ʾ��4GB�Ŀռ�(ÿ����������Ӧ1MB�������ַ)��ÿ��������ռ��4�ֽڣ�����һ��ҳ��ռ16KB(4096*4KB)���ڴ�ʹ��SDRAM��ʼ��16KB(0x4000)�����һ��ҳ������ʣ�µ��ڴ濪ʼ�����ַΪ0x30004000��
*/


/*
 * init.c: ����һЩ��ʼ������Steppingstone������
 * ����head.Sͬ����һ���ֳ��򣬴�ʱMMUδ������ʹ�������ַ
 */

/* WATCHDOG�Ĵ��� */
#define WTCON           (*(volatile unsigned long *)0x53000000)
/* �洢�������ļĴ�����ʼ��ַ */
#define MEM_CTL_BASE    0x48000000


/*
 * �ر�WATCHDOG������CPU�᲻������
 */
void disable_watch_dog(void)
{
    WTCON = 0;  // �ر�WATCHDOG�ܼ򵥣�������Ĵ���д0����
}

/*
 * ���ô洢��������ʹ��SDRAM
 */
void memsetup(void)
{
    /* SDRAM 13���Ĵ�����ֵ */
    unsigned long  const    mem_cfg_val[]={ 0x22011110,     //BWSCON
                                            0x00000700,     //BANKCON0
                                            0x00000700,     //BANKCON1
                                            0x00000700,     //BANKCON2
                                            0x00000700,     //BANKCON3
                                            0x00000700,     //BANKCON4
                                            0x00000700,     //BANKCON5
                                            0x00018005,     //BANKCON6
                                            0x00018005,     //BANKCON7
                                            0x008C07A3,     //REFRESH
                                            0x000000B1,     //BANKSIZE
                                            0x00000030,     //MRSRB6
                                            0x00000030,     //MRSRB7
                                    };
    int     i = 0;
    volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;
    for(; i < 13; i++)
        p[i] = mem_cfg_val[i];
}

/*
 * ���ڶ����ִ��븴�Ƶ�SDRAM
 */
void copy_2th_to_sdram(void)
{
    unsigned int *pdwSrc  = (unsigned int *)2048; //led.o�ļ��ص�ַ�����ӽű��б�ָ��2048;�ھ����ļ��е�λ��
                                                  //���Եڶ����ִ���ʹ洢��Steppingstone�е�ַ2048֮��
    unsigned int *pdwDest = (unsigned int *)0x30004000;

    while (pdwSrc < (unsigned int *)4096)
    {
        *pdwDest = *pdwSrc;
        pdwDest++;
        pdwSrc++;
    }
}

/*
S3C2440 MANUAL �洢��������
 ����ҳ��
 */
void create_page_table(void)
{

/*
 * ���ڶ���������һЩ�궨��
 * ��������bit[11:0]=0b110000011110
 */
#define MMU_FULL_ACCESS     (3 << 10)   /* ����Ȩ�� */
#define MMU_DOMAIN          (0 << 5)    /* �����ĸ��� */
#define MMU_SPECIAL         (1 << 4)    /* ������1 */
#define MMU_CACHEABLE       (1 << 3)    /* cacheable */
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable */
#define MMU_SECTION         (2)         /* ��ʾ���Ƕ������� */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | \
                             MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)
#define MMU_SECTION_SIZE    0x00100000

	unsigned long virtuladdr, physicaladdr;
	unsigned long *mmu_tlb_base = (unsigned long *)0x30000000;/*�����ַ  bank6	 ֧��SDRAM*/

	/*
	* Steppingstone����ʼ�����ַΪ0����һ���ֳ������ʼ���е�ַҲ��0��
	* Ϊ���ڿ���MMU���������е�һ���ֵĳ���
	* ��0��1M�������ַӳ�䵽ͬ���������ַ
	*/
	virtuladdr = 0;
	physicaladdr = 0;
	*(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_WB;
	//*(mmu_tlb_base + (virtuladdr >> 20)) = *(TTB[31-14]+MVA[31-20]+00) = *(��������ַ)


	/*
	* 0x56000000��GPIO�Ĵ�������ʼ�����ַ��
	* GPBCON��GPBDAT�������Ĵ����������ַ0x56000050��0x56000054��
	* Ϊ���ڵڶ����ֳ��������Ե�ַ0xA0000050��0xA0000054������GPFCON��GPFDAT��
	* �Ѵ�0xA0000000��ʼ��1M�����ַ�ռ�ӳ�䵽��0x56000000��ʼ��1M�����ַ�ռ�
	*/
	virtuladdr = 0xA0000000;
	physicaladdr = 0x56000000;
	*(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC;
	//*(mmu_tlb_base + (virtuladdr >> 20)) =*(TTB[31-14]+MVA[31-20]+00) = *(��������ַ)


	/*
	* SDRAM�������ַ��Χ��0x30000000��0x33FFFFFF��
	* �������ַ0xB0000000��0xB3FFFFFFӳ�䵽�����ַ0x30000000��0x33FFFFFF�ϣ�
	* �ܹ�64M���漰64����������
	*/
	virtuladdr = 0xB0000000;
	physicaladdr = 0x30000000;
	while (virtuladdr < 0xB4000000) {
		*(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_WB;
		virtuladdr += 0x100000; //0x100000 = 1MB����ҳ����1MBΪ��λ
		physicaladdr += 0x100000;
	}
}

/*
 * ����MMU
 */
void mmu_init(void)
{
    unsigned long ttb = 0x30000000;

__asm__(
    "mov    r0, #0\n"
    "mcr    p15, 0, r0, c7, c7, 0\n"    /* ʹ��ЧICaches��DCaches */

    "mcr    p15, 0, r0, c7, c10, 4\n"   /* drain write buffer on v4 */
    "mcr    p15, 0, r0, c8, c7, 0\n"    /* ʹ��Чָ�����TLB */

    "mov    r4, %0\n"                   /* r4 = ҳ���ַ ��ȡ��0������*/
    "mcr    p15, 0, r4, c2, c0, 0\n"    /* ����ҳ���ַ�Ĵ��� */

    "mvn    r0, #0\n"
    "mcr    p15, 0, r0, c3, c0, 0\n"    /* ����ʿ��ƼĴ�����Ϊ0xFFFFFFFF��
                                         * ������Ȩ�޼��
                                         */
    /*
     * ���ڿ��ƼĴ������ȶ�����ֵ������������޸ĸ���Ȥ��λ��
     * Ȼ����д��
     */
    "mrc    p15, 0, r0, c1, c0, 0\n"    /* �������ƼĴ�����ֵ */

    /* ���ƼĴ����ĵ�16λ����Ϊ��.RVI ..RS B... .CAM
     * R : ��ʾ����Cache�е���Ŀʱʹ�õ��㷨��
     *     0 = Random replacement��1 = Round robin replacement
     * V : ��ʾ�쳣���������ڵ�λ�ã�
     *     0 = Low addresses = 0x00000000��1 = High addresses = 0xFFFF0000
     * I : 0 = �ر�ICaches��1 = ����ICaches
     * R��S : ������ҳ���е�������һ��ȷ���ڴ�ķ���Ȩ��
     * B : 0 = CPUΪС�ֽ���1 = CPUΪ���ֽ���
     * C : 0 = �ر�DCaches��1 = ����DCaches
     * A : 0 = ���ݷ���ʱ�����е�ַ�����飻1 = ���ݷ���ʱ���е�ַ������
     * M : 0 = �ر�MMU��1 = ����MMU
     */

    /*
     * ���������Ҫ��λ����������Ҫ��������������
     */
                                        /* .RVI ..RS B... .CAM */
    "bic    r0, r0, #0x3000\n"          /* ..11 .... .... .... ���V��Iλ */
    "bic    r0, r0, #0x0300\n"          /* .... ..11 .... .... ���R��Sλ */
    "bic    r0, r0, #0x0087\n"          /* .... .... 1... .111 ���B/C/A/M */

    /*
     * ������Ҫ��λ
     */
    "orr    r0, r0, #0x0002\n"          /* .... .... .... ..1. ���������� */
    "orr    r0, r0, #0x0004\n"          /* .... .... .... .1.. ����DCaches */
    "orr    r0, r0, #0x1000\n"          /* ...1 .... .... .... ����ICaches */
    "orr    r0, r0, #0x0001\n"          /* .... .... .... ...1 ʹ��MMU */

    "mcr    p15, 0, r0, c1, c0, 0\n"    /* ���޸ĵ�ֵд����ƼĴ��� */
    : /* ����� */ //���
    : "r" (ttb) );  //���� r=ttb����0������
}