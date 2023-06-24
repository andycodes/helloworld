#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>

int illegal_instruction_execution(void) 
{
  //int (*bad_instruction)(void) = (void *)0xE0000000;
  //  int (*bad_instruction)(void) = (void *)0xdeadbeef;
  int (*bad_instruction)(void) = (void *)0;
  return bad_instruction();
}

void tc_illegal_instr_exc(void)
{
  printk("start %s\n", __func__);
  illegal_instruction_execution();
  printk("end %s\n", __func__);
}

UTEST_TC_EXPORT(tc_illegal_instr_exc, "tc_illegal_instr_exc", RT_NULL, RT_NULL, 2);