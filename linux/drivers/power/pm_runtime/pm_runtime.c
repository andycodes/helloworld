
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/pm_runtime.h>


static int runtime_pm_probe(struct platform_device *pdev)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_probe!\n");
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	return 0;
}

static int runtime_pm_remove(struct platform_device *pdev)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_remove!\n");
	pm_runtime_disable(&pdev->dev);
	return 0;
}

static int runtime_pm_suspend(struct device *dev)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_suspend!\n");
	return 0;
}

static int runtime_pm_resume(struct device *dev)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_resume!\n");
	return 0;
}

static int runtime_pm_idle(struct device *dev)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_idle\n");
	return 0;
}


static const struct dev_pm_ops runtime_pm_ops = {
	SET_RUNTIME_PM_OPS(runtime_pm_suspend,
					runtime_pm_resume,
					runtime_pm_idle)
};

static void runtime_pm_release(struct device * dev)
{
}

static struct platform_device runtime_device = {
	.name		= "runtime_device",
	.id         = -1,
	.dev        = {
	        .release = runtime_pm_release,
	},
};

static struct platform_driver runtime_driver = {
	.probe		= runtime_pm_probe,
	.remove		= runtime_pm_remove,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "runtime_device",
		.pm	= &runtime_pm_ops,
	},
};

static int runtime_pm_init(void)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_init\n");
	platform_device_register(&runtime_device);
	platform_driver_register(&runtime_driver);
	return 0;
}

static void runtime_pm_exit(void)
{
	printk(KERN_EMERG "runtime_pm: runtime_pm_exit\n");

	platform_driver_unregister(&runtime_driver);
	platform_device_unregister(&runtime_device);
}

module_init(runtime_pm_init);
module_exit(runtime_pm_exit);

