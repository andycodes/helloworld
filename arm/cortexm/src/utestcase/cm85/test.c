#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>

rt_err_t helloutc_init(void)
{
    printk("%s\n", __func__);
}

rt_err_t helloutc_cleanup(void)
{
    printk("%s\n", __func__);
}

void helloutc_tc(void)
{
    printk("%s\n", __func__);
}

UTEST_TC_EXPORT(helloutc_tc, "helloutc", helloutc_init, helloutc_cleanup, 2);