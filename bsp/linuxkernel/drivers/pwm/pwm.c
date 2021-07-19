#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/clk.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "pwm" 

#define PWM_IOCTL_SET_FREQ 1 
#define PWM_IOCTL_STOP 0  

/* freq: pclk/50/16/65536 ~ pclk/50/16
 * if pclk = 50MHz, freq is 1Hz to 62500Hz
 * human ear : 20Hz~ 20000Hz
 */
static void PWM_Set_Freq( unsigned long freq )
{
	printk("%s\n", __func__);
}

static void PWM_Stop(void)
{
	printk("%s\n", __func__);
}

static int s3c24xx_pwm_open(struct inode *inode, struct file *file)
{
	printk("%s\n", __func__);
	return 0;
}

static int s3c24xx_pwm_close(struct inode *inode, struct file *file)
{
    PWM_Stop();
    return 0;
}

static long ioctl_ctrl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case PWM_IOCTL_SET_FREQ: 
            if (arg == 0) 
                return -EINVAL; 
            PWM_Set_Freq(arg); 
            break;
        case PWM_IOCTL_STOP: 
            PWM_Stop(); 
            break;
    }
    return 0; 
}

static struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.open = s3c24xx_pwm_open,
	.release = s3c24xx_pwm_close,
	.unlocked_ioctl = ioctl_ctrl,
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &dev_fops,
};

static int __init dev_init(void)
{
    int ret;
    ret = misc_register(&misc); 
    printk (DEVICE_NAME"\tinitialized\n");
    return ret;
}

static void __exit dev_exit(void)
{
    misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
