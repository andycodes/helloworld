#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/netfilter_ipv4.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <asm/uaccess.h>
#include "ecall.h"

#define ECALL_DEBUG

#define KMSG      "a message from kernel\n"

char umsg[MEG_LEN];
shell_fun_type *fun_ptr = (shell_fun_type *)umsg;
unsigned long fun_addr = 0;

typedef int (*PTRFUN)(int,int,int,int,int,int);

PTRFUN pAddr;

static int data_to_kernel(struct sock *sk, int cmd, void *user,
			  unsigned int len)
{
	int ret;
	switch(cmd) {
		case IMP1_SET: {
			memset(umsg, 0,MEG_LEN);
			ret = copy_from_user(umsg, user, len);
			if(ret) {
				pr_err("[%s] copy_from_user err\n",__func__);
				return -1;
			}
#ifdef ECALL_DEBUG
			printk("func_name: %s\n", fun_ptr->func_name);
			printk("arg1: %d\n", fun_ptr->data.args[0]);
			printk("arg2: %d\n", fun_ptr->data.args[1]);
			printk("arg3: %d\n", fun_ptr->data.args[2]);
			printk("arg4: %d\n", fun_ptr->data.args[3]);
			printk("arg5: %d\n", fun_ptr->data.args[4]);
			printk("arg6: %d\n", fun_ptr->data.args[5]);
#endif                
			fun_addr = (unsigned long)kallsyms_lookup_name(fun_ptr->func_name);
			if(fun_addr) {
				pAddr = (PTRFUN)fun_addr;
				(*pAddr)(fun_ptr->data.args[0],
				fun_ptr->data.args[1],
				fun_ptr->data.args[2],
				fun_ptr->data.args[3],
				fun_ptr->data.args[4],
				fun_ptr->data.args[5]);
			}
		    
		}break;
		default:break;
	}
	return 0;
}

static struct nf_sockopt_ops imp1_sockops =
{
  .pf = PF_INET,
  .set_optmin = IMP1_SET,
  .set_optmax = IMP1_MAX,
  .set = data_to_kernel,
};

static int __init ecall_init(void)
{
  return nf_register_sockopt(&imp1_sockops);
}

static void __exit ecall_exit(void)
{
  nf_unregister_sockopt(&imp1_sockops);
}

/*TEST*/

int ecall_test(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6)
{
	printk("%s %d,%d,%d,%d,%d,%d\n",__func__,arg1,arg2,arg3,arg4,arg5,arg6);
	return 0;
}


module_init(ecall_init);
module_exit(ecall_exit);
MODULE_LICENSE("Dual BSD/GPL");

