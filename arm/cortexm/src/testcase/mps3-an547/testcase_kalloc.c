#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>
#include "kalloc.h"

void testcase_kalloc_tc(void)
{
  printk("start %s\n", __func__);

void*  memory1 =  kalloc();
void*  memory2 =  kalloc();

  printk("memory  0x%x 0x%x\n", memory1, memory2);

  kfree(memory1);
  kfree(memory2);
}

UTEST_TC_EXPORT(testcase_kalloc_tc, "testcase_kalloc_tc", RT_NULL, RT_NULL, 2);
