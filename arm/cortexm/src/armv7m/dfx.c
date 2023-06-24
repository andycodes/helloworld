#include <stdint.h>
#include "uart.h"
#include "ARMCM3.h"

void debugHardfault(unsigned int *sp)
{
    unsigned int cfsr  = SCB->CFSR;
    unsigned int hfsr  = SCB->HFSR;
    unsigned int mmfar = SCB->MMFAR;
    unsigned int bfar  = SCB->BFAR;

    unsigned int r0  = sp[0];
    unsigned int r1  = sp[1];
    unsigned int r2  = sp[2];
    unsigned int r3  = sp[3];
    unsigned int r12 = sp[4];
    unsigned int lr  = sp[5];
    unsigned int pc  = sp[6];
    unsigned int psr = sp[7];

    printk("HardFault:\n");
    printk("SCB->CFSR   0x%08lx\n", cfsr);
    printk("SCB->HFSR   0x%08lx\n", hfsr);
    printk("SCB->MMFAR  0x%08lx\n", mmfar);
    printk("SCB->BFAR   0x%08lx\n", bfar);
    printk("\n");

    printk("SP          0x%08lx\n", (unsigned int)sp);
    printk("R0          0x%08lx\n", r0);
    printk("R1          0x%08lx\n", r1);
    printk("R2          0x%08lx\n", r2);
    printk("R3          0x%08lx\n", r3);
    printk("R12         0x%08lx\n", r12);
    printk("LR          0x%08lx\n", lr);
    printk("PC          0x%08lx\n", pc);
    printk("PSR         0x%08lx\n", psr);

    while(1);
}

__attribute__( (naked) )
void HardFault_Handler(void)
{
#if 0
    __asm volatile
    (
        "tst lr, #4                                    \n"
        "ite eq                                        \n"
        "mrseq r0, msp                                 \n"
        "mrsne r0, psp                                 \n"
        "ldr r1, debugHardfault_address                \n"
        "bx r1                                         \n"
        "debugHardfault_address: .word debugHardfault  \n"
    );
#endif
printk("HardFault:\n");
 while(1);
}

void dfx_init(void)
{
    SCB->SHCSR |=  SCB_SHCSR_USGFAULTENA_Msk
    | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk | 
                SCB_CCR_DIV_0_TRP_Msk |
                SCB_CCR_BFHFNMIGN_Msk;
}