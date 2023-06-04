#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>

int illegal_instruction_execution(void) {
  int (*bad_instruction)(void) = (void *)0xE0000000;
  return bad_instruction();
}

void testcase_illegal_instruction_excution_tc(void)
{
  printk("start %s\n", __func__);
  illegal_instruction_execution();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(testcase_illegal_instruction_excution_tc, "testcase_illegal_instruction_excution", RT_NULL, RT_NULL, 2);