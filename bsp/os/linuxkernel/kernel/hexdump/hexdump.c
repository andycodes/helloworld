#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/printk.h>

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

	memset((void*)paddr, 0xaa,100);
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_NONE, 16, 1,paddr, 100, true);
	pr_info("\n****************\n");
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_ADDRESS, 16, 1,paddr, 100, true);
	pr_info("\n****************\n");
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_OFFSET, 16, 1,paddr, 100, true);

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

