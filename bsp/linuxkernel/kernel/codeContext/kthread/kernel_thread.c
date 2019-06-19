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
	struct sched_param param = {.sched_priority = 1};
	DECLARE_WAITQUEUE(wait, current);

	sched_setscheduler(current, SCHED_RR, &param);
	add_wait_queue(&apm_waitqueue, &wait);

	set_current_state(TASK_INTERRUPTIBLE);
	while(!kthread_should_stop()) {
		schedule();
		pr_info("test_thread.\n");
		__set_current_state(TASK_INTERRUPTIBLE);
	}

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&apm_waitqueue, &wait);
	return 0;
}

static int thread_test(void *data)
{
	msleep(5000);
	wake_up_interruptible(&apm_waitqueue);
	pr_info("thread_t.\n");
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

	thread_t = kthread_run(thread_test, NULL, "thread_test");
	return 0;
}

 void kthread_exit(void)
{
	//if (task_test) kthread_stop(task_test);
	//if (thread_t) kthread_stop(thread_t);
}

module_init(kernel_thread_init);
module_exit(kthread_exit);
MODULE_LICENSE("Dual BSD/GPL");

