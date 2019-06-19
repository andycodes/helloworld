/*
 * leds.c: ѭ������4��LED
 * ���ڵڶ����ֳ��򣬴�ʱMMU�ѿ�����ʹ�������ַ
 */ 

#define GPFCON      (*(volatile unsigned long *)0xA0000050)     // �����ַ0x56000050
#define GPFDAT      (*(volatile unsigned long *)0xA0000054)     // �����ַ0x56000054

#define GPF4_out    (1<<(4*2))
#define GPF5_out    (1<<(5*2))
#define GPF6_out    (1<<(6*2))

/*
 * wait�������ϡ�static inline������ԭ��ģ�
 * ��������ʹ�ñ���leds.cʱ��waitǶ��main�У���������ֻ��mainһ��������
 * ����������ʱ��main�����ĵ�ַ�����������ļ�ָ��������ʱװ�ص�ַ��
 * �������ļ�mmu.lds�У�ָ����leds.o������ʱװ�ص�ַΪ0xB4004000��
 * ������head.S�еġ�ldr pc, =0xB0004000��������ȥִ��main������
 */
static inline void wait(volatile unsigned long dly)
{
    for(; dly > 0; dly--);
}

int main(void)
{
    unsigned long i = 0;

    GPFCON = GPF4_out|GPF5_out|GPF6_out;        // ��LED1,2,4��Ӧ��GPF4/5/6����������Ϊ���

    while(1){
        wait(30000);
        GPFDAT = (~(i<<4));        // ����i��ֵ������LED1,2,4
        if(++i == 8)
            i = 0;
    }

    return 0;
}