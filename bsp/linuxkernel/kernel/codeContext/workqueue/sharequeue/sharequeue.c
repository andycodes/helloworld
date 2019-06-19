#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>

static void intr_print(void* data)
{
    int n = 5;
    while(n--)
    {
            printk("FAN SAIHUA\n");
            msleep(10000);
    }
}

/*2�ֳ�ʼ������*/
#ifdef DYNAMIC_INIT
static struct work_struct works;
#else
/*��̬��ʼ��*/
static DECLARE_WORK(works, intr_print);
#endif

static int intr_init(void)
{
#ifdef DYNAMIC_INIT
	INIT_WORK(&works, (void*)intr_print);
#endif

	/*�����������schedule_work�������еݽ�
	�µĹ����ڵ㣬schedule_work�ڲ��ỽ
	��worker_thread�ں��̣߳�ʹ֮����״̬Ϊ�ɵ��ȣ���
	����һ�ν��̵���ʱ�̣�worker_thread������ִ�У�
	����Ҫ������ǵ�������������������ÿ��
	�����ڵ��Ϲ��صĺ�����������ϸù����ڵ�
	�����������б�ɾ���������нڵ��ϵĺ���
	������ϣ�worker_thread����sleep��ֱ��schedule_work�ٴ�
	��ĳ������������á�*/
#define WORK_ON_APPOINTMENT_CPU
#ifdef  WORK_ON_APPOINTMENT_CPU
	/* run intr_print on boot cpu */
	/*cpu_online_mask ��ǰ��ЧCPU*/
	/*����Ч��CPU�б����ҵ��ĵ�һ��CPU*/
	schedule_work_on(cpumask_first(cpu_online_mask), &works);
#else
	schedule_work(&works);

	/*schedule_delayed_work*/
	/*�������������һ�������ӳ�ִ��*/
#endif

	return 0;
}

static void intr_exit(void)
{
	/*��ģ�鱻����ʱӦ��ȥ����һ��
	flash_scheduled_work() ���������������ʹ
	�ȴ����������е����񶼱�ִ�С�*/
}

module_init(intr_init);
module_exit(intr_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");


