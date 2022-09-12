#include "module.h"
#include "os.h"
#include "io.h"

void SVC1_Handler(void)
{
    printk("hello %s ^-^^-^^-^^-^\n", __func__);
}


static int test_svc(void)
{
    printk("%s\n", __func__);
    svcall();
}
device_initcall(test_svc);