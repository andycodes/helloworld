#include "arch.h"
#include "os.h"
#include "task.h"
#include "system_ARMCM3.h"
#include "ARMCM3.h"
#include "core_cm3.h"

extern unsigned int _p_StackTop;
extern uint32_t SystemCoreClock;

void init_systick(uint32_t ms)
{
    systick_t *systick_p = (systick_t *)SYSTICK_BASE;
    uint8_t *sys_prio_p = (uint8_t *)SYSTICK_PRIO_REG;
    *sys_prio_p = 0xf0;
    //#define SystemCoreClock     12000000UL
    systick_p->load = ms * (12000000UL / 1000) - 1;
    systick_p->val = 0;
    systick_p->ctrl = 0x7;
}

void systick_handler(void)
{
    /*DEBUG("systick_handler\n");*/
    task_system_tick_handler();
}

void trigger_pend_sv(void)
{
    MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI; /*Set PENDSVC loweset priority*/
    MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET; /*Trigger PendSV*/
}

void switch_to_psp(void)
{
    uint32_t ctrl;

    __set_PSP((uint32_t)(&_p_StackTop));

    ctrl = __get_CONTROL();
    __set_CONTROL(ctrl | CONTROL_SPSEL_Msk); // switch to PSP
}

extern uint32_t _bss;
extern uint32_t _ebss;
void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}

void __PROGRAM_START(void)
{
    switch_to_psp();
    clear_bss();

    (void)main();
}