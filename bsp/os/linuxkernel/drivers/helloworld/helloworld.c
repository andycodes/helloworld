#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/slab.h>

static int __init hello_init(void)
{
	void *paddr = NULL;
	printk(KERN_ALERT "Hello, world!\n");
	paddr = kzalloc(100, GFP_KERNEL);
	if(NULL == paddr) {
		pr_err("[%s]kzalloc err\n", __func__);
		return -1;
	}

	pr_info("[%s][%pK]\n", __func__, paddr);

	return 0;
}

static void __exit hello_exit(void)
 {
    printk(KERN_ALERT "Goodbye, cruel world\n");
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

