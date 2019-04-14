/*This program is used to allocate memory in kernel
and pass the physical address to userspace through proc file.*/
#include <linux/version.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
#include <linux/seq_file.h>
#include <linux/percpu.h>
#include <linux/sched.h>

#define PROC_MEMSHARE_DIR              "memshare"
#define PROC_MEMSHARE_PHYADDR          "phymem_addr"
#define PROC_MEMSHARE_SIZE             "phymem_size"

/*alloc one page. 4096 bytes*/
#define PAGE_ORDER       0
/*this value can get from PAGE_ORDER*/
#define PAGES_NUMBER     1

static struct proc_dir_entry * proc_memshare_dir = NULL;
static struct proc_dir_entry * phymem_entry = NULL;
static struct proc_dir_entry * phymem_size_entry = NULL;

unsigned long kernel_memaddr = 0;
unsigned long kernel_memsize= 0;

static int  phymem_phyaddr_single_show(struct seq_file *s, void *p)
{
    return seq_printf(s, "%08lx\n", __pa(kernel_memaddr));
}

static int phymem_phyaddr_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file,phymem_phyaddr_single_show, NULL);
}

static struct file_operations phymem_phyaddr_ops =
{
    .open = phymem_phyaddr_seq_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int  phymem_size_single_show(struct seq_file *s, void *p)
{
    return seq_printf(s, "%lu\n", kernel_memsize);
}

static int phymem_size_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file,phymem_size_single_show, NULL);
}

static struct file_operations phymem_size_ops =
{
    .open = phymem_size_seq_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init memshare_init(void)
{
    /*build proc dir "memshare"and two proc files: phymem_addr, phymem_size in the dir*/
    proc_memshare_dir = proc_mkdir(PROC_MEMSHARE_DIR, NULL);

    phymem_entry = proc_create(PROC_MEMSHARE_PHYADDR,0,proc_memshare_dir,&phymem_phyaddr_ops);
    if(NULL == phymem_entry)
    {
        pr_err("%s phymem_entry proc_create err\n",__func__);
        return -1;
    }

    phymem_size_entry = proc_create(PROC_MEMSHARE_SIZE,0,proc_memshare_dir,&phymem_size_ops);
    if(NULL == phymem_size_entry)
    {
        pr_err("%s phymem_size_entry proc_create err\n",__func__);
        return -1;
    }

    kernel_memaddr = __get_free_pages(GFP_KERNEL,(PAGE_ORDER));
    if(!kernel_memaddr)
    {
       printk("Allocate memory failure!\n");
    }
    else
    {
        SetPageReserved(virt_to_page(kernel_memaddr));
        kernel_memsize = PAGES_NUMBER * PAGE_SIZE;
        printk("Allocate memory success!. The phy mem addr=%08lx, size=%lu\n",
            __pa(kernel_memaddr), kernel_memsize);
    }

    return 0;
}

static void __exit memshare_exit(void)
{
    printk("The content written by user is: %s/n", (unsigned char *) kernel_memaddr);
    ClearPageReserved(virt_to_page(kernel_memaddr));
    free_pages(kernel_memaddr, PAGE_ORDER);
    remove_proc_entry(PROC_MEMSHARE_PHYADDR,proc_memshare_dir);
    remove_proc_entry(PROC_MEMSHARE_SIZE,proc_memshare_dir);
    return;
}

module_init(memshare_init);
module_exit(memshare_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("fansaihua brucefan@foxmail.com");
MODULE_DESCRIPTION("Kernel memory share module.");

