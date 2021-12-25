/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-11     Bernard      first version
 * 2012-01-01     aozima       support context switch load/store FPU register.
 * 2013-06-18     aozima       add restore MSP feature.
 * 2013-06-23     aozima       support lazy stack optimized.
 * 2018-07-24     aozima       enhancement hard fault exception handler.
 */


/*@{*/

.cpu cortex-m33
.syntax unified
.thumb
.text

.equ    SCB_VTOR,           0xE000ED08              /* Vector Table Offset Register */
.equ    NVIC_INT_CTRL,      0xE000ED04              /* interrupt control state register */
.equ    NVIC_SYSPRI2,       0xE000ED20              /* system priority register (2) */
.equ    NVIC_PENDSV_PRI,    0x000000FF              /* PendSV and SysTick priority value (lowest) */
.equ    NVIC_PENDSVSET,     0x10000000              /* value to trigger PendSV exception */

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

    LDR     r2,  =rt_trustzone_current_context      /* r2 = &rt_secure_current_context */
    LDR     r2, [r2]                                /* r2 = *r2 */
    MOV     r3, lr                                  /* r3 = lr */
    MRS     r4, psplim                              /* r4 = psplim */
    MRS     r5, control                             /* r5 = control */
    STMFD   r0!, {r2-r5}                            /* push to thread stack */

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


