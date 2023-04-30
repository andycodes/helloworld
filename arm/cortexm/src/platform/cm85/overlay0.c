
#include "uart.h"

int g_oly0_cnt = 9;

void overlay_function1()
{
    printk("Written by overlay_function1 %d\n", g_oly0_cnt);
}
