#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mfd/core.h>
#include <linux/slab.h>

#define PM800_IRQ_RTC  11

static struct resource rtc_resources[] = {
	{
	 .name = "88pm80x-rtc",
	 .start = PM800_IRQ_RTC,
	 .end = PM800_IRQ_RTC,
	 .flags = IORESOURCE_IRQ,
	 },
};

static struct mfd_cell rtc_devs[] = {
	{
	 .name = "88pm80x-rtc",
	 .num_resources = ARRAY_SIZE(rtc_resources),
	 .resources = &rtc_resources[0],
	 .id = -1,
	 },
};


static int __init mfd_init(void)
 {
	mfd_add_devices(NULL, &rtc_devs[0],
			    ARRAY_SIZE(rtc_devs), &rtc_resources[0], 0,
			    NULL);


    printk(KERN_ALERT "mfd_init\n");
 	return 0;
 }

static void __exit mfd_exit(void)
 {
 	printk(KERN_ALERT "mfd_exit\n");
 }

subsys_initcall(mfd_init);
module_exit(mfd_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

