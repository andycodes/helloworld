#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>

uint32_t read_from_bad_address(void) {
  return *(volatile uint32_t *)0xbadcafe;
}

void testcase_read_from_bad_address_tc(void)
{
  printk("start %s\n", __func__);
  read_from_bad_address();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_read_from_bad_address_tc, "testcase_read_from_bad_address", RT_NULL, RT_NULL, 2);