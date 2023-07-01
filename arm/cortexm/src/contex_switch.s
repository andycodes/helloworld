.text
.code 16
.syntax unified
.global pendsv_handler
.global g_current_task
.global g_next_task
.global g_os_first_switch

pendsv_handler:
    /*CM3 will push the r0-r3, r12, r14, r15, xpsr by hardware*/
    ldr     r1, =g_os_first_switch // r1 = &g_os_first_switch
    ldr     r0, [r1]
    str     r1, [r1]
    cbz     r0, switch_to_thread  //如果R0中的值为0，则说明接下来运行的是第一个任务，所以不需要保存寄存器R4-R11中的内容

    /* g_current_task->psp-- = r11;
     * ...
     * g_current_task->psp-- = r4;
     * g_current_task->stack = psp;
     */
    MRS     R0, PSP  
    stmdb   r0!, {r4-r11}
    ldr     r1, =g_current_task
    ldr     r1, [r1]
    str     r0, [r1]

switch_to_thread:

    /* *g_current_task = *g_next_task */
    ldr     r0, =g_current_task
    ldr     r1, =g_next_task
    ldr     r2, [r1]
    str     r2, [r0]

    /*r0 = g_current_task->stack*/
    ldr     r0, [r2]
    ldmia   r0!, {r4-r11}

    msr     psp, r0
    orr     lr, lr, #0x04   /*Swtich to PSP*/
    bx      lr
