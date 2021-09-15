#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

#define MSG(message, args...) printk(KERN_DEBUG "irq:" message, ##args)

int irq;
char *interface;

// 下面这2个参数通过插入内核模块
//的时候赋值的...
module_param(irq, int, 0644);
module_param(interface, charp, 0644);

// 中断捕获的时候的处理函数
irqreturn_t  irq_handle_function(int irq, void *device_id)
{   
    static int count = 1;
    MSG("[%d]receive the irq at %ld...\n", count, jiffies);
    count++;    
    return IRQ_NONE;/*IRQ_NONE        interrupt was not from this device*/
}

int irqtest_init(void)
{   

    MSG("interface=%s and irq=%d...\n", interface, irq);

/*
   注册中断捕获，
   第三个参数的意思是和其他设备共享该中断号，
   最后一个参数是设备的id，
   其实对于共享下的设备这个号码据说是随便写，
    一般都写irq的了。	
    只要注册成功就可以等待对应设备的该中断号
    的到来 就可以处理回调函数了。。	
int request_irq(unsigned int irq, irq_handler_t handler,
        unsigned long irqflags, const char *devname, void *dev_id)
 */
    if(request_irq(irq, irq_handle_function, IRQF_SHARED, interface, (void *)&irq)) 
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

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");

/* cat /proc/interface
    insmod irqtest.ko irq=1 interface=fan
*/

