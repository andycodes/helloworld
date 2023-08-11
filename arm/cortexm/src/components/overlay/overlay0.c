
#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

int g_oly0_cnt = 9;

void overlay_function1()
{
    printk("Written by overlay_function1 %d\n", g_oly0_cnt);
}
