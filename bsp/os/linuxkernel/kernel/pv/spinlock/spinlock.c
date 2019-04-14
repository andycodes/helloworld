#include <linux/init.h> 
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/delay.h>

spinlock_t my_lock ;

int thread_fist(void *p)
{
	unsigned long flags;
	while(1) {
		spin_lock_irqsave(&my_lock, flags);
		printk("hello world\n");/* Critical Section code ... */
		spin_unlock_irqrestore(&my_lock, flags);
		msleep(100);
	}
	
	return 0;
}
  
int thread_second(void *p)
{
	unsigned long flags;
	while(1) {
			spin_lock_irqsave(&my_lock, flags);
			printk("thread_second\n");/* Critical Section code ... */
			spin_unlock_irqrestore(&my_lock, flags);
			msleep(100);
	}
	
	return 0;
}
  
static int __init test_init(void)
{
	struct task_struct *task;
	printk("enter the test_init/n");
	spin_lock_init(&my_lock);
	task = kthread_run(thread_fist, NULL, "thread0");
	if (PTR_ERR_OR_ZERO(task))
		return PTR_ERR_OR_ZERO(task);
	task = kthread_run(thread_second, NULL, "thread1");
	return PTR_ERR_OR_ZERO(task);
}
 
static void __exit test_exit(void)
{ 
    printk("enter the test_exit\n");
} 
 
module_init(test_init);
module_exit(test_exit);
 
MODULE_AUTHOR("FANSAIHUA");
MODULE_DESCRIPTION("for semaphore test");
MODULE_LICENSE("Dual BSD/GPL");