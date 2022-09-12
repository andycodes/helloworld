#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

void __PROGRAM_START(void)
{
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    module_init();
}
