#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static char buf[] ="hello usr world!\n";
static char buf1[32];
 
int __init test_init(void)
{
	struct file *fp;
	mm_segment_t fs;
	loff_t pos;
	
	printk("test enter\n");
	fp =filp_open("/project/get_set_fs",O_RDWR | O_CREAT,0644);
	if (IS_ERR(fp)){
		printk("create file error\n");
		return -1;
	}
	
	fs =get_fs();
	set_fs(KERNEL_DS);
	pos =0;
	vfs_write(fp,buf, sizeof(buf), &pos);
	pos =0;
	vfs_read(fp,buf1, sizeof(buf), &pos);
	printk("Write contet=%s\n",buf1);
	filp_close(fp,NULL);
	set_fs(fs);
	return 0;
}

void __exit test_exit(void)
{
	printk("test exit\n");
}
 
module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");

