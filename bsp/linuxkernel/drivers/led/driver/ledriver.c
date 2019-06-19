#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/module.h>

/*LED*/
#define S3C2410_GPF 
#define S3C24XX_LEDF_ACTLOW (1<<0)      /* LED is on when GPIO low */
#define S3C24XX_LEDF_TRISTATE   (1<<1)      /* tristate to turn off */

struct s3c24xx_led_platdata {
    unsigned int         gpio;
    unsigned int         flags;

    char            *name;
    char            *def_trigger;
};

struct s3c24xx_gpio_led {
    struct led_classdev      cdev;
    struct s3c24xx_led_platdata *pdata;
};

static inline struct s3c24xx_gpio_led *pdev_to_gpio(struct platform_device *dev)
{
    return platform_get_drvdata(dev);
}

static inline struct s3c24xx_gpio_led *to_gpio(struct led_classdev *led_cdev)
{
    return container_of(led_cdev, struct s3c24xx_gpio_led, cdev);
}

static void s3c24xx_led_set(struct led_classdev *led_cdev,
                enum led_brightness value)
{
    struct s3c24xx_gpio_led *led = to_gpio(led_cdev);
    struct s3c24xx_led_platdata *pd = led->pdata;
    int state = (value ? 1 : 0) ^ (pd->flags & S3C24XX_LEDF_ACTLOW);

    /* there will be a short delay between setting the output and
     * going from output to input when using tristate. */

    gpio_set_value(pd->gpio, state);

    if (pd->flags & S3C24XX_LEDF_TRISTATE) {
        if (value)
            gpio_direction_output(pd->gpio, state);
        else
            gpio_direction_input(pd->gpio);
    }
}

static int s3c24xx_led_probe(struct platform_device *dev)
{
    struct s3c24xx_led_platdata *pdata = dev->dev.platform_data;
    struct s3c24xx_gpio_led *led;
    int ret;
    
    printk(KERN_ALERT "platform start!\n");
    
    led = devm_kzalloc(&dev->dev, sizeof(struct s3c24xx_gpio_led),
               GFP_KERNEL);
    if (led == NULL) {
        dev_err(&dev->dev, "No memory for device\n");
        return -ENOMEM;
    }

    platform_set_drvdata(dev, led);

    led->cdev.brightness_set = s3c24xx_led_set;
    led->cdev.default_trigger = pdata->def_trigger;
    led->cdev.name = pdata->name;
    led->cdev.flags |= LED_CORE_SUSPENDRESUME;

    led->pdata = pdata;

    //ret = devm_gpio_request(&dev->dev, pdata->gpio, "S3C24XX_LED");
    if (ret < 0)
        return ret;

    /* no point in having a pull-up if we are always driving */

    //s3c_gpio_setpull(pdata->gpio, S3C_GPIO_PULL_NONE);

    if (pdata->flags & S3C24XX_LEDF_TRISTATE)
        gpio_direction_input(pdata->gpio);
    else
        gpio_direction_output(pdata->gpio,
            pdata->flags & S3C24XX_LEDF_ACTLOW ? 1 : 0);

    /* register our new led device */

    ret = led_classdev_register(&dev->dev, &led->cdev);
    if (ret < 0)
        dev_err(&dev->dev, "led_classdev_register failed\n");

    return ret;
}

static int s3c24xx_led_remove(struct platform_device *dev)
{
    struct s3c24xx_gpio_led *led = pdev_to_gpio(dev);
    printk(KERN_ALERT "Goodbye, cruel world\n");
    led_classdev_unregister(&led->cdev);

    return 0;
}

static struct platform_driver s3c24xx_led_driver = {
    .probe      = s3c24xx_led_probe,
    .remove     = s3c24xx_led_remove,
    .driver     = {
        .name       = "s3c24xx_led",
        .owner      = THIS_MODULE,
    },
};

static int __init hello_init(void)
 {
    return platform_driver_register(&s3c24xx_led_driver);
 }

static void __exit hello_exit(void)
 {
    platform_driver_unregister(&s3c24xx_led_driver);
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fudan_abc");
MODULE_DESCRIPTION("S3C24XX LED driver");

