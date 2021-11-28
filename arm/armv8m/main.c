#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "cmsdk_uart.h"


void main(void)
{
    pal_uart_cmsdk_init(0x50200000);
    while (1){
        printk("hello armv8@@@@\n");
    };
}
