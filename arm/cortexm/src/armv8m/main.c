#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "cmsis_gcc.h"
#include "core_cm55.h"

extern int testcase_task();

extern uint32_t _bss;
extern uint32_t _ebss;
extern void testcase(void);

static inline void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}

void __PROGRAM_START(void)
{
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    testcase();
}
