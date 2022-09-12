#include "module.h"
#include "os.h"
#include "cpu.h"

static void test_cpu(void)
{
    char *cpuinfo = ArchCpuInfo();
    printk("%s \n", cpuinfo);
}

device_initcall(test_cpu);