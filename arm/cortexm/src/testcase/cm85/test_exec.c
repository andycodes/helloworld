#include "module.h"
#include "os_stdio.h"
#include "io.h"

static int test_exec(void)
{
    printk("%s\n", __func__);
    writel(0x12345678, (volatile void *)0xFFFFABCD);
}
//device_initcall(test_exec);