/*
ʵ��Ŀ�ģ�����MMU��ӳ��SDRAM�ĵ�ַ�ռ䣬
���������ַʵ�֡���ƴ󷨡����������MMU��ʹ�á�

ʵ�黷����˵��������S3C2410������H2410��H2410���İ�
��չ��64MB��K4S561632 SDRAM(4M*16bit*4BANK)����ַ��Χ��0x30000000~0x33FFFFFF��
GPIO�˿ڵĵ�ַ��Χ��0x56000000~0X560000B0��

ʵ��˼·���������ϵ��������Զ���NandFlash��ʼ��4K����
���Ƶ�SRAM�У�Ȼ����ת��0��ַ��ʼִ�У�Ȼ���ʼ���洢
������SDRAM����2K��Ĵ����SRAM�и��Ƶ�SDRAM��(�����0x30004000��
ǰ16KB�������ҳ��)������ҳ������MMUʵ�������ַӳ��GPIO�Ĵ�
����SDRAM�������ת��SDRAM��(��ַ0xB0004000)���С���������ջָ�룬
������ƴ������ڵ�ʵ�ֵ�Ʋ���
*/

.text
.global _start
_start:
    bl  disable_watch_dog                   @ �ر�WATCHDOG������CPU�᲻������
    bl  mem_control_setup                  @ ���ô洢��������ʹ��SDRAM
    ldr sp, =4096                                    @ ����ջָ�룬������C��������ǰ��Ҫ���ջ
    bl  copy_2th_to_sdram                   @ ���ڶ����ִ��븴�Ƶ�SDRAM
    bl  create_page_table                     @ ����ҳ��
    bl  mmu_init                                      @ ����MMU�������Ժ�������붼�������ַ
    ldr sp, =0xB4000000                       @ ����ջָ�룬ָ��SDRAM����(ʹ�������ַ)
    ldr pc, =0xB0004000                        @ ����SDRAM�м���ִ�еڶ����ִ���
halt_loop:
    b   halt_loop
������ҳ��
void create_page_table(void)
{

/*
* ���ڶ���������һЩ�궨�壺[31:20]�λ�ַ��[11:10]AP��[8:5]Domain��[3]C��[2]B��[1:0]0b10Ϊ��������
*/
#define MMU_FULL_ACCESS     (3 << 10)   /* ����Ȩ��AP */
#define MMU_DOMAIN          (0 << 5)    /* �����ĸ��� Domain*/
#define MMU_SPECIAL         (1 << 4)    /* ������1 */
#define MMU_CACHEABLE       (1 << 3)    /* cacheable Cλ*/
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable Bλ*/
#define MMU_SECTION         (2)         /* ��ʾ���Ƕ������� */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)
#define MMU_SECTION_SIZE    0x00100000        /*ÿ������������Ӧ1MB��С�ռ�*/


    unsigned long virtuladdr, physicaladdr;
    unsigned long *mmu_tlb_base = (unsigned long *)0x30000000;        /*SDRAM��ʼ��ַ���ҳ��*/

    /*
     * Steppingstone����ʼ�����ַΪ0����һ���ֳ������ʼ���е�ַҲ��0�� Ϊ���ڿ���MMU���������е�һ���ֵĳ��� ��0��1M�������ַӳ�䵽ͬ���������ַ
     */
    virtuladdr = 0;
    physicaladdr = 0;
    /*�����ַ[31:20]��������һ��ҳ���ҵ�����Ӧ������������Ӧ��(virtualaddr>>20)������������[31:20]����ε������ַ����Ӧ(physicaladdr & 0xFFF00000)*/
    *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_WB;

    /*
     * 0x56000000��GPIO�Ĵ�������ʼ�����ַ��GPBCON��GPBDAT�������Ĵ����������ַ0x56000010��0x56000014�� Ϊ���ڵڶ����ֳ��������Ե�ַ0xA0000010��0xA0000014������GPBCON��GPBDAT��
     * �Ѵ�0xA0000000��ʼ��1M�����ַ�ռ�ӳ�䵽��0x56000000��ʼ��1M�����ַ�ռ�
     */
    virtuladdr = 0xA0000000;
    physicaladdr = 0x56000000;
    *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC;


    /*
     * SDRAM�������ַ��Χ��0x30000000��0x33FFFFFF�� �������ַ0xB0000000��0xB3FFFFFFӳ�䵽�����ַ0x30000000��0x33FFFFFF�ϣ� �ܹ�64M���漰64����������
     */
    virtuladdr = 0xB0000000;
    physicaladdr = 0x30000000;
    while (virtuladdr < 0xB4000000)
    {
        *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_WB;
        virtuladdr += MMU_SECTION_SIZE;
        physicaladdr += MMU_SECTION_SIZE;
    }
}
�� ����MMU��
void mmu_init(void)
{
    unsigned long ttb = 0x30000000;


__asm__(
    "mov    r0, #0\n"
    "mcr    p15, 0, r0, c7, c7, 0\n"    /* ʹ��ЧICaches��DCaches */

    "mcr    p15, 0, r0, c7, c10, 4\n"   /* drain write buffer on v4 */
    "mcr    p15, 0, r0, c8, c7, 0\n"    /* ʹ��Чָ�����TLB */

    "mov    r4, %0\n"                   /* r4 = ҳ���ַ */
    "mcr    p15, 0, r4, c2, c0, 0\n"    /* ����ҳ���ַ�Ĵ��� */

    "mvn    r0, #0\n"
    "mcr    p15, 0, r0, c3, c0, 0\n"    /* ����ʿ��ƼĴ�����Ϊ0xFFFFFFFF�� ������Ȩ�޼��*/
    /*
     * ���ڿ��ƼĴ������ȶ�����ֵ������������޸ĸ���Ȥ��λ��Ȼ����д��
     */
    "mrc    p15, 0, r0, c1, c0, 0\n"    /* �������ƼĴ�����ֵ */

    /* ���ƼĴ����ĵ�16λ����Ϊ��.RVI ..RS B... .CAM
     * R : ��ʾ����Cache�е���Ŀʱʹ�õ��㷨��0 = Random replacement��1 = Round robin replacement
     * V : ��ʾ�쳣���������ڵ�λ�ã�0 = Low addresses = 0x00000000��1 = High addresses = 0xFFFF0000
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
    : /* ����� */
    : "r" (ttb) );
}


