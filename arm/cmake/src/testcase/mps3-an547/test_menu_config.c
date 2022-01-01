#include "cmsdk_uart.h"
#include "os_stdio.h"
#include <stdint.h>


void test_menuconfig(void)
{
#ifdef CONFIG_MEMU
    printk("test_menuconfig defined \n");
#else
    printk("test_menuconfig not defined\n");
#endif
}