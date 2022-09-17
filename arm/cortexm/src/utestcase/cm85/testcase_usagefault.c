#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM85.h>
#include <core_cm85.h>


rt_err_t testcase_usagefault_init(void)
{
    printk("%s\n", __func__);
}

rt_err_t testcase_usagefault_cleanup(void)
{
    printk("%s\n", __func__);
}

void div_by_zero( void )
{
  volatile unsigned int a, b, c;
  
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
  a = 1;
  b = 0;
  c = a / b;
}  


void testcase_usagefault_tc(void)
{
    div_by_zero();
    printk("%s\n", __func__);
}

UTEST_TC_EXPORT(testcase_usagefault_tc, "testcase_usagefault", 
testcase_usagefault_init, testcase_usagefault_cleanup, 2);