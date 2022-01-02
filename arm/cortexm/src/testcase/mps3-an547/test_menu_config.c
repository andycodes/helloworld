//#include "cmsdk_uart.h"
#include "os_stdio.h"
#include <stdint.h>
#include "config.h"


static void test_menuconfig(void)
{
#ifdef CONFIG_MEMU
    printk("test_menuconfig defined \n");
#else
    printk("test_menuconfig not defined\n");
#endif
}

device_initcall(test_menuconfig);