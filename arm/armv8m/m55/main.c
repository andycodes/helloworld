#include <stdint.h>
#include <stdbool.h>


#include "os_stdio.h"

extern void UartStdOutInit(void);
extern void printk(const char *fmt, ...);

void main(void)
{
    UartStdOutInit();

    while (1){
        printk("hello cortex-m55@@@@\n");
    };
}
