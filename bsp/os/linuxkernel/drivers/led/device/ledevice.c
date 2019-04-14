#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>
#include <linux/io.h>

#include <asm/irq.h>


#define S3C2410_GPF 
#define S3C24XX_LEDF_ACTLOW (1<<0)      /* LED is on when GPIO low */
#define S3C24XX_LEDF_TRISTATE   (1<<1)      /* tristate to turn off */


struct s3c24xx_led_platdata {
    unsigned int         gpio;
    unsigned int         flags;

    char            *name;
    char            *def_trigger;
};

static struct s3c24xx_led_platdata smdk_pdata_led4 = {
    .gpio       = S3C2410_GPF(4),
    .flags      = S3C24XX_LEDF_ACTLOW | S3C24XX_LEDF_TRISTATE,
    .name       = "led4",
    .def_trigger    = "timer",
};

static struct platform_device smdk_led4 = {
    .name       = "s3c24xx_led",
    .id     = 0,
    .dev        = {
        .platform_data = &smdk_pdata_led4,
    },
};

/* devices we initialise */

static struct platform_device __initdata *smdk_devs[] = {
    &smdk_led4,
};

static int __init led_init(void)
 {
    platform_add_devices(smdk_devs, ARRAY_SIZE(smdk_devs));
    printk(KERN_ALERT "led_init\n");
    return 0;
 }

static void __exit led_exit(void)
 {
    printk(KERN_ALERT "led_exit\n");
 }

subsys_initcall(led_init);
module_exit(led_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

