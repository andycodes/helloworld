#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void access_disabled_coprocessor(void) {
  // FreeRTOS will automatically enable the FPU co-processor.
  // Let's disable it for the purposes of this example
  __asm volatile(
      "ldr r0, =0xE000ED88 \n"
      "mov r1, #0 \n"
      "str r1, [r0]	\n"
      "dsb \n"
      "vmov r0, s0 \n"
      );
}

void testcase_access_disabled_coprocessorc(void)
{
  printk("start %s\n", __func__);
  access_disabled_coprocessor();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_access_disabled_coprocessorc, "testcase_read_from_bad_address", RT_NULL, RT_NULL, 2);