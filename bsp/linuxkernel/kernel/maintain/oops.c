/*======================================================================
    A kernel module: oops example                                               
    This example is to introduce how to debug according to oops                          
                                                                        
    The initial developer of the original code is Baohua Song           
    <author@linuxdriver.cn>. All Rights Reserved.                       
======================================================================*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM  200   //���豸��

static ssize_t oopsexam_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
  int *p=0;  
  *p  = 1;  //create oops
  return len;
}

static ssize_t oopsexam_write(struct file *filp, const char *buf, size_t len, loff_t
  *off)
{
  int *p=0;  
  *p  = 1;    //create oops
  return len;
}

//��ʼ���ַ��豸������file_operations�ṹ��
struct file_operations oopsexam_fops =
{
  read: oopsexam_read, write: oopsexam_write,
};

static int __init oopsexam_init(void)
{
  int ret;

  //ע���豸����
  ret = register_chrdev(MAJOR_NUM, "oopsexam", &oopsexam_fops);
  if (ret)
  {
    printk("oopsexam register failure\n");
  }
  else
  {
    printk("oopsexam register success\n");
  }
  return ret;
}

static void __exit oopsexam_exit(void)
{
   printk("oopsexam_exit\n");
   //ע���豸����
   unregister_chrdev(MAJOR_NUM, "oopsexam");
}

module_init(oopsexam_init);
module_exit(oopsexam_exit);


MODULE_AUTHOR("fansaihua");
MODULE_LICENSE("Dual BSD/GPL");

