#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

#define DEVICE_NAME "misc"

static long misc_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk(KERN_ALERT "misc_unlocked_ioctl!\n");
    return 0;
}

static struct file_operations dev_fops = {
	.owner			= THIS_MODULE,
	.unlocked_ioctl	= misc_unlocked_ioctl,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init misc_init(void)
{
	int ret = misc_register(&misc);
	printk(KERN_ALERT "misc_init!\n");
	return ret;
}

static void __exit misc_exit(void)
{
	misc_deregister(&misc);
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

