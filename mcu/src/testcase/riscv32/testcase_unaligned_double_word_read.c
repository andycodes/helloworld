#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void unaligned_double_word_read(void) {
  extern void *g_unaligned_buffer;
  uint64_t *buf = g_unaligned_buffer;
  *buf = 0x1122334455667788;
}

void testcase_unaligned_double_word_read_tc(void)
{
  printk("start %s\n", __func__);
  unaligned_double_word_read();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_unaligned_double_word_read_tc, "testcase_unaligned_double_word_read", RT_NULL, RT_NULL, 2);