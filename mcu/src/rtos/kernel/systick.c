
extern unsigned int g_os_startflag;

unsigned int g_systick_count = 0;

void SysTick_Handler(void)
{
    g_systick_count++;
    //printk("SysTick_Handler\n");
    if (g_os_startflag = 1)
      task_scheduler();
}
