#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/mutex.h>
#include <linux/miscdevice.h>

static int global_var = 0;
static struct semaphore sem;
static wait_queue_head_t outq;
static int flag = 0;

static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
/*wait_event_interruptible(queue,condition);当condition为真时，
唤醒 等待队列上的进程，否则继续堵塞。
(不能直接的立即唤醒进程，而是由调度程序转换上下文，调整为可运行状态)
这种情况下能被信号打断
*/
	if(wait_event_interruptible(outq, flag != 0))
		return - ERESTARTSYS;

	if(down_interruptible(&sem))
		return - ERESTARTSYS;

	flag = 0;
	if(copy_to_user(buf, &global_var, sizeof(int))) {
		up(&sem);
		return - EFAULT;
	}

	up(&sem);
	return sizeof(int);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len,loff_t *off)
{
	if(down_interruptible(&sem))
		return - ERESTARTSYS;

	if(copy_from_user(&global_var, buf, sizeof(int))) {
		up(&sem);
		return - EFAULT;
	}

	up(&sem);
	flag = 1;
/*唤醒处于TASK_INTERRUPTIBLE的等待进程。*/
	wake_up_interruptible(&outq);
	return sizeof(int);
}


struct file_operations globalvar_fops =
{
	read: globalvar_read,
	write: globalvar_write,
};

#define DEVICE_NAME "waitq"
static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,/*/dev/waitq*/
	.fops = &globalvar_fops,
};

static int __init globalvar_init(void)
{
	int ret = misc_register(&misc);
	if (ret) {
		pr_err("[%s]misc_register failure\n", __func__);
		return -1;
	}

	printk("globalvar register success\n");
	sema_init(&sem, 1);
	init_waitqueue_head(&outq);
	return ret;
}

static void __exit globalvar_exit(void)
{
	misc_deregister(&misc);
}

module_init(globalvar_init);
module_exit(globalvar_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");


