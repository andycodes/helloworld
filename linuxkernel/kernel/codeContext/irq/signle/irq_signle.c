#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

#define MSG(message, args...) printk(KERN_DEBUG "irq:" message, ##args)
#define IRQ_SUB_DEV0 0
#define IRQ_SUB_DEV1 1
#define IRQ_NONE        -1

int irq = 1;
char *interface = "fan";

int read_device_irq(void)
{
    /*read irq register status*/
    return 0;
}

int handle_sub_dev0_irq(void)
{
    /*stub*/
    return 0;
}

int handle_sub_dev1_irq(void)
{
    /*stub*/
    return 0;
}

// 中断捕获的时候的处理函数
irqreturn_t  irq_handle_function(int irq, void *device_id)
{   
    static int count = 1;
    int irq_src = 0;
    int ret = -1;
    
    MSG("[%d]irq_handle_function receive the irq at %ld...\n", count, jiffies);
    count++;    
    irq_src = read_device_irq(); 
    
    switch(irq_src)
    {
        case IRQ_SUB_DEV0: 
            ret = handle_sub_dev0_irq(); 
            break; 
        case IRQ_SUB_DEV1: 
            ret = handle_sub_dev1_irq(); 
            break; 
        default: 
            ret = IRQ_NONE; 
            break; 
    }
    
    return IRQ_WAKE_THREAD;/*唤醒中断线程，thread_fn将会被执行；*/
}

irqreturn_t  irq_handle_function1(int irq, void *device_id)
{   
    static int count = 1;
    MSG("[%d]irq_handle_function1 receive the irq at %ld...\n", count, jiffies);
    count++;    
    return IRQ_HANDLED;/*IRQ_NONE        interrupt was not from this device*/
}

int irqtest_init(void)
{   

    MSG("interface=%s and irq=%d...\n", interface, irq);

    if(request_threaded_irq(irq, irq_handle_function,irq_handle_function1, IRQF_SHARED, interface, (void *)&irq)) 
    {       
        MSG("request_irq  failure...\n");     
        return -EIO;
    }

    MSG("register irq success...\n");
    return 0;
}

void irqtest_exit(void)
{   
    free_irq(irq, &irq);    
    MSG("free_irq ...\n");
}

module_init(irqtest_init);
module_exit(irqtest_exit);

// 下面这2个参数通过插入内核模块
//的时候赋值的...
module_param(irq, int, 0644);
module_param(interface, charp, 0644);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");

/* cat /proc/interface
    insmod irqtest.ko irq=1 interface=fan
*/

