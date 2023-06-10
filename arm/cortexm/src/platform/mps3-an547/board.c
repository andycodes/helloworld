#include "SMM_MPS3.h"
#include "core_cm55.h"
#include "os.h"
#include "system_ARMCM55.h"
#include "uart.h"

char *board_info(void)
{
    return "CM55,mps3-an547";
}

void fault_init(void)
{
    SCB->SHCSR |=  SCB_SHCSR_SECUREFAULTENA_Msk | SCB_SHCSR_USGFAULTENA_Msk
    | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk | SCB_CCR_DIV_0_TRP_Msk |
    SCB_CCR_BFHFNMIGN_Msk;
}

void mpu_init(void)
{
    MPU->CTRL &= ~MPU_CTRL_HFNMIENA_Msk;
    MPU->CTRL &= ~MPU_CTRL_PRIVDEFENA_Msk;
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

    mpu_init();
    fault_init();
    printk ("Version 1.1.0" " Build date: " __DATE__ "\n");

    extern void overlay_main(void);
    overlay_main();
}