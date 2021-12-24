
#include "module.h"

static int test_os(void)
{
    printk("fansaihua init %s\n", __func__);
    return 0;
}

device_initcall(test_os);