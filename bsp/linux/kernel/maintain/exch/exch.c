#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/syscalls.h>

int __init exch_init(void)
{
    return 0;//module_init ����ҪRETURN ;��ȻINSMOD ��ʱ�򱨴�
}

void __exit exch_exit(void) 
{ 

} 
 
module_init(exch_init); 
module_exit(exch_exit); 

MODULE_LICENSE("GPL");


