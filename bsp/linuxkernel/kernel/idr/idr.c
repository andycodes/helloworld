#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/idr.h>
/*���� radix tree���㷨�������µ�id������id������id*/
/*
IDR������Linux�ں���ָ��������ID������ơ�

ʵ���������������һ�ֽ�һ������ID�ź�һ��ָ�������һ��Ļ��ơ�

�������������03��2�¼����ںˣ���ʱ��ΪPOSIX��ʱ����һ��������
���ڣ��ں��кܶ�ط��������ҵ�������Ӱ��



IDR����ԭ��

IDR������������Щ��Ҫ��ĳ���������ض�ָ�������һ��ĵط���
���磬��IIC�����У�ÿ���豸�����Լ��ĵ�ַ��Ҫ����
�������ҵ��ض����豸���ͱ���Ҫ�ȷ����豸�ĵ�ַ��
��������Ҫ���������ϵ�IIC�豸ʱ������Ҫ֪�����ǵ�ID�ţ�
ͬʱҪ���ں��н���һ�������������豸�Ľṹ�壬����������

��ID�ź��豸�ṹ�������������ʹ���������������
һ��ID �źܴ���������������ռ�ݴ����ڴ�ռ䡣
����Ȼ�����ܡ��������������ǣ����������ʵ�ʴ��ڵ��豸�ܶ࣬
������Ĳ�ѯЧ�ʻ�ܵ͡�

��ʱ��IDR����Ӧ�˶������û����ڲ����ú����ʵ�֣�
���Ժܷ���Ľ�������ָ��������������Ҿ��кܸߵ�����Ч��
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

