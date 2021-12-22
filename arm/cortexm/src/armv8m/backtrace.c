
#include <stdint.h>

/*
-->High Address,Stack Top
PC<------|
LR       |
IP       |
FP       |
......   |
PC <-|   |
LR   |   |
IP   |   |
FP---|-- |
......   |
PC       |
LR       |
IP       |
FP---
-->Low Address,Stack Bottom
*/
void rt_hw_backtrace(uint32_t *fp, uint32_t thread_entry)
{
    uint32_t i, pc, func_entry;

    pc = *fp;
    printk("[0x%x]\n", pc-0xC);

    for(i=0; i<10; i++)
    {
        fp = (uint32_t *)*(fp - 3);
        pc = *fp ;

        func_entry = pc - 0xC;

        if(func_entry <= 0x30000000) break;

        if(func_entry == thread_entry)
        {
            printk("EntryPoint:0x%x\n", func_entry);

            break;
        }

        printk("[0x%x]\n", func_entry);
    }
}

