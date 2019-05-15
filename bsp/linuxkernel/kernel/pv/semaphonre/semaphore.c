#include <linux/init.h> 
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/mutex.h>
 
int num[2][5]={
 
{0,2,4,6,8},
 
{1,3,5,7,9}
 
};
  
struct semaphore first_sem;
struct semaphore second_sem;
 
int thread_fist(void *p)
{
    int i; 
    int *num=(int *)p;
    for(i=0;i<5;i++) 
    {
        down(&first_sem);
        printk("hello world %d\n",num[i]);
        up(&second_sem);
    }
    
    return 0;
}
  
int thread_second(void *p)
{
    int i;
    int *num=(int *)p;
    for(i=0;i<5;i++)
    { 
        down(&second_sem);
        printk("hello fansaihua %d\n",num[i]); 
        up(&first_sem);
    }
    
    return 0;
}
  
static int __init test_init(void)
{
    printk("enter the test_init\n");
    // init_MUTEX(&first_sem);//初始化为1打开信号量
    sema_init(&first_sem, 1); 
    //  init_MUTEX_LOCKED(&second_sem);//初始化为0 将该信号量锁住
    sema_init(&second_sem, 0); 
    kernel_thread(thread_fist,num[0],CLONE_KERNEL); 
    kernel_thread(thread_second,num[1],CLONE_KERNEL);  
    return 0;
}
 
static void __exit test_exit(void)
{ 
    printk("enter the test_exit\n");
} 
 
module_init(test_init);
module_exit(test_exit);
 
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("FANSAIHUA");
MODULE_DESCRIPTION("for semaphore test");

