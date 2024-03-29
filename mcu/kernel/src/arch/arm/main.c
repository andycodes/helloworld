#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"
#include "systick.h"
#include <stdint.h>
#include "arch.h"
#include "task.h"
#include "memblock.h"
#include "timer.h"
#include "mutex.h"
#include "flag_group.h"
#include "lib.h"
#include "kalloc.h"

extern unsigned int __StackTop;
extern unsigned int __PspTop;
extern unsigned int __PspStart[1024 * 2];

#define PLATFORM_SYSTICK    (10 * (12000000UL / 1000) - 1)
unsigned int g_os_startflag = 0;


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

extern uint32_t __data_ldm_start;
extern uint32_t __data_vdm_start;
extern uint32_t __data_vdm__end;
void load_data(void)
{
    char *src = (char *)&__data_ldm_start;
    char *dst = (char *)&__data_vdm_start;

    while (dst <= (char *)&__data_vdm__end) {
        *dst++ = *src++;
    }
}

task_t task1;
task_t task4;
flag_group_t flag_group;

void task1_entry(void *param)
{
    SysTick_Config(10 * (12000000UL / 1000) - 1);
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
    init_task_module();
    timer_module_init();

    task_init(&task1, task1_entry, (void *)0x11111111, 0, &__PspStart[1024]);
    task_init(&task4, task4_entry, (void *)0x44444444, 1, &__PspStart[1024 *2]);
    g_next_task = task_highest_ready();
    task_run_first();
    for(;;);
    return 0;
}

void __PROGRAM_START(void)
{
    load_data();
    clear_bss();
    dfx_init();
    board_init();

    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    printk("%s %x %x %x %x\n", __func__, 
        __data_ldm_start, &__data_ldm_start, __data_vdm_start, &__data_vdm_start);

    kmalloc_init();
    module_init();

    printk("hello RTOS ^-^^-^^-^^-^\n");
    os_main();
}