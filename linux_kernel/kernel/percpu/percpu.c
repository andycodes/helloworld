#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/percpu.h>
 
 
static int * ptr;
 
static int __init hello_init (void)
{			
	int cpu;	
	int * the_ptr;
	
	ptr = alloc_percpu(int);
	
	for_each_possible_cpu(cpu){
		/* �ر��ں˿���ռ�� */	
		get_cpu();
		/* ��ȡ�ض�cpu����������ָ�� */
		the_ptr = per_cpu_ptr(ptr, cpu);	
		*the_ptr = cpu;
		printk("val = %d\n", *the_ptr);	
		put_cpu();
	}
 
	
	
	return 0;
}
 
 
static void __exit hello_exit (void)
{	
	free_percpu(ptr);/* �ͷſռ� */
}
 
module_init(hello_init);
module_exit(hello_exit);
 
MODULE_AUTHOR("Tian bei");
MODULE_DESCRIPTION("per_cpu_ptr test");
MODULE_LICENSE("GPL");
 