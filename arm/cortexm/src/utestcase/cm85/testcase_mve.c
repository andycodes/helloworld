#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM85.h>
#include <core_cm85.h>

rt_err_t testcase_mve_init(void)
{
    printk("%s\n", __func__);
    return 0;
}

rt_err_t testcase_mve_cleanup(void)
{
    printk("%s\n", __func__);
    return 0;
}

void mve_test(void)
{
    int a[] = {1, 1, 1, 1, 1};
    int b[] = {2, 2, 2, 2, 2};
    int c[] = {0, 0, 0, 0, 0};

    for (int i = 0; i < 5; i++){
        c[i] = a[i] + b[i];
    }

    printk("%s\n", __func__);
    for (int i = 0; i < 5; i++){
        printk("%d\n", c[i]);
    }
}

void testcase_mve_tc(void)
{
    mve_test();
    printk("%s\n", __func__);
}

UTEST_TC_EXPORT(testcase_mve_tc, "testcase_mve", 
testcase_mve_init, testcase_mve_cleanup, 2);