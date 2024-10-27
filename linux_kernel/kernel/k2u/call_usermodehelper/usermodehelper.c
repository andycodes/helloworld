#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/sysctl.h>
#include <linux/slab.h>

#define USER_EXEC_FILE_PATH  ("/project/trunck/linuxkernel/drivers/opc/call_usermodehelper/userspace.sh")

static int hello_init(void)
{
   int result = 0;
   char  cmdPath[]= USER_EXEC_FILE_PATH;
   char* cmdArgv[]= {USER_EXEC_FILE_PATH,"andy","huangyingying",NULL};
   char* cmdEnvp[]= {"HOME=/","PATH=/sbin:/bin:/usr/bin",NULL};
   /*
      process a user process in kernel space
        static inline int
        call_usermodehelper(char *path, char **argv, char **envp, int wait)
        enum umh_wait {
           UMH_NO_WAIT = -1,     //   don't wait at all 
           UMH_WAIT_EXEC = 0,    //  wait for the exec, but not the process 
           UMH_WAIT_PROC = 1,    //   wait for the process to complete 

   */
   result = call_usermodehelper(cmdPath,cmdArgv,cmdEnvp,UMH_WAIT_PROC);      

   printk(" result  %d\n",result);
   printk("The process is \"%s\",pidis %d ,sys_getpid is %d \n",current->comm,current->pid);

   return result;
}

static void hello_exit(void)
{
    printk("Bye, my dear!/n Cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");

