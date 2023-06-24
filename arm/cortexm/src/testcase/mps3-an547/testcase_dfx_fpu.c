#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void tc_dfx_fpu(void)
{
    volatile float  a, b;
    volatile double x, y;

  printk("%s\n", __func__);

    a = b = 1.0e30f;
    a *= b; /* overflow; will be wrapped to a moderate number */
    printk("%g\n", a);
    a /= b;
    printk("%g\n", a);
    a /= b; /* underflow; will wrap back */
    printk("%g\n", a);
    x = y = 1.0e300;
    x *= y; /* overflow; will be wrapped to a moderate number */
    printk("%g\n", x);
    x /= y;
    printk("%g\n", x);
    x /= y; /* underflow; will wrap back */
    printk("%g\n", x);
}

UTEST_TC_EXPORT(tc_dfx_fpu, "tc_dfx_fpu", RT_NULL, RT_NULL, 0);