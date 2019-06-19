#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>

#define ARRAY_LEN_MAX   (20)  
/*dentry描述的是逻辑的文件，而inode描述的是文件的物理属性*/
struct dentry *my_debugfs_root;

static u8 a = 0;
/*
struct debugfs_blob_wrapper {
	void *data;
	unsigned long size;
};
*/
char hello[32] = "Hello world!\n";
struct debugfs_blob_wrapper b;
unsigned int array[ARRAY_LEN_MAX];

static int c_open(struct inode *inode, struct file *filp)
{
    filp->private_data = inode->i_private;
    return 0;
}

static ssize_t c_read(struct file *filp, char __user *buffer,
        size_t count, loff_t *ppos)
{
    if (*ppos >= 32)
        return 0;
    if (*ppos + count > 32)
        count = 32 - *ppos;

    if (copy_to_user(buffer, hello + *ppos, count))
        return -EFAULT;

    *ppos += count;

    return count;
}

static ssize_t c_write(struct file *filp, const char __user *buffer,
        size_t count, loff_t *ppos)
{
    if (*ppos >= 32)
        return 0;
    if (*ppos + count > 32)
        count = 32 - *ppos;

    if (copy_from_user(hello + *ppos, buffer, count))
        return -EFAULT;

    *ppos += count;

    return count;
}

struct file_operations c_fops = {
    .owner = THIS_MODULE,
    .open = c_open,
    .read = c_read,
    .write = c_write,
};


static int bdi_debug_stats_show(struct seq_file *s, void *p)
{
    seq_printf(s, "AB3100 registers:\n");
    return 0;
}


static int bdi_debug_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, bdi_debug_stats_show, inode->i_private);
}

struct file_operations d_fops = {
    .open = bdi_debug_stats_open,
    .read = seq_read,
    .llseek	= seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
};

static int __init mydebugfs_init(void)
{
    struct dentry *sub_dir, *r_a, *r_b, *s_c,*s_d;

    printk(KERN_INFO "mydebugfs_init\n");

    /*debugfs默认根目录  /sys/kernel/debug */
    /*struct dentry *debugfs_create_dir(const char *name, struct dentry *parent)*/
    my_debugfs_root = debugfs_create_dir("mydebug", NULL);
    if (!my_debugfs_root)
    return -ENOENT;

    /*这表示文件名为"a"，
    文件属性是0644，
    父目录是上面建立的"mydebug"，
    对应的变量是模块中的a。*/
    r_a = debugfs_create_u8("a", 0644, my_debugfs_root, &a);
    if (!r_a)
    goto Fail;

    b.data = (void *)hello;
    b.size = strlen(hello) + 1;
    r_b = debugfs_create_blob("b", 0644, my_debugfs_root, &b);
    if (!r_b)
    goto Fail;

    sub_dir = debugfs_create_dir("subdir", my_debugfs_root);
    if (!sub_dir)
    goto Fail;

    s_c = debugfs_create_file("c", 0644, sub_dir, NULL, &c_fops);
    if (!s_c)
    goto Fail;

    s_d = debugfs_create_file("d_name", 0644,my_debugfs_root, NULL, &d_fops);
    if (!s_d)
    goto Fail;
        
    return 0;

    Fail:
    debugfs_remove_recursive(my_debugfs_root);
    my_debugfs_root = NULL;
    return -ENOENT;
}

static void __exit mydebugfs_exit(void)
{
    printk(KERN_INFO "mydebugfs_exit\n");
    /*recursively递归 removes a directory*/
    debugfs_remove_recursive(my_debugfs_root);
    return;
}

module_init(mydebugfs_init);
module_exit(mydebugfs_exit);

MODULE_AUTHOR("fansaihua brucefan@foxmail.com");
MODULE_DESCRIPTION("debugfs test");
MODULE_LICENSE("GPL");

/*
root@fan-VirtualBox:/sys/kernel/debug/mydebug# cat a
0
root@fan-VirtualBox:/sys/kernel/debug/mydebug# echo 1 >a
root@fan-VirtualBox:/sys/kernel/debug/mydebug# cat a
1
root@fan-VirtualBox:/sys/kernel/debug/mydebug# 

*/

