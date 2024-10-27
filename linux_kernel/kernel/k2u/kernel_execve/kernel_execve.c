#include<linux/init.h>  
#include<linux/module.h>  
#include<linux/kernel.h>   
#include<linux/syscalls.h>   

#define USER_EXEC_FILE_PATH  ("/project/trunck/linuxkernel/drivers/opc/call_usermodehelper/userspace.sh")

static int __init hello_init(void)   
{   
    kernel_execve(USER_EXEC_FILE_PATH, NULL, NULL);
    return 0;   
}   
static void __exit hello_exit(void)   
{   
    printk("Goodbye\n");   
} 

module_init(hello_init);   
module_exit(hello_exit);

MODULE_LICENSE("GPL"); 

