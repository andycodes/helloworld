#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "cmsis_gcc.h"
#include "lib.h"

void __PROGRAM_START(void)
{
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    testcase();
}
