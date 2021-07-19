#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */

static DEVICE_ATTR(mma7660_regs, S_IRUGO | S_IWUGO, show_7660regs, write_7660regs);

static struct attribute *mma7660_sysfs_entries[] = {
      &dev_attr_mma7660_regs.attr,
      NULL
         };

static struct attribute_group mma660_attr_group = {
            .attrs  = mma7455l_sysfs_entries,
     };

static ssize_t show_7660regs(struct device *dev,
                      struct device_attribute *attr, char *buf)
{
    struct mma7455l_info *mma = dev_get_drvdata(dev);
    int i;
    char buffer[10];
         if (10 != (i = i2c_master_recv(mma->client, buffer, 10)))
    {//读出mma7660十个寄存器的值
    mmadbg("i2c i/o error: rc == %d (should be 10)\n", i);
    return;
    }
     dbg("read : addr:value :\n");     
    for(i=0;i<=10;i++)
    {if(i==5) printk("\n");printk(" %d=%x ,,", i,  buffer[i] );     }
    dbg("\n");        
}

static ssize_t write_7660regs(struct device *dev,
                       struct device_attribute *attr, const char *buf, size_t count)
{
    struct mma7455l_info *mma = dev_get_drvdata(dev);
                                            
    dbg("in write_mode: %s\n",buf);
        int addr=0,value=0;
    int i=0,flag=0;
    char buffer[10];
    for(i=0;i<count;i++)
    printk("count=%d,\n",buf[i]);
    for(i=0;buf[i]!=10;i++)
    {
    if(buf[i]==' ')
    {flag=1;continue;}
    if(flag==0)
    addr=addr*10+(buf[i]-'0');
    else
    value=value*10+(buf[i]-'0');
    }
         count=  reg_write(mma->client, addr,  value);
        return count;
}


static int __init hello_init(void)
{
 printk(KERN_ALERT "Hello, world!\n");

err = sysfs_create_group(&client->dev.kobj, &mma7660_attr_group);
 
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

/*
/sys/class/i2c-adapter/i2c-0/0-004c # ls
echo "7 34" > mma7660_regs
cat mma7660_regs
*/

