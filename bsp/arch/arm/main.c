#include "s3c2410.h"
#include "serial.h"

#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))
#define	GPB9_out	(1<<(9*2))
#define	GPB10_out	(1<<(10*2))


static unsigned long m_RandSeed;
static unsigned long m_RandSeed1 = 0x12345678;


/* ������� */
inline unsigned long  Rand()
{
    return (m_RandSeed=1664525L*m_RandSeed+1013904223L)>>5;
}

void wait(unsigned long dly)
{
	for(; dly > 0; dly--);
}

int main()
{
	unsigned long i = 0, cnt = 0;
	unsigned char c;
	Rand();
	GPBCON	 = GPB7_out|GPB8_out|GPB9_out|GPB10_out;

	init_uart( );	//������57600��8N1(8������λ����У��λ��1��ֹͣλ)

	while(1){
		wait(100000);
		GPBDAT = (~( (i++)<<7));
	}

	return 0;
}
