#include <stdio.h>

int main(void)
{
    int i=5;
    int p[6] ={0};

    void *ptr = malloc(i);
    
    while(i--)
    {
        p[i-2] =i;
        printf("i %d\np  %p\n",i,&p[i-2]);
    }
    return 0;
}
