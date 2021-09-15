#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

#define MSG(message, args...) printk(KERN_DEBUG "irq:" message, ##args)

int irq;
char *interface;

// ������2������ͨ�������ں�ģ��
//��ʱ��ֵ��...
module_param(irq, int, 0644);
module_param(interface, charp, 0644);

// �жϲ����ʱ��Ĵ�����
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
   ע���жϲ���
   ��������������˼�Ǻ������豸������жϺţ�
   ���һ���������豸��id��
   ��ʵ���ڹ����µ��豸��������˵�����д��
    һ�㶼дirq���ˡ�	
    ֻҪע��ɹ��Ϳ��Եȴ���Ӧ�豸�ĸ��жϺ�
    �ĵ��� �Ϳ��Դ���ص������ˡ���	
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

