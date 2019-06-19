#include "s3c2410.h"
#include "serial.h"
 
#define	TXD0READY	(1<<2)
#define	RXD0READY	(1)

void init_uart( )
{//��ʼ��UART
	GPHCON |= 0xa0;		//GPH2,GPH3 used as TXD0,RXD0
	GPHUP	 = 0x0c;		//GPH2,GPH3�ڲ�����

	ULCON0	 = 0x03;		//8N1	
	UCON0	 = 0x05;		//��ѯ��ʽ
	UFCON0 = 0x00;		//��ʹ��FIFO
	UMCON0 = 0x00;		//��ʹ������
	UBRDIV0 = 12;		//������Ϊ57600

}

void putc(unsigned char c)
{
	while( ! (UTRSTAT0 & TXD0READY) );
	UTXH0 = c;
}

unsigned char getc( )
{
	while( ! (UTRSTAT0 & RXD0READY) );
	return URXH0;
}

void printk(unsigned char* str)
{
	int i = 0;
	while( str[i] ){
		putc( (unsigned char) str[i++] );
	}
}
