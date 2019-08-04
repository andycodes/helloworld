#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sem.h>
#include <linux/kthread.h> 
#include <linux/jiffies.h>

 
struct completion my_completion1;
struct completion my_completion2;//���������������

static struct task_struct * task_one = NULL;
static struct task_struct * task_two = NULL;

 
int thread_one(void *p)
{
	unsigned long timeleft;
	printk(KERN_ALERT"DRIVER:I AM WAITING FOR SALEMAN CLOSED THE DOOR\n");
	//wait_for_completion(&my_completion1);//�ȴ������completion1
	reinit_completion(&my_completion1);
	timeleft = wait_for_completion_timeout(&my_completion1,msecs_to_jiffies(20));
	if (!timeleft) {
		pr_err("[%s]wait_for_completion_timeout\n", __func__);
		return -1;
	}

	printk(KERN_ALERT"DRIVER:OK , LET'S GO!NOW~\n");
	printk(KERN_ALERT"DRIVER:ARRIVE THE STATION.STOPED CAR!\n");
	complete(&my_completion2);//���������completion2

	return 0;
 }

 int thread_two(void *p)
{
	printk(KERN_ALERT"SALEMAN:THE DOOR IS CLOSED!\n");
	complete(&my_completion1);//���������completion1
	printk(KERN_ALERT"SALEMAN:YOU CAN GO NOW!\n");
	reinit_completion(&my_completion2);
	wait_for_completion(&my_completion2);//�ȴ������completion2
	printk(KERN_ALERT"SALEMAN:OK,THE DOOR BE OPENED!\n");
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

	wake_up_process(task_one);//�����߳�
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

