#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/string.h>

#include "tracelog.h"
  
int __init kernel_test_init(void)
{
    char log_msg[] ="FANSAIHUA\n";
    printk("kernel_test_init\n"); 
    tracelog(log_msg,strlen(log_msg)) ;
    return 0;//module_init 必须要RETURN ;不然INSMOD 的时候报错
}

void __exit kernel_test_exit(void) 
{ 
   printk("kernel_test_exit \n"); 
} 
 
module_init(kernel_test_init); 
module_exit(kernel_test_exit); 

MODULE_LICENSE("GPL");


