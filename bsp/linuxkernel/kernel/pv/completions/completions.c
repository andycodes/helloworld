#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sem.h>
#include <linux/kthread.h>
#include <linux/jiffies.h>


struct completion my_completion1;
struct completion my_completion2;//定义了两个完成量

static struct task_struct * task_one = NULL;
static struct task_struct * task_two = NULL;


int thread_one(void *p)
{
	unsigned long timeleft;
	pr_err("DRIVER:I AM WAITING FOR SALEMAN CLOSED THE DOOR\n");
	reinit_completion(&my_completion1);
	timeleft = wait_for_completion_timeout(&my_completion1,msecs_to_jiffies(200));
	if (!timeleft) {
		pr_err("[%s]wait_for_completion_timeout\n", __func__);
	}

	pr_err("DRIVER:OK , LET'S GO!NOW~\n");
	pr_err("DRIVER:ARRIVE THE STATION.STOPED CAR!\n");
	complete(&my_completion2);//唤醒完成量completion2

	return 0;
 }

 int thread_two(void *p)
{
	if (!completion_done(&my_completion1)) {
		complete(&my_completion1);
		pr_err("SALEMAN:YOU CAN GO NOW!\n");
	}

	reinit_completion(&my_completion2);
	wait_for_completion(&my_completion2);//等待完成量completion2
	pr_err("SALEMAN:OK,THE DOOR BE OPENED!\n");
	return 0;
 }

 static int hello_init(void)
 {
	int err;
	init_completion(&my_completion1);
	init_completion(&my_completion2);

	task_one = kthread_create(thread_one, NULL, "task_one");
	if (IS_ERR(task_one)){
		pr_err("[%s]Unable to start kernel task_one.\n", __func__);
		err = PTR_ERR(task_one);
		task_one = NULL;
		return err;
	}

	task_two = kthread_create(thread_two, NULL, "task_two");
	if (IS_ERR(task_two)){
		pr_err("[%s]Unable to start kernel task_two.\n", __func__);
		err = PTR_ERR(task_two);
		task_two = NULL;
		return err;
	}

	wake_up_process(task_one);//启动线程
	wake_up_process(task_two);

	return 0;
 }

 static void hello_exit(void)
{
	if(task_one)kthread_stop(task_one);
	if(task_two)kthread_stop(task_two);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_AUTHOR("FANSAIHUA");
MODULE_DESCRIPTION("A simple completion Module");
MODULE_LICENSE("Dual BSD/GPL");

