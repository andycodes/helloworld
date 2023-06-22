#include "arch.h"
#include "os.h"
#include "task.h"
#include "system_ARMCM55.h"
#include "ARMCM55.h"

extern unsigned int __StackTop;
extern unsigned int __PspTop;


void SysTick_Handler(void)
{
    DEBUG("SysTick_Handler\n");
    task_system_tick_handler();
}

void switch_to_psp(void)
{
    uint32_t ctrl;

    __set_PSP((uint32_t)(&__PspTop));
    ctrl = __get_CONTROL();
    __set_CONTROL(ctrl | CONTROL_SPSEL_Msk); // switch to PSP
}

extern uint32_t _bss;
extern uint32_t _ebss;
static void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}