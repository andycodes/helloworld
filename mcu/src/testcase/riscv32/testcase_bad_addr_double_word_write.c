#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void bad_addr_double_word_write(void) {
  volatile uint64_t *buf = (volatile uint64_t *)0x30000000;
  *buf = 0x1122334455667788;
}

void testcase_bad_addr_double_word_write_tc(void)
{
  printk("start %s\n", __func__);
  div_by_zero();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_bad_addr_double_word_write_tc, "testcase_bad_addr_double_word_write", RT_NULL, RT_NULL, 2);