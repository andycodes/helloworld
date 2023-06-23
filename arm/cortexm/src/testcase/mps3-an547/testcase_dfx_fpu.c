#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void tc_dfx_fpu(void)
{
  printk("%s\n", __func__);

  float a = 3.14;
  float b = a / 0;

  printk(" b %f %s\n", b, __func__);
}

UTEST_TC_EXPORT(tc_dfx_fpu, "tc_dfx_fpu", RT_NULL, RT_NULL, 0);