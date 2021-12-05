#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "SMM_MPS3.h"

void main(void)
{
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if(core_clock != 0)
        SystemCoreClockUpdate();
        
    UartStdOutInit();

    while (1){
        printk("hello %s\n", get_boardinfo());
    };
}
