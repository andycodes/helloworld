#include <stdint.h>
#include "os_stdio.h"

void rt_hw_show_memory(uint32_t addr, uint32_t size)
{
    int i = 0, j =0;

    //RT_ASSERT(addr);

    addr = addr & ~0xF;
    size = 4*((size + 3)/4);

    while(i < size)
    {
        printk("0x%08x: ", addr );

        for(j=0; j<4; j++)
        {
            printk("0x%08x  ", *(uint32_t *)addr);

            addr += 4;
            i++;
        }

        printk("\n");
    }

    return;
}
