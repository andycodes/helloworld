#include <linux/init.h>
#include <linux/module.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
 

#define  PROC_FILE       "proc_file"
#define  PROC_DIR_NAME   "fansaihuadir"
 
static char msg[255] = {0};
static struct proc_dir_entry * p_entry = NULL;
static struct proc_dir_entry *parent = NULL;

static ssize_t ipsec_conntrack_read(struct file * file,char *data,size_t len,loff_t *offset)
{
    printk("read\noffset %d\n",(int)*offset);
    
    if(*offset > 0) 
    {
        return 0;
    }
    
    if(copy_to_user(data,msg,strlen(msg)) < 0)
    {
            return -1;
    }
    
    *offset += strlen(msg);
    
    return strlen(msg);
}
 
static ssize_t ipsec_conntrack_write(struct file *file, const char *data,size_t len,loff_t *offset)
{
    printk("write\noffset %d\n",(int)*offset);

    if(copy_from_user(msg,(void *)data,len))
    {
        return -EFAULT;
    }
    
    msg[len - 1] = '\0';
    printk("%s\n", msg);
    return len;
}

/*read:ipsec_conntrack_read GNU GCC */
/*.read = ipsec_conntrack_read C99 over usingthe GNU extension */

static struct file_operations ipsec_conntrack_ops =
 
{
        read:ipsec_conntrack_read,
        write:ipsec_conntrack_write,
};

static int __init proc_ipsec_init(void)
{
    printk("proc fs module_init\n");
/*
*struct proc_dir_entry *proc_mkdir(const char *name,struct proc_dir_entry *parent);
*name�����㶨���Ŀ¼����
*parent�����㶨������Ŀ¼�ĸ�Ŀ¼����ΪNULL,��ʾΪ/proc��
*/
    parent = proc_mkdir(PROC_DIR_NAME, NULL);
    if(parent == NULL)
    {
        return -ENOMEM;
    }
 /*
 ** create_proc_entry :create file in proc files system
**name : Ҫ�������ļ�����
**mode : �ļ����룬Ϊ 0 ����ϵͳĬ�ϵ����봴���ļ���
**base : ָ�����ļ����ڵ�Ŀ¼�����Ϊ NULL�����ļ��������� /proc ��Ŀ¼�¡�
*/
//    p_entry = create_proc_entry(PROC_FILE,S_IFREG | S_IRUGO ,NULL);
    p_entry = create_proc_entry(PROC_FILE,S_IFREG | S_IRUGO ,parent);
    if(p_entry == NULL)
    {
       return -ENOMEM;
    }
    
    p_entry->proc_fops = &ipsec_conntrack_ops;
    return 0;
}

static void  __exit proc_ipsec_exit(void)
{
    remove_proc_entry(PROC_FILE,parent);
    remove_proc_entry(PROC_DIR_NAME,NULL);
    
    printk("proc ko exit\n");

}

module_init(proc_ipsec_init);
module_exit(proc_ipsec_exit);

MODULE_AUTHOR("fansaihua");
MODULE_DESCRIPTION("Proc Test Module");
MODULE_LICENSE("GPL");

/*�����ֶ�*/
/*    
cd /proc
echo "123">proc_file
dmesg 
cat proc_file
dmesg 
*/

