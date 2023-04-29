#include "uart.h"

int g_cpuide_cnt = 8;

void cpuidle(void)
{
    printk("cpuidle~~~%d\n", g_cpuide_cnt);
}