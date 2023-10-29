#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
#include "arch.h"
#include "clib.h"
#include "os.h"

struct ContextStateFrame {
    unsigned int r0;
    unsigned int r1;
    unsigned int r2;
    unsigned int r3;
    unsigned int r12;
    unsigned int lr;
    unsigned int returnaddress;
    unsigned int retpsr;
};

/*
# First eight values on stack will always be:
# 0~R3、R12、LR、ReturnAddress、RETPSR
*/

#if 1
void debugHardfault(struct ContextStateFrame *fp)
{
    printk("debugHardfault:\n");
    printk("SCB->HFSR   0x%08lx\n", SCB->HFSR);
    printk("SCB->CFSR   0x%08lx\n", SCB->CFSR);  // UFSR|BFSR|MMFSR
    printk("SCB->MMFAR  0x%08lx\n", SCB->MMFAR);//MemManage Fault Address Register
    printk("SCB->BFAR   0x%08lx\n", SCB->BFAR);
    printk("SCB->DFSR   0x%08lx\n", SCB->DFSR);//调试fault状态寄存器
    printk("SCB->AFSR   0x%08lx\n", SCB->AFSR);//辅助fault状态寄存器

    printk("\n");

    if ((SCB->HFSR & SCB_HFSR_FORCED_Msk) != 0) { 
        printk("Forced Hard Fault\n");
    }

    if((SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk) != 0) {
        printk("UFSR Fault:");
        if((SCB->CFSR & SCB_CFSR_DIVBYZERO_Msk) != 0) {
            printk("Divide by zero\n");
        }
    }

    if((SCB->CFSR & SCB_CFSR_BUSFAULTSR_Msk) != 0) {
        printk("BFSR Bus fault: ");
    }

    if((SCB->CFSR & SCB_CFSR_MEMFAULTSR_Msk) != 0) {
        printk("MMFSR Memory Management fault: ");
    }   

    printk("SP          0x%08lx\n", (unsigned int)fp);
    printk("R0          0x%08lx\n", fp->r0);
    printk("R1          0x%08lx\n", fp->r1);
    printk("R2          0x%08lx\n", fp->r2);
    printk("R3          0x%08lx\n", fp->r3);
    printk("R12         0x%08lx\n", fp->r12);
    printk("LR          0x%08lx\n", fp->lr);
    printk("RETURNADDRESS 0x%08lx\n", fp->returnaddress);
    printk("RETPSR        0x%08lx\n", fp->retpsr);

    /*recovery*/

    SCB->HFSR = SCB->HFSR;
    SCB->CFSR = SCB->CFSR;

    while(1);
}
#else
__attribute__((naked, used))
void debugHardfault(struct ContextStateFrame *fp)
{
    /*recovery*/
    SCB->HFSR = SCB->HFSR;
    SCB->CFSR = SCB->CFSR;

    __asm volatile
    (
        "MRS R0, PSR    \n"
        "ORR  R0,R0, #0x1000000 \n"
        "MSR PSR,R0     \n"
        "bx lr \n"
    );
}
#endif

/*
# psp was active prior to exception if bit 2 is set
# otherwise, the msp was active
*/
__attribute__( (naked) )
void HardFault_Handler(void)
{
    __asm volatile
    (
        "tst lr, #4                                    \n"
        "ite eq                                        \n"
        "mrseq r0, msp                                 \n"
        "mrsne r0, psp                                 \n"
        "b debugHardfault                             \n"
    );
}

void dfx_init(void)
{
    SCB->SHCSR |=  SCB_SHCSR_SECUREFAULTENA_Msk | 
                    SCB_SHCSR_USGFAULTENA_Msk | 
                    SCB_SHCSR_BUSFAULTENA_Msk | 
                    SCB_SHCSR_MEMFAULTENA_Msk;

    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk | 
                SCB_CCR_DIV_0_TRP_Msk |
                SCB_CCR_BFHFNMIGN_Msk;
}