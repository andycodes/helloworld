#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"

void main(void)
{
    UartStdOutInit();

    while (1){
        printk("hello %s\n", get_boardinfo());
    };
}
