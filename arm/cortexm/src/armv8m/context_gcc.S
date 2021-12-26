.global set_primask
.global get_primask
.global disable_irq
.global enable_irq


/*@{*/

.cpu cortex-m33
.syntax unified
.thumb
.text

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.global rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
.type rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
    MSR     PRIMASK, r0
    BX      LR

.global HardFault_Handler
.type HardFault_Handler, %function
HardFault_Handler:
    /* get current context */
    MRS     r0, msp                                 /* get fault context from handler. */
    TST     lr, #0x04                               /* if(!EXC_RETURN[2]) */
    BEQ     get_sp_done
    MRS     r0, psp                                 /* get fault context from thread. */
get_sp_done:

    STMFD   r0!, {r4 - r11}                         /* push r4 - r11 register */

    MOV     r3, lr                                  /* r3 = lr */
    MRS     r4, psplim                              /* r4 = psplim */
    MRS     r5, control                             /* r5 = control */
    STMFD   r0!, {r3-r5}                            /* push to thread stack */

    STMFD   r0!, {lr}                               /* push exec_return register */

    TST     lr, #0x04                               /* if(!EXC_RETURN[2]) */
    BEQ     update_msp
    MSR     psp, r0                                 /* update stack pointer to PSP. */
    B       update_done
update_msp:
    MSR     msp, r0                                 /* update stack pointer to MSP. */
update_done:

    PUSH    {LR}
    BL      rt_hw_hard_fault_exception
    POP     {LR}

    ORR     lr, lr, #0x04
    BX      lr


get_primask:
    mrs     r0, PRIMASK
    blx     lr

set_primask:
    msr     PRIMASK, r0
    blx     lr

disable_irq:
    cpsid   i
    blx     lr

enable_irq:
    cpsie   i
    blx     lr