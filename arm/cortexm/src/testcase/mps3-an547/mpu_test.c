#include "cmsdk_uart.h"
#include "armv8m_mpu.h"
#include "testcase.h"
#include <stdint.h>

void test_armv8m_mpu_write()
{
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    printk("0x30001000:%x\n", *temp_addr);

    *temp_addr = 0x1;
    printk("0x30001000:%x\n", *temp_addr);

    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);
    mpu_select_region(mpu, 0);
    mpu_set_region_base(mpu, 0x30000000UL, REGION_NON_SHAREABLE, REGION_RO_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/
    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);

    printk("0x30001000:%x\n", *temp_addr);
    *temp_addr = 0x2;
    printk("0x30001000:%x\n", *temp_addr);
    printk("%s:mpu setup done\n", __func__);
}

void test_armv8m_mpu_overlap()
{
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    printk("0x30001000:%x\n", *temp_addr);
    *temp_addr = 0x1;
    printk("0x30001000:%x\n", *temp_addr);

    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);

    mpu_select_region(mpu, 0);
    mpu_set_region_base(mpu, 0x30000000UL, REGION_NON_SHAREABLE, REGION_RW_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/

    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);

    printk("0x30001000:%x\n", *temp_addr);
    *temp_addr = 0x2;
    // can not access now
    printk("0x30001000:%x\n", *temp_addr);
    printk("%s:mpu setup done\n", __func__);
}

void test_armv8m_xn()
{
    /* Inject code at 0x30001000 */
typedef void (*test_func_t)(void);
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    test_func_t test_f = (test_func_t )0x30001001;
    /*  1000041c <test_func>:
        1000041c:   b500        push    {lr}
        1000041e:   4801        ldr r0, [pc, #4]    ; (10000424 <test_func+0x8>)
        10000420:   4780        blx r0
        10000422:   bd00        pop {pc}
        10000424:   100005eb    andne   r0, r0, fp, ror #11
    */
    *temp_addr++ = 0x4801b500;
    *temp_addr++ = 0xbd004780;
    *temp_addr++ = 0x100005eb;
    test_f();

    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);
    mpu_select_region(mpu, 0);
    mpu_set_region_base(mpu, 0x30000100UL, REGION_NON_SHAREABLE, REGION_RO_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/
    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);
    printk("%s:mpu setup done\n", __func__);
    //can not access now
    test_f();
}

apError mpu_test(void)
{
    printk("void mpu_test(void)\n");
    //test_armv8m_mpu_write();
    //test_armv8m_mpu_overlap();
    //test_armv8m_xn();
    return apERR_NONE;
}
