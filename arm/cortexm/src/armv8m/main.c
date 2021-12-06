#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"

void main(void)
{
    system_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    testcase();
}
