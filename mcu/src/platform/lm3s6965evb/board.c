#if 1
#include "os.h"
#include "uart.h"

char *board_info(void)
{
    return "CM3";
}

void mpu_init(void)
{
#if 0
    MPU->CTRL &= ~MPU_CTRL_HFNMIENA_Msk;
    MPU->CTRL &= ~MPU_CTRL_PRIVDEFENA_Msk;
#endif
}

void board_init(void)
{
#if 0
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
    printk ("Version 1.1.0" " Build date: " __DATE__ "\n");

    extern void overlay_main(void);
    overlay_main();
#endif
}
#endif