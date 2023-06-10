#include "board.h"
#include "lib.h"
#include "module.h"
#include "os.h"

int g_oly1_cnt = 10;

void overlay_function2()
{
    printk("Written by overlay_function2 %d \n", g_oly1_cnt);
}
