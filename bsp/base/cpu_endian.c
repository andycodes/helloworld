#include <stdio.h>

int check_cpu_endian(void)
{
   union w
     { 
       int a;
       char b;
     } c;
   
    c.a = 1;
    
    return(c.b ==1);
}

int main(void)
{
    printf("%d\n",check_cpu_endian());
    return 0;
}

