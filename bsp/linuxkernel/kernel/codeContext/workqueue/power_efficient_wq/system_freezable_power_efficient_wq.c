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

struct d_wk_p {
	int data;
	struct delayed_work dwork;
};
struct d_wk_p t_wk;

void  wq_func1(struct work_struct *data)
{
	struct d_wk_p *di = container_of(data,struct d_wk_p,dwork.work);
	printk("data[%d] \n",di->data);
	queue_delayed_work(system_freezable_power_efficient_wq, &t_wk.dwork,3*HZ);
}

static int wq_init(void)
{
	t_wk.data = 200;
	INIT_DELAYED_WORK(&t_wk.dwork,wq_func1);
	queue_delayed_work(system_freezable_power_efficient_wq, &t_wk.dwork, 0);
	return 0;
}

static void wq_exit(void){}

module_init(wq_init);
module_exit(wq_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");
