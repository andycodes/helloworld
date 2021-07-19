#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

#define MSG(message, args...) printk(KERN_DEBUG "irq:" message, ##args)
#define IRQ_TEST  30
#define IRQ_TEST_EINT(x)   (IRQ_TEST+x)

int irq;
char *interface;
char irq_data[] = "father";

// 中断捕获的时候的处理函数
irqreturn_t  irq_handle_function(int irq, void *device_id)
{   
    static int count = 1;
    MSG("[%d]irq_handle_function receive the irq at %ld...\n", count, jiffies);
    count++;    
    return IRQ_NONE;/*IRQ_NONE        interrupt was not from this device*/
}

void
irq_set_chip_and_handler_name(unsigned int irq, struct irq_chip *chip,
                  irq_flow_handler_t handle, const char *name)
{
    irq_set_chip(irq, chip);
    __irq_set_handler(irq, handle, 0, name);
}
EXPORT_SYMBOL_GPL(irq_set_chip_and_handler_name);

static void s5p_irq_demux_eint16_31(unsigned int irq, struct irq_desc *desc)
{
    MSG("s5p_irq_demux_eint16_31\n");
     generic_handle_irq(IRQ_TEST_EINT(3));
}


static inline void s5p_irq_vic_eint_mask(struct irq_data *data)
{
    MSG("s5p_irq_vic_eint_mask\n");
}

static void s5p_irq_vic_eint_unmask(struct irq_data *data)
{
    MSG("s5p_irq_vic_eint_unmask\n");
}

static void s5p_irq_vic_eint_maskack(struct irq_data *data)
{
    MSG("s5p_irq_vic_eint_maskack\n");
}

static inline void s5p_irq_vic_eint_ack(struct irq_data *data)
{
    MSG("s5p_irq_vic_eint_ack\n");
}

static int s5p_irq_eint_set_type(struct irq_data *data, unsigned int type)
{
    MSG("s5p_irq_eint_set_type\n");
    return 0;
}

int s3c_irqext_wake(struct irq_data *data, unsigned int state)
{
    MSG("s3c_irqext_wake\n");
    return 0;
}

static struct irq_chip s5p_irq_vic_eint = {
    .name       = "s5p_vic_eint",
    .irq_mask   = s5p_irq_vic_eint_mask,
    .irq_unmask = s5p_irq_vic_eint_unmask,
    .irq_mask_ack   = s5p_irq_vic_eint_maskack,
    .irq_ack    = s5p_irq_vic_eint_ack,
    .irq_set_type   = s5p_irq_eint_set_type,
#ifdef CONFIG_PM
    .irq_set_wake   = s3c_irqext_wake,
#endif
};

static inline void s5p_irq_eint_mask(struct irq_data *data)
{
    MSG("s3c_irqext_wake\n");
}

static void s5p_irq_eint_unmask(struct irq_data *data)
{
    MSG("s5p_irq_eint_unmask\n");
}

static void s5p_irq_eint_maskack(struct irq_data *data)
{
    MSG("s5p_irq_eint_maskack\n");
}

static inline void s5p_irq_eint_ack(struct irq_data *data)
{
    MSG("s5p_irq_eint_ack\n");
}

void
handle_level_irq(unsigned int irq, struct irq_desc *desc)
{
        MSG("handle_level_irq\n");
}

static struct irq_chip s5p_irq_eint = {
    .name       = "s5p-eint",
    .irq_mask   = s5p_irq_eint_mask,
    .irq_unmask = s5p_irq_eint_unmask,
    .irq_mask_ack   = s5p_irq_eint_maskack,
    .irq_ack    = s5p_irq_eint_ack,
    .irq_set_type   = s5p_irq_eint_set_type,
#ifdef CONFIG_PM
    .irq_set_wake   = s3c_irqext_wake,
#endif
};

int irqtest_init(void)
{   
    int irq;
    MSG("interface=%s and irq=%d...\n", interface, irq);


    /*修改父中断的流控函数*/
    irq_set_chained_handler(irq, s5p_irq_demux_eint16_31);
    irq_set_handler_data(irq,(void*)irq_data);


    for (irq = IRQ_TEST_EINT(1); irq <= IRQ_TEST_EINT(2); irq++)
        irq_set_chip(irq, &s5p_irq_vic_eint);

    for (irq = IRQ_TEST_EINT(3); irq <= IRQ_TEST_EINT(4); irq++) {
        irq_set_chip_and_handler(irq, &s5p_irq_eint, handle_level_irq);
        //set_irq_flags(irq, IRQF_VALID);
    }

    if(request_irq(IRQ_TEST_EINT(3), irq_handle_function, IRQF_SHARED, interface, (void *)&irq)) 
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

