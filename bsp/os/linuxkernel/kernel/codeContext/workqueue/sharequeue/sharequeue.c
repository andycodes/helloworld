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

static void intr_print(void* data)
{
    int n = 5;
    while(n--)
    {
            printk("FAN SAIHUA\n");
            msleep(10000);
    }
}

/*2种初始化方法*/
#ifdef DYNAMIC_INIT
static struct work_struct works;
#else
/*静态初始化*/
static DECLARE_WORK(works, intr_print);
#endif

static int intr_init(void)
{
#ifdef DYNAMIC_INIT
	INIT_WORK(&works, (void*)intr_print);
#endif

	/*驱动程序调用schedule_work向工作队列递交
	新的工作节点，schedule_work内部会唤
	醒worker_thread内核线程（使之进程状态为可调度）。
	在下一次进程调度时刻，worker_thread被调度执行，
	其主要任务便是调用它所管理工作队列中每个
	工作节点上挂载的函数，调用完毕该工作节点
	会从任务队列中被删除。当所有节点上的函数
	调用完毕，worker_thread继续sleep，直到schedule_work再次
	被某个驱动程序调用。*/
#define WORK_ON_APPOINTMENT_CPU
#ifdef  WORK_ON_APPOINTMENT_CPU
	/* run intr_print on boot cpu */
	/*cpu_online_mask 当前有效CPU*/
	/*在有效的CPU列表中找到的第一个CPU*/
	schedule_work_on(cpumask_first(cpu_online_mask), &works);
#else
	schedule_work(&works);

	/*schedule_delayed_work*/
	/*向工作队列中添加一个任务并延迟执行*/
#endif

	return 0;
}

static void intr_exit(void)
{
	/*当模块被缷载时应该去调用一个
	flash_scheduled_work() 函数，这个函数会使
	等待队列中所有的任务都被执行。*/
}

module_init(intr_init);
module_exit(intr_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");


