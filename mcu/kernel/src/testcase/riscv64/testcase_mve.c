#include "os.h"
#include "clib.h"
#include "utest.h"
#include <utest_log.h>
#include <ARMCM55.h>
#include "basic_math_functions.h"

q7_t src_data[] = {-5,-4,-3,-2,-1,1,2,3,4,5};
q7_t des_data[10] = {0};

void tc_mve(void)
{
  arm_clip_q7(src_data, des_data, 0, 10, 10);
  for (int i = 0; i < 10; i++){
    printk("%d ", des_data[i]);
  }
}

UTEST_TC_EXPORT(tc_mve, "tc_mve", RT_NULL, RT_NULL, 0);