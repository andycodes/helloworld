
#include "module.h"

extern void task_switch(void);
static int test_os_task_switch(void)
{
    printk("%s\n", __func__);
    task_switch();
}
device_initcall(test_os_task_switch);