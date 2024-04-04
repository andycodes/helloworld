#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>

void testcase_c_tc(void)
{
  printk("%s\n", __func__);
  int a = 10;
  int ar[a];

  for (int i = 0; i < 10; i++) {
    ar[i] = i;
    //printk(" %d ", ar[i]);
  }
  
  printk("%s ar[9]:%d\n", __func__, ar[9]);

}

UTEST_TC_EXPORT(testcase_c_tc, "testcase_c", RT_NULL, RT_NULL, 2);
