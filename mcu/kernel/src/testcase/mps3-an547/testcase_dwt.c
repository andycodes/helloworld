#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>


void tc_dwt(void)
{
  dwt_init();
  uint32_t cnt = dwt_get();
  printk("tc_dwt 0x%x ", cnt);
  cnt = dwt_get();
  printk("tc_dwt 0x%x ", cnt); 
}

UTEST_TC_EXPORT(tc_dwt, "tc_dwt", RT_NULL, RT_NULL, 0);