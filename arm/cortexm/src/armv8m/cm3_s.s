.text
.code 16
.syntax unified
/*Export*/
.global reset_handler
.global _p_stack_top
.global get_psp
.global set_psp
.global get_msp
.global get_control_reg
.global pendsv_handler
.global set_primask
.global get_primask
.global disable_irq
.global enable_irq

/*Import*/
.global g_current_task
.global g_next_task
.global main

get_psp:
    mrs     r0, PSP
    blx     lr

set_psp:
    msr     PSP, r0
    blx     lr

get_msp:
    mrs     r0, MSP
    blx     lr

get_control_reg:
    mrs     r0, CONTROL
    blx     lr


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
