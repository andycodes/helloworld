#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"
#include "os.h"
#include <stdint.h>
#include "arch.h"
#include "task.h"
#include "os.h"
#include "memblock.h"
#include "timer.h"
#include "mutex.h"
#include "flag_group.h"
#include "lib.h"

extern unsigned int __StackTop;
extern unsigned int __PspTop;


void switch_to_psp(void)
{
    uint32_t ctrl;

    __set_PSP((uint32_t)(&__PspTop));
    ctrl = __get_CONTROL();
    __set_CONTROL(ctrl | CONTROL_SPSEL_Msk); // switch to PSP
}

extern uint32_t _bss;
extern uint32_t _ebss;

void clear_bss(void)
{
    char *start = (char *)&_bss;
    char *dst = (char *)&_ebss;
    
    while (start < dst) {
        *start = 0;
        start++;
    }
}


extern unsigned int __StackTop;
extern unsigned int __PspTop;

task_t task1;
task_t task2;
task_t task3;
task_t task4;
task_stack_t task1_stk[2048];
//task_stack_t task2_stk[1024];
//task_stack_t task3_stk[1024];
task_stack_t task4_stk[2048];

flag_group_t flag_group;

void task1_entry(void *param)
{
    SysTick_Config(100 * (12000000UL / 1000) - 1);
    flag_group_init(&flag_group, 0xff);
    for(;;) {
        printk("%s\n", __func__);
        task_delay_s(1);
        flag_group_notify(&flag_group, 0, 0x6);
    }
}

void task2_entry(void *param)
{
    uint32_t result_flags = 0;
    for(;;) {
        flag_group_wait(&flag_group, FLAGGROUP_CLEAR_ALL | FLAGGROUP_CONSUME, 0x4, &result_flags, 2000);
        printk("%s\n", __func__);
    }
}

void task3_entry(void *param)
{
    for(;;) {
        printk("%s\n", __func__);
        task_delay_s(1);
    }

}

void task4_entry(void *param)
{
    for(;;) {
        printk("%s\n", __func__);
        task_delay_s(1);
    }
}


int os_main(void)
{
    DEBUG("Hello FAN RTOS \n");

    DEBUG("psp msp:0x%x, 0x%x\n", &__PspTop, &__StackTop);
    switch_to_psp();
    DEBUG("psp:0x%x\n", __get_PSP());
    DEBUG("msp:0x%x\n", __get_MSP());

    init_task_module();
    timer_module_init();

    task_init(&task1, task1_entry, (void *)0x11111111, 0, &task1_stk[1024]);
//  task_init(&task2, task2_entry, (void *)0x22222222, 1, &task2_stk[1024]);
//  task_init(&task3, task3_entry, (void *)0x33333333, 0, &task3_stk[1024]);
    task_init(&task4, task4_entry, (void *)0x44444444, 1, &task4_stk[1024]);
    g_next_task = task_highest_ready();
    task_run_first();
    for(;;);
    return 0;
}

void __PROGRAM_START(void)
{
    clear_bss();
    dfx_init();
    board_init();

    printk("hello %s ^-^^-^^-^^-^\n", board_info());

    module_init();

    printk("hello RTOS ^-^^-^^-^^-^\n");
    os_main();
}