#include "testcase.h"

extern apError mpu_test(void);
extern apError test_systick(void);
extern apError test_menuconfig(void);
extern apError test_init(void);

Test_t tests[] =
{
    {&mpu_test,          0,  "mpu write  "},
    {&test_systick,          0,  "systick  "},
    {&test_menuconfig,          0,  "test_menuconfig  "},
    {&test_init,          0,  "test_init  "},
};
