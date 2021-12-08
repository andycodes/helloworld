#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "cmsis_gcc.h"

extern uint32_t __INITIAL_SP;
extern const char* __StackLimit;

void main(void)
{
    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));

    system_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    testcase();
}
