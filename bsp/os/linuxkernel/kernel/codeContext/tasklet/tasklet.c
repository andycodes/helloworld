/*
Tasklets 实现于softirq之上，实际上也是softirqs.
Tasklet 同时只运行于一个 CPU.
不同的tasklets 可同时运行于不同的CPU.
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

static struct tasklet_struct mytasklet;

static void mytasklet_handler(unsigned long data)
{
         printk("[%s]\n", __func__);
}

static int __init mytasklet_init(void)
{
    tasklet_init(&mytasklet,mytasklet_handler,0);
    tasklet_schedule(&mytasklet);
    return 0;
}

static void __exit mytasklet_exit(void)
{
    printk("My module is leaving\n");
}

module_init(mytasklet_init);
module_exit(mytasklet_exit);
MODULE_LICENSE("GPL");

