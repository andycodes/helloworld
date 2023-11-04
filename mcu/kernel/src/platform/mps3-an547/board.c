#include "SMM_MPS3.h"
#include <ARMCM55.h>
#include "core_cm55.h"
#include "os.h"
#include "system_ARMCM55.h"
#include "uart.h"
#include "mpu.h"

char *board_info(void)
{
    return "CM55,mps3-an547";
}

extern void mpu_init(void);

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
    printk ("Version 1.1.0" " Build date: " __DATE__ "\n");

    extern void overlay_main(void);
    overlay_main();
}