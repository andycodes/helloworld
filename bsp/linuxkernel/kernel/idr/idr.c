#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/idr.h>
/*基于 radix tree的算法，分配新的id，遍历id，查找id*/
/*
IDR机制在Linux内核中指的是整数ID管理机制。

实质上来讲，这就是一种将一个整数ID号和一个指针关联在一起的机制。

这个机制最早在03年2月加入内核，当时作为POSIX定时器的一个补丁。
现在，内核中很多地方都可以找到它的身影。



IDR机制原理：

IDR机制适用在那些需要把某个整数和特定指针关联在一起的地方。
例如，在IIC总线中，每个设备都有自己的地址，要想在
总线上找到特定的设备，就必须要先发送设备的地址。
当适配器要访问总线上的IIC设备时，首先要知道它们的ID号，
同时要在内核中建立一个用于描述该设备的结构体，和驱动程序

将ID号和设备结构体结合起来，如果使用数组进行索引，
一旦ID 号很大，则用数组索引会占据大量内存空间。
这显然不可能。或者用链表，但是，如果总线中实际存在的设备很多，
则链表的查询效率会很低。

此时，IDR机制应运而生。该机制内部采用红黑树实现，
可以很方便的将整数和指针关联起来，并且具有很高的搜索效率
*/

#define PMU_IDR_START   0
#define PMU_IDR_END       99

struct idr pmu_idr;

struct pmu
{
    int a;
    char* b;
};

struct pmu  pmu0 = {0,"pmu0"};
struct pmu  pmu1 = {1,"pmu1"};

static int __init idr_module_init(void)
{
    int  id0 = 0;
    int  id1 = 0;
    struct pmu* cur_pmu = NULL;

    printk("%s\n",__func__);

    idr_init(&pmu_idr);

    id0 = idr_alloc(&pmu_idr, &pmu0,PMU_IDR_START, PMU_IDR_END,GFP_KERNEL);
    if(id0 < 0)
    {
        pr_err("idr_alloc pmu0 err\n");
        return -1;
    }

    id1 = idr_alloc(&pmu_idr, &pmu1,PMU_IDR_START, PMU_IDR_END, GFP_KERNEL);
    if(id1 < 0)
    {
        pr_err("idr_alloc pmu1 err\n");
        return -1;
    }

    cur_pmu = (struct pmu*)idr_find(&pmu_idr,id1);
    if(NULL != cur_pmu)
    {
        printk("id1: %d,%s\n",id1,cur_pmu->b);
    }

    return 0;
}

static void __exit idr_exit(void)
{
    idr_destroy(&pmu_idr);
}

module_init(idr_module_init);
module_exit(idr_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

