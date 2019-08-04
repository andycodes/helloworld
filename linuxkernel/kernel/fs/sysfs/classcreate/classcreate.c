#if 0 // 1 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

int hello_major = 555;
int hello_minor = 0;
int number_of_devices = 1;
struct cdev cdev;
dev_t dev = 0;

struct file_operations hello_fops = 
    {
     .owner = THIS_MODULE
    };

struct class *my_class;

static void char_reg_setup_cdev (void)
{
    int error, devno = MKDEV (hello_major, hello_minor);
    cdev_init (&cdev, &hello_fops);
    cdev.owner = THIS_MODULE;
    cdev.ops = &hello_fops;
    error = cdev_add (&cdev, devno , 1);
    if (error)
    {
        printk (KERN_NOTICE "Error %d adding char_reg_setup_cdev", error);
    }
}

static int __init hello_2_init (void)
{
    int result;
    dev = MKDEV (hello_major, hello_minor);
    /*number_of_devices ��ʾע��Ĵ��豸��Ŀ*/
    result = register_chrdev_region (dev, number_of_devices, "hello");
    if (result<0) 
    {
        printk (KERN_WARNING "hello: can't get major number %d/n", hello_major);
        return result;
    }

    char_reg_setup_cdev ();

    /* create your own class under /sysfs */
    my_class = class_create(THIS_MODULE, "my_class");
    if(IS_ERR(my_class)) 
    {
        printk("Err: failed in creating class./n");
        return -1; 
    } 
    
    /* register your own device in sysfs, and 
    this will cause udev to create 
    corresponding device node */

    /*����ɹ�������
    ����/devĿ¼�²���/dev/fansaihua�豸*/
    device_create( my_class, NULL, MKDEV(hello_major, 0), NULL, "fansaihua");
    printk (KERN_INFO "Registered character driver/n");
    return 0;
}

static void __exit hello_2_exit (void)
{
    dev_t devno = MKDEV (hello_major, hello_minor);
    cdev_del (&cdev);
    device_destroy(my_class, MKDEV(hello_major, 0)); //delete device node under /dev
    class_destroy(my_class); //delete class created by us
    unregister_chrdev_region (devno, number_of_devices);
    printk (KERN_INFO "char driver cleaned up/n");
}

module_init (hello_2_init);
module_exit (hello_2_exit);
MODULE_LICENSE ("GPL");

#else
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class


static int my_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: open()\n");
  return 0;
}
  static int my_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: close()\n");
  return 0;
}
  static ssize_t my_read(struct file *f, char __user *buf, size_t
  len, loff_t *off)
{
  printk(KERN_INFO "Driver: read()\n");
  return 0;
}
  static ssize_t my_write(struct file *f, const char __user *buf,
  size_t len, loff_t *off)
{
  printk(KERN_INFO "Driver: write()\n");
  return len;
}
  static struct file_operations pugs_fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .write = my_write
};

static u32 integrator_id = 0xa;

static const char manufacturer[] = "huangyingying";

static ssize_t intcp_get_manf(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "%02x\n", integrator_id >> 24);
}

static ssize_t intcp_set_manf(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	return 0;
}

static DEVICE_ATTR(intcp_manf_attr, S_IRUGO, intcp_get_manf, intcp_set_manf);

static int __init ofcd_init(void) /* Constructor */
{
  struct device * dev = NULL;
  int error = 0;
  printk(KERN_INFO "fansaihua: class test");

/**
 * alloc_chrdev_region() - register a range of char device numbers
 * @dev: output parameter for first assigned number
 * @baseminor: first of the requested range of minor numbers
 * @count: the number of minor numbers required
 * @name: the name of the associated device or driver
 *
 * Allocates a range of char device numbers.  The major number will be
 * chosen dynamically, and returned (along with the first minor number)
 * in @dev.  Returns zero or a negative error code.
 */
 /*���� name ��ʾ�豸��
 ���ƣ��������Ҳ���� 
 /proc/devices �ļ��Լ�sfsfs �п���*/
/*int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,
			const char *name)*/
/*cat /proc/devices you can see  fansaihuaCharDevice*/
  if (alloc_chrdev_region(&first, 0, 1, "fansaihuaCharDevice") < 0)
  {
    return -1;
  }
  
/*
This is used to create a struct class pointer that can then be used
 * in calls to device_create().
���������������һ��struct class�Ľṹ��ָ�룬���ָ�������device_create()�����Ĳ���*/
  if ((cl = class_create(THIS_MODULE, "fansaihuaClass")) == NULL)
  {
    unregister_chrdev_region(first, 1);
    return -1;
  }


/**
 * device_create - creates a device and registers it with sysfs
 * @class: pointer to the struct class that this device should be registered to
 * @parent: pointer to the parent struct device of this new device, if any
 * @devt: the dev_t for the char device to be added
 * @drvdata: the data to be added to the device for callbacks
 * @fmt: string for the device's name
 *
 * This function can be used by char device classes.  A struct device
 * will be created in sysfs, registered to the specified class.
 *
 * A "dev" file will be created, showing the dev_t for the device, if
 * the dev_t is not 0,0.
 * If a pointer to a parent struct device is passed in, the newly created
 * struct device will be a child of that device in sysfs.
 * The pointer to the struct device will be returned from the call.
 * Any further sysfs files that might be required can be created using this
 * pointer.
 *
 * Returns &struct device pointer on success, or ERR_PTR() on error.
 *
 * Note: the struct class passed to this function must have previously
 * been created with a call to class_create().
 */
 /*ls /dev/ you can see  fansaihuaDevice*/
/** device_create - creates a device and registers it with sysfs
���Ƚ���һ��"sysfs"��sysfs��linux2.6���ṩ��һ�����⵵��ϵͳ��
���豸ģ���У�sysfs�ļ�ϵͳ������ʾ�豸�Ľṹ��
���豸�Ĳ�νṹ����ķ�Ӧ���û��ռ��У�
�Ӷ�����ͨ���޸�sysfs�е��ļ��������޸��豸������ֵ��
sysfs�����ص���Ŀ¼�µ�"/sys"�ļ����¡�*/
/*device_create - creates a device and registers it with sysfs*/
  dev = device_create(cl, NULL, first, NULL, "fansaihuaDevice");
  if (dev == NULL)
  {
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }

/*ʹ���������ʱҪ���� device_create�����ص�device*ָ�룬
��������/sys/class/�´���һ�������ļ���
�Ӷ�ͨ������������ļ����ж�д������ɶ�Ӧ�����ݲ�����*/
  error = device_create_file(dev,&dev_attr_intcp_manf_attr);
  if (error <0)
  {
     printk("device_create_file err\n");
  }

  cdev_init(&c_dev, &pugs_fops);

  if (cdev_add(&c_dev, first, 1) == -1)
  {
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
  return 0;
}

static void __exit ofcd_exit(void) /* Destructor */
{
  cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  unregister_chrdev_region(first, 1);
  printk(KERN_INFO "fansaihua: ofcd unregistered");
}

module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("fansaihua");
MODULE_DESCRIPTION("Our First Character Driver");

/*  TEST ******************
root@fan-VirtualBox:/dev# echo "huangyingying" > /dev/fansaihuaDevice 
root@fan-VirtualBox:/dev# dmesg |tail -10

<6>[ 4149.161460] Namaskar: ofcd registered
[ 4351.122308] Driver: open()
[ 4351.122541] Driver: write()
[ 4351.122553] Driver: close()
root@fan-VirtualBox:/dev# cat /dev/fansaihuaDevice 
root@fan-VirtualBox:/dev# dmesg |tail -10

<6>[ 4149.161460] Namaskar: ofcd registered
[ 4351.122308] Driver: open()
[ 4351.122541] Driver: write()
[ 4351.122553] Driver: close()
[ 4398.879924] Driver: open()
[ 4398.885885] Driver: read()
[ 4398.885898] Driver: close()
root@fan-VirtualBox:/dev# 

*/

/*

���û��ռ��ȡ����
...
read(dev->fd, val, sizeof(*val));
...
write(dev->fd, &val, sizeof(val));
*/
#endif
