#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/printk.h>

#define BUFF_SIZE	(128)

static int __init hello_init(void)
{
	void *paddr = NULL;
	printk(KERN_ALERT "Hello, world!\n");
	paddr = kzalloc(BUFF_SIZE, GFP_KERNEL);
	if(NULL == paddr) {
		pr_err("[%s]kzalloc err\n", __func__);
		return -1;
	}

	pr_info("[%s][%pK]\n", __func__, paddr);

	memset((void*)paddr, 0xaa,BUFF_SIZE);
	/*Frame: aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa  ................*/
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_NONE, 16, 1,paddr, BUFF_SIZE, true);
	pr_info("\n****************\n");
	/*Frame: 000000006ee0a4df: aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa  ................*/
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_ADDRESS, 16, 1,paddr, BUFF_SIZE, true);
	pr_info("\n****************\n");
	/*Frame: 00000070: aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa  ................*/
	print_hex_dump(KERN_ERR, "Frame: ",DUMP_PREFIX_OFFSET, 16, 1,paddr, BUFF_SIZE, true);

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

