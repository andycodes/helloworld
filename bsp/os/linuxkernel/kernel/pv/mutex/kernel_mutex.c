#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/mutex.h>

static struct task_struct * task_test0 = NULL;
static struct task_struct * task_test1 = NULL;
struct mutex test_mutex;


int test_thread0(void *data)
{
	printk("thread0 start....\n");
	while(1){
		printk("thread0 ....\n");
		/*If mutex is available,
		mutex_trylock will return successfully with mutex locked.
		If mutex is already locked, mutex_trylock immediately
		returns EBUSY to the caller without acquiring mutex or blocking. */
		if (!mutex_trylock(&test_mutex))
		{
		return -EBUSY;
		}

		/*do what you want ...*/

		mutex_unlock(&test_mutex);

		msleep(1000);
	}

	return 0;
}

static DEFINE_MUTEX(qat_cfg_read_lock);
int test_thread1(void *data)
{
	printk("thread1 start....\n");
	while(1){
		mutex_lock(&qat_cfg_read_lock);
		printk("[%s]start....\n", __func__);
/*The same thread cannot obtain the same mutext lock again!!!!!*/
		mutex_lock(&qat_cfg_read_lock);
		printk("[%s]second\n", __func__);
		msleep(1000);
		mutex_unlock(&qat_cfg_read_lock);
	}

	return 0;
}


 int kernel_mutex_init(void)
{
    int err;

    task_test0 = kthread_create(test_thread0, NULL, "test_task0");
    if (IS_ERR(task_test0)){
        printk("Unable to start kernel thread0.\n");
        err = PTR_ERR(task_test0);
        task_test0 = NULL;
        return err;
    }

    task_test1 = kthread_create(test_thread1, NULL, "test_task1");
    if (IS_ERR(task_test1)){
        printk("Unable to start kernel thread1.\n");
        err = PTR_ERR(task_test1);
        task_test1 = NULL;
        return err;
    }

    wake_up_process(task_test0);//启动线程
    wake_up_process(task_test1);//启动线程

    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

 void kernel_mutex_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
    if (task_test0) kthread_stop(task_test0);
    if (task_test1) kthread_stop(task_test1);
}

module_init(kernel_mutex_init);
module_exit(kernel_mutex_exit);
MODULE_LICENSE("Dual BSD/GPL");

