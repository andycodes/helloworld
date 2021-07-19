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
    int n = 50;
    while(n--)
    {
            printk("FAN SAIHUA\n");
            msleep(1000);
    }
}

static struct work_struct works;

static int intr_init(void)
{
	INIT_WORK(&works, (void*)intr_print);

	/*
	static inline bool schedule_work(struct work_struct *work)
	{
		return queue_work(system_wq, work);
	}

	system_wq---ϵͳ����WQ

	�����������schedule_work�������еݽ�
	�µĹ����ڵ㣬schedule_work�ڲ��ỽ
	��worker_thread�ں��̣߳�ʹ֮����״̬Ϊ�ɵ��ȣ���
	����һ�ν��̵���ʱ�̣�worker_thread������ִ�У�
	����Ҫ������ǵ�������������������ÿ��
	�����ڵ��Ϲ��صĺ�����������ϸù����ڵ�
	�����������б�ɾ���������нڵ��ϵĺ���
	������ϣ�worker_thread����sleep��ֱ��schedule_work�ٴ�
	��ĳ������������á�*/

	/* run intr_print on boot cpu */
	/*cpu_online_mask ��ǰ��ЧCPU*/
	/*����Ч��CPU�б����ҵ��ĵ�һ��CPU*/
	//schedule_work_on(cpumask_first(cpu_online_mask), &works);

	return !schedule_work(&works);

	/*schedule_delayed_work*/
	/*�������������һ�������ӳ�ִ��*/
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


