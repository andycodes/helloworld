# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/local/4.9.3/arm-cortexa9-linux-gnueabihf/sys-root/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "main.c"
# 1 "s3c2410.h" 1
# 2 "main.c" 2
# 1 "serial.h" 1
void putc(unsigned char c);
unsigned char getc( );
void printk(unsigned char* str);
# 3 "main.c" 2







static unsigned long m_RandSeed;
static unsigned long m_RandSeed1 = 0x12345678;



inline unsigned long Rand()
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
 (*(volatile unsigned long *)0x56000010) = (1<<(7*2))|(1<<(8*2))|(1<<(9*2))|(1<<(10*2));

 init_uart( );

 while(1){
  wait(100000);
  (*(volatile unsigned long *)0x56000014) = (~( (i++)<<7));
 }

 return 0;
}
