#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "SMM_MPS3.h"
#include "core_cm55.h"

void system_init(void)
{
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if(core_clock != 0)
        SystemCoreClockUpdate();
        
    UartStdOutInit();

    //NVIC_ClearAllPendingIRQ();
    NVIC->ICPR[0] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[1] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[2] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[3] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[4] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[5] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[6] = 0xFFFFFFFF;         /* Clear all pending interrupts */
    NVIC->ICPR[7] = 0xFFFFFFFF;         /* Clear all pending interrupts */
}

void main(void)
{
    system_init();
    printk("hello %s ^-^^-^^-^^-^\n", get_boardinfo());
    testcase();
}
