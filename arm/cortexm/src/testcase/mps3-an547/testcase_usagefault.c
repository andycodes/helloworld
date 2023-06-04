#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>

void div_by_zero( void )
{
  volatile unsigned int a, b, c;

  a = 1;
  b = 0;
  c = a / b;

  printk("c is %u\n", c);
}  

void testcase_usagefault_tc(void)
{
  printk("start %s\n", __func__);
  div_by_zero();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_usagefault_tc, "testcase_usagefault", RT_NULL, RT_NULL, 2);