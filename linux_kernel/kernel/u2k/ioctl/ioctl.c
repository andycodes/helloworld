#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/wireless.h>
#include <linux/netdevice.h>
#include <net/iw_handler.h>
#include <net/wext.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>
#pragma pack(1)
typedef struct ioctl_test {
	int a;
	char b;
	long long c;
	char __user *data_addr;
}ioctl_test_t;
#pragma pack()   // »Ö¸´×Ö½Ú¶ÔÆë
static int ioctl_test_open(struct inode *inode, struct file *file)
{
	printk ("[%s]\n", __func__);
	return 0;
}

static long ioctl_ctrl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	ioctl_test_t tt;
	char* data_addr;
	unsigned long funcs = 0;
	switch(cmd) {
	case 0:
		if (get_user(funcs, (unsigned long __user *)arg))
			return -EFAULT;
		funcs++;
		return put_user(funcs, (unsigned long __user *)arg);
	case 1:
		if (copy_from_user(&tt, (void *)arg, sizeof(ioctl_test_t))) {
			pr_err("[%s]copy_from_user err\n", __func__);
			return -EFAULT;
		}
		printk("[%s][%x][%x][%llx]\n", __func__, tt.a, tt.b, tt.c);

		data_addr = memdup_user(tt.data_addr, 8);
		if (IS_ERR(data_addr))
			return PTR_ERR(data_addr);

		printk("data5[%d]\n", *(tt.data_addr + 5));
	break;
	default:
		return -EINVAL;
	}

	return 0;
}

#ifdef CONFIG_COMPAT
static long vsock_dev_compat_ioctl(struct file *filp,
				   unsigned int cmd, unsigned long arg)
{
	printk ("[%s]%lu %u\n", __func__, arg, cmd);
	return ioctl_ctrl(filp, cmd, compat_ptr(arg));
}
#endif

static struct file_operations dev_fops = {
	.owner          = THIS_MODULE,
	.open    =   ioctl_test_open,
	.unlocked_ioctl = ioctl_ctrl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= vsock_dev_compat_ioctl,
#endif
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "ioctrl_test",
    .fops = &dev_fops,
};

static int __init dev_init(void)
{
    int ret = misc_register(&misc);
    printk("\n IOCTRL\n");
    return ret;
}

static void __exit dev_exit(void)
{
    misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");
