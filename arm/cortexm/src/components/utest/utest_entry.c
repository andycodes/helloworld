#include "module.h"
#include "os.h"
#include "io.h"

static int utest_entry(void)
{
    printk("%s\n", __func__);

    extern int utest_init(void);
    utest_init();

    extern void utest_testcase_run(int argc, char** argv);
    utest_testcase_run(1, NULL);

    return 0;
}
device_initcall(utest_entry);