#include "SMM_MPS3.h"
#include <ARMCM85.h>
#include <core_cm85.h>
#include "os.h"
#include "system_ARMCM85.h"
#include "uart.h"

char *board_info(void)
{
    return "CM85,CM85";
}

void fault_init(void)
{
    SCB->SHCSR |=  SCB_SHCSR_SECUREFAULTENA_Msk | SCB_SHCSR_USGFAULTENA_Msk
    | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk | SCB_CCR_DIV_0_TRP_Msk;
}

void board_init(void)
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

    fault_init();

    printk ("Version 1.1.0" " Build date: " __DATE__ "\n");
}