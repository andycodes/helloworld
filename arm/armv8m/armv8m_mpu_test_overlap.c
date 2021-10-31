void test_armv8m_mpu_overlap()
{
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    easy_printf("0x30001000:%x\n", *temp_addr);
    *temp_addr = 0x1;
    easy_printf("0x30001000:%x\n", *temp_addr);

    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);

	//设置region0：0x30000000 - 0x30001FFF
	//可读可写，不可执行，device memory
    mpu_select_region(mpu, 0);
    mpu_set_region_base(mpu, 0x30000000UL, REGION_NON_SHAREABLE, REGION_RW_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/
	//设置region1：0x30001000 - 0x30001FFF
	//可读可写，不可执行，device memory
    mpu_select_region(mpu, 1);
    mpu_set_region_base(mpu, 0x30001000UL, REGION_NON_SHAREABLE, REGION_RW_PRIV_ONLY, REGION_XN);
    mpu_set_region_limit(mpu, 0x30001FFFUL, 1, REGION_EN);
    mpu_set_region_attr(mpu, 0, 1); /*device memory*/
	//打开MPU
    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);
    easy_printf("%s:mpu setup done\n", __func__);
	//打开MPU后，由于0x30001000的地址在region0和region1中重叠了，访问该地址会触发hard fault
	//代码执行到这一句的时候会触发异常
    easy_printf("0x30001000:%x\n", *temp_addr);
    easy_printf("%s done\n", __func__);
}
