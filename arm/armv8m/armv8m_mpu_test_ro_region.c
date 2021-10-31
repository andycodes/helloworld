//测试MPU是否关闭region写权限
void test_armv8m_mpu_write()
{
    volatile uint32_t *temp_addr = (volatile uint32_t *)0x30001000UL;
    //关闭MPU前可以在Memory进行读写
    easy_printf("0x30001000:%x\n", *temp_addr);
    *temp_addr = 0x1;
    easy_printf("0x30001000:%x\n", *temp_addr);

    armv8m_mpu_t *mpu = (armv8m_mpu_t *)0xE000ED90;
    mpu_disable(mpu);	//关闭MPU
    mpu_select_region(mpu, 0);	//设置region0
    //设置region0基地址0x30000000，只读不可执行
    mpu_set_region_base(mpu, 0x30000000UL, REGION_NON_SHAREABLE, REGION_RO_PRIV_ONLY, REGION_XN); 
    //设置region0上限为0x30001FFFF， region0使用attr0，并且使能region
    mpu_set_region_limit(mpu, 0x30001FFFUL, 0, REGION_EN);
    //设置region0属性为device memory
    mpu_set_region_attr(mpu, 0, 0); /*device memory*/
    //打开MPU
    mpu_hfnmiena_disable(mpu);
    mpu_privdefena_enable(mpu);
    mpu_enable(mpu);
    easy_printf("%s:mpu setup done\n", __func__);
	//打开MPU后测试是否具有写权限
    easy_printf("0x30001000:%x\n", *temp_addr);
    //程序执行到这会触发hard fault
    *temp_addr = 0x2;
    easy_printf("0x30001000:%x\n", *temp_addr);
    easy_printf("%s done\n", __func__);
}
