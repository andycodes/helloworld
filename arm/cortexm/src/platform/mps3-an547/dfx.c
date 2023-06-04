#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
#include "ARMCM55.h"

typedef struct __attribute__((packed)) ContextStateFrame {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t return_address;
  uint32_t xpsr;
} sContextStateFrame;

#define HARDFAULT_HANDLING_ASM(_x)               \
  __asm volatile(                                \
      "tst lr, #4 \n"                            \
      "ite eq \n"                                \
      "mrseq r0, msp \n"                         \
      "mrsne r0, psp \n"                         \
      "b my_fault_handler_c \n"                  \
                                                 )




//CMB_USING_OS_PLATFORM
#if 0
void dump_stack(void)
{
    if (stack_pointer < stack_start_addr || stack_pointer > stack_start_addr + stack_size) {
        stack_is_overflow = true;
    }

    if (stack_is_overflow) {
        if ((uint32_t) stack_pointer < stack_start_addr) {
            stack_pointer = (uint32_t *) stack_start_addr;
        } else if ((uint32_t) stack_pointer > stack_start_addr + stack_size) {
            stack_pointer = (uint32_t *) (stack_start_addr + stack_size);
        }        
    }
    
    for (; (uint32_t) stack_pointer < stack_start_addr + stack_size; stack_pointer++) {
        cmb_println("  addr: %08x    data: %08x", stack_pointer, *stack_pointer);
    }    
}


void recover(void)
{
  // Clear any logged faults from the CFSR
  *cfsr |= *cfsr;
  // the instruction we will return to when we exit from the exception
  frame->return_address = (uint32_t)recover_from_task_fault;
  // the function we are returning to should never branch
  // so set lr to a pattern that would fault if it did
  frame->lr = 0xdeadbeef;
  // reset the psr state and only leave the
  // "thumb instruction interworking" bit set
  frame->xpsr = (1 << 24);
}
#endif
void printBusFaultErrorMsg(uint32_t CFSRValue)
{
   printk("Bus fault: ");
   CFSRValue = ((CFSRValue & 0x0000FF00) >> 8); // mask and right shift to lsb
}

void printMemoryManagementErrorMsg(uint32_t CFSRValue)
{
   printk("Memory Management fault: ");
   CFSRValue &= 0x000000FF; // mask just mem faults
}

void debugHardfault(unsigned int *sp)
{
    unsigned int cfsr  = SCB->CFSR;
    unsigned int hfsr  = SCB->HFSR;
    unsigned int mmfar = SCB->MMFAR;
    unsigned int bfar  = SCB->BFAR;
    unsigned int dfsr  = SCB->DFSR;    
    unsigned int afsr  = SCB->AFSR;    

    unsigned int r0  = sp[0];
    unsigned int r1  = sp[1];
    unsigned int r2  = sp[2];
    unsigned int r3  = sp[3];
    unsigned int r12 = sp[4];
    unsigned int lr  = sp[5];
    unsigned int pc  = sp[6];
    unsigned int psr = sp[7];

    printk("HardFault:\n");
    printk("SCB->HFSR   0x%08lx\n", hfsr);
    printk("SCB->CFSR   0x%08lx\n", cfsr);
    printk("SCB->MMFAR  0x%08lx\n", mmfar);
    printk("SCB->BFAR   0x%08lx\n", bfar);
    printk("SCB->DFSR   0x%08lx\n", dfsr);
    printk("SCB->AFSR   0x%08lx\n", afsr);

    printk("\n");

    if ((SCB->HFSR & (1 << 30)) != 0) { 
        printk("Forced Hard Fault\n");
    }

    if((SCB->CFSR & 0xFFFF0000) != 0) {
        unsigned int CFSRValue = SCB->CFSR >>= 16;
        printk("UFSR Fault:");

        if((CFSRValue & (1 << 9)) != 0) {
            printk("Divide by zero\n");
        }
    }

    if((SCB->CFSR & 0xFF00) != 0) {
        printBusFaultErrorMsg(SCB->CFSR);
    }
    if((SCB->CFSR & 0xFF) != 0) {
        printMemoryManagementErrorMsg(SCB->CFSR);
    }   

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

//__attribute__((optimize("O0")))
__attribute__( (naked) )
void HardFault_Handler(void)
{
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
}