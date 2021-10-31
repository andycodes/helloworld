void test_func_print()
{
    easy_printf("%s entry\n", __func__);
}

void test_armv8m_xn()
{
    /* Inject code at 0x30001000 */
    //在0x300001000地址注入代码test_func
typedef void (*test_func_t)(void);
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    test_func_t test_f = (test_func_t )0x30001001;//Thumb指令集，所以函数call的时候地址要加1
    /*  1000041c <test_func>:
        1000041c:   b500        push    {lr}
        1000041e:   4801        ldr r0, [pc, #4]    ; (10000424 <test_func+0x8>)
        10000420:   4780        blx r0
        10000422:   bd00        pop {pc}
        10000424:   100005eb    andne   r0, r0, fp, ror #11 //100005eb是test_func_print的地址
    */
    *temp_addr++ = 0x4801b500;
    *temp_addr++ = 0xbd004780;
    *temp_addr++ = 0x100005eb;
    //使能MPU前可以执行在0x30001000处的test_func
    test_f();
    
    //使能MPU region0：0x30000000 - 0x300010000
    //只读，不可执行，device memory
    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);
    mpu_select_region(mpu, 0);
    mpu_set_region_base(mpu, 0x30000100UL, REGION_NON_SHAREABLE, REGION_RO_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/
    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);
    easy_printf("%s:mpu setup done\n", __func__);
    //使能MPU后不可执行0x30001000的test_func，因此代码执行到这里的时候会触发hardfault
    test_f();
}   
