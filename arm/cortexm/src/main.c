#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

extern uint32_t _bss;
extern uint32_t _ebss;

extern uint32_t __data_vdm_start;
extern uint32_t __data_vdm__end;
extern uint32_t __data_ldm_start;

void move_data(void)
{
    char *src = &__data_ldm_start;
    char *dst = &__data_vdm_start;

    while (dst < &__data_vdm__end) {
        *dst++ = *src++;
    }
}

void clear_bss(void)
{
    char *start = &_bss;
    char *dst = &_ebss;
    
    while (start < dst) {
        *start = 0;
        start++;
    }
}

void __PROGRAM_START(void)
{
    move_data();
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    module_init();
}
