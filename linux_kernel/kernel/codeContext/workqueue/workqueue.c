#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>

static struct work_struct works;
struct workqueue_struct *wq_test_workqueue;

void  wq_func1(struct work_struct *data)
{
	printk("ENTER wq_func1 ok \n");
}

static int wq_init(void)
{
	spinlock_t my_lock ;
	unsigned long flags;

	/*create_workqueue*/
	/*���ڴ���һ��workqueue���У�
	Ϊϵͳ�е�ÿ��CPU������һ���ں��߳�*/
	wq_test_workqueue = create_workqueue("wq_test");

	/*create_singlethread_workqueue*/
	/*���ڴ���workqueue��ֻ����һ���ں��߳�*/
	if (!wq_test_workqueue) {
		pr_err("wq_test_workqueue create_workqueue failed\n");
		return 0;
	}

	/*�������ڳ�ʼ��һ����������*/
	INIT_WORK(&works, wq_func1);
	/*INIT_DELAYED_WORK  ���Ӻ�ִ��*/

	/*TEST: loss event*/
	spin_lock_init(&my_lock);
	spin_lock_irqsave(&my_lock, flags);
	queue_work(wq_test_workqueue, &works);
	queue_work(wq_test_workqueue, &works);
	spin_unlock_irqrestore(&my_lock, flags);


	/*flush_workqueue*/
	/*��չ��������е���������ʹ��*/

	return 0;
}

static void wq_exit(void)
{
	if (wq_test_workqueue)
		destroy_workqueue(wq_test_workqueue);
}

module_init(wq_init);
module_exit(wq_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");

