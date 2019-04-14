#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/sys.h>
#include <linux/reboot.h>
#include <linux/kthread.h> 
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>


static struct task_struct * task_test0 = NULL;
static struct task_struct * task_test1 = NULL;

/*初始化 test_atomic_notifier_list*/
ATOMIC_NOTIFIER_HEAD(test_atomic_notifier_list);

EXPORT_SYMBOL(test_atomic_notifier_list);


BLOCKING_NOTIFIER_HEAD(test_blocking_notifier_list);
EXPORT_SYMBOL(test_blocking_notifier_list);


static int myreboot(struct notifier_block *self, unsigned long event, void *data)
{
    printk(KERN_ALERT "Just a test! Event code: %li! System reboot now...", event);
    return NOTIFY_OK;
}

static struct notifier_block myreboot_notifier = {
.notifier_call = myreboot,
};


static int test_atomic(struct notifier_block *this, unsigned long event,
            void *ptr)
{
    printk(KERN_ALERT "Just a test! Event code: 0x%0lx! System test_atomic now...", event);
    return NOTIFY_OK;
}

static struct notifier_block test_atomic_blk = {
    .notifier_call  = test_atomic,
};

static int test_blocking_handler(struct notifier_block *this, unsigned long code, void *x)
{
    printk(KERN_ALERT "Just a test! Event code: 0x%0lx! System test_blocking now...", code);
    return NOTIFY_OK;
}

static struct notifier_block test_blocking_blk = {
    .notifier_call  = test_blocking_handler,
};

int test_thread0(void *data)
{
    static char buf[1024];
    printk("thread0 start....\n");
    msleep(1000);/*等待注册完成*/
    atomic_notifier_call_chain(&test_atomic_notifier_list,0x5555,buf);
    msleep(100);
/*返回值
    *NOTIFY_DONE 0x0000 对该事件不感兴趣（根据unsigned long参数）
NOTIFY_OK 0x0001 成功响应该事件
NOTIFY_STOP_MASK 0x8000 该回调函数返回后停止处理后续notifier block
NOTIFY_BAD (NOTIFY_STOP_MASK|0x0002)
出错，回调函数返回后停止处理后续notifier block
NOTIFY_STOP (NOTIFY_OK|NOTIFY_STOP_MASK)
成功响应事件，回调函数返回后停止处理后续notifier block
注意，NOTIFY_STOP和NOTIFY_BAD的定义都包含了NOTIFY_STOP_MASK。
**/
    blocking_notifier_call_chain(&test_blocking_notifier_list,0xaaaa,buf);

    return 0;
}

int test_thread1(void *data)
{
    printk("thread1 start....\n");

     /*注册 重启之前触发事件*/
    register_reboot_notifier(&myreboot_notifier);

    /*注册atomic事件*/
    atomic_notifier_chain_register(&test_atomic_notifier_list, &test_atomic_blk);

     /*注册blocking事件*/
    blocking_notifier_chain_register(&test_blocking_notifier_list,&test_blocking_blk);
    
     return 0;
}

static int myreboot_init(void)
{
    int err;
   task_test0 = kthread_create(test_thread0, NULL, "test_task0");

    if (IS_ERR(task_test0))
    {
        printk("Unable to start kernel thread0.\n");
        err = PTR_ERR(task_test0);
        task_test0 = NULL;
        return err;
    }

    task_test1 = kthread_create(test_thread1, NULL, "test_task1");

    if (IS_ERR(task_test1))
    {
        printk("Unable to start kernel thread1.\n");
        err = PTR_ERR(task_test1);
        task_test1 = NULL;
        return err;
    }
    
    wake_up_process(task_test0);//启动线程
    wake_up_process(task_test1);//启动线程
    
    return 0;
}

static void myreboot_exit(void)
{
    unregister_reboot_notifier(&myreboot_notifier);

    atomic_notifier_chain_unregister(&test_atomic_notifier_list, &test_atomic_blk);

    blocking_notifier_chain_unregister(&test_blocking_notifier_list,&test_blocking_blk);

    if (task_test0) kthread_stop(task_test0);
    if (task_test1) kthread_stop(task_test1);
}

module_init(myreboot_init);
module_exit(myreboot_exit);
MODULE_LICENSE("Dual BSD/GPL");

