#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>    /* printk() */
#include <linux/slab.h>        /* kmalloc() */
#include <linux/fs.h>        /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#define MAX_NUM (20)

static void *ct_seq_start(struct seq_file *s, loff_t *pos)
{ 
    loff_t *spos = kmalloc(sizeof(loff_t), GFP_KERNEL);
    if (NULL == spos)
    {
		pr_err("%s kmalloc failed\n",__func__);
		return NULL;
    }

    if(*pos > MAX_NUM)
    {
		pr_err("%s *pos is %lli;MAX_NUM is 20\n",__func__,*pos);
		return NULL;
    }

     *spos = *pos;
     printk("%s  *spos: %lli\n",__func__,*spos);
    return spos; 
 }

static void *ct_seq_next(struct seq_file *s, void *v, loff_t *pos)
{ 
	loff_t *spos = v;
	*pos = ++*spos;
	printk("%s *spos  %lli; *pos %lli \n",__func__,*spos,*pos);

	if(*spos >MAX_NUM)
	{
        pr_err("%s *spos is %d;MAX_NUM is 20\n",__func__,*spos);
        return NULL;
	}

	return spos;
}

static void ct_seq_stop(struct seq_file *s, void *v)
{ 
    loff_t *spos = v;
    printk("%s \n",__func__);
    if(v)
    {
        printk("%s spos %p data: %lli\n",__func__,spos,*spos);
    }
    
    kfree(v); 
}

static int ct_seq_show(struct seq_file *s, void *v)
{ 
	loff_t *spos = v;
	printk("%s *spos : %lli\n",__func__,*spos);
	seq_printf(s, "%lld\n", (long long)*spos);
	return 0;
}

static const struct seq_operations ct_seq_ops = 
{           .start = ct_seq_start,
	        .next  = ct_seq_next,
	        .stop  = ct_seq_stop,
	        .show  = ct_seq_show 
};

static int ct_open(struct inode *inode, struct file *file)
{ 
    return seq_open(file, &ct_seq_ops); 
}

static const struct file_operations ct_file_ops = 
{ 
    .owner   = THIS_MODULE,
    .open    = ct_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = seq_release 
};

static int __init ct_init(void)
{ 
    proc_create("sequence", 0, NULL, &ct_file_ops);
    return 0; 
}

static void __exit seq_cleanup_module(void)
{
    remove_proc_entry("sequence", NULL);
}

module_init(ct_init);
module_exit(seq_cleanup_module);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

