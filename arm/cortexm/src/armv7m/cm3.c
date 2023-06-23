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
    SysTick_Config(ms * (12000000UL / 1000) - 1);
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