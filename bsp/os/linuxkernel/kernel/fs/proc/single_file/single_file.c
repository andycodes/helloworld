#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/percpu.h>
#include <linux/sched.h>

#define TEST_FILE_NAME  ("exam_esq_file")

static int  single_show(struct seq_file *s, void *p)
{
    seq_printf(s, "fansaihua&huangyingying\n");
    return 0;
}
static int exam_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file,single_show, NULL);
}

static struct file_operations exam_seq_fops = {
        .open = exam_seq_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};

static int __init exam_seq_init(void)
{
    static struct proc_dir_entry *entry = NULL;

    entry = proc_create(TEST_FILE_NAME,0,NULL,&exam_seq_fops);
    if(NULL == entry)
    {
        pr_err("%s proc_create err\n",__func__);
        return -1;
    }

    return 0;
}

static void __exit exam_seq_exit(void)
{
    remove_proc_entry(TEST_FILE_NAME, NULL);
}

module_init(exam_seq_init);
module_exit(exam_seq_exit);
MODULE_LICENSE("GPL");
/*cat /proc/exam_esq_file*/

