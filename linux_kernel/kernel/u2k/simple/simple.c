#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
 
MODULE_LICENSE("GPL");
 
#define DEVICE_NAME ("my_dev")
 
int MAJOR_NUM = 500;
int g_val;
struct device *dev;
struct class *myclass;
 
static ssize_t global_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	int ret;
	char val[20];
	printk(KERN_ERR "###### global_read \n");
	
	sprintf(val, "%d\n", g_val);
	ret = simple_read_from_buffer(buf, len, off, val, strlen(val));
	return ret;
}
 
static ssize_t global_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	int  ret, temp;
	char val[20];
	
	ret = simple_write_to_buffer((void*)val, sizeof(val)-1, off, buf, len);
	sscanf(val, "%d", &temp);
	g_val = temp;
	return ret;
}
 
struct file_operations fileops = {
	.read = global_read,
	.write = global_write,
};
 
static int __init globalvar_init(void)
{
	int ret;
	g_val = 0;
	
	printk(KERN_ERR "golabvar_init \n");
	
	ret = register_chrdev(MAJOR_NUM, "my_driver", &fileops);
	if(ret) {
		printk(KERN_ERR "register_chrdev fail \n");
        return -1;
	}

    printk(KERN_ERR "register_chrdev sucess \n");
    //注册一个类，使mdev可以在"/dev/"目录下 面建立设备节点
    myclass = class_create(DEVICE_NAME);
    //创建一个设备节点，节点名为DEVICE_NAME
    dev = device_create(myclass, NULL, MKDEV(MAJOR_NUM, 0), NULL, DEVICE_NAME);
    if(!dev) {
        printk(KERN_ERR "device_create faile \n");
    }
		
	return 0;
} 
 
static void __exit globalvar_exit(void)
{
	printk("golabvar_exit \n");
	device_destroy(myclass, MKDEV(MAJOR_NUM, 0));
	class_destroy(myclass);
	unregister_chrdev(MAJOR_NUM, "globalvar");
}
 
module_init(globalvar_init);
module_exit(globalvar_exit);
MODULE_LICENSE("Dual BSD/GPL");

/*
echo 123 >/dev/my_dev
cat /dev/my_dev
123
*/