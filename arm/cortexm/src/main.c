#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

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
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    module_init();
}
