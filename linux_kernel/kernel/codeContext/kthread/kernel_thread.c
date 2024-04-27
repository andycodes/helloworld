#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>


#define APM_CHECK_TIMEOUT	(HZ)
static DECLARE_WAIT_QUEUE_HEAD(apm_waitqueue);
struct task_struct *task_test = NULL;
struct task_struct *thread_t = NULL;


/*建议使用 wait_event_interruptible  简单*/
static int test_thread(void *data)
{
	DECLARE_WAITQUEUE(wait, current);

	add_wait_queue(&apm_waitqueue, &wait);

	set_current_state(TASK_INTERRUPTIBLE);
	while(!kthread_should_stop()) {
		schedule();
		pr_info("%s.\n", __func__);
		__set_current_state(TASK_INTERRUPTIBLE);
	}

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&apm_waitqueue, &wait);
	return 0;
}

static int test_run(void *data)
{
	pr_info("%s.\n", __func__);
	msleep(500);
	wake_up_interruptible(&apm_waitqueue);
	return 0;
}

 int kernel_thread_init(void)
{
	int err;
	task_test = kthread_create(test_thread, NULL, "test_task");
	if (IS_ERR(task_test)) {
		printk("Unable to start kernel thread.\n");
		err = PTR_ERR(task_test);
		task_test = NULL;
		return err;
	}

	wake_up_process(task_test);//启动线程



	thread_t = kthread_run(test_run, NULL, "test_run");
	return 0;
}

module_init(kernel_thread_init);
MODULE_LICENSE("Dual BSD/GPL");
