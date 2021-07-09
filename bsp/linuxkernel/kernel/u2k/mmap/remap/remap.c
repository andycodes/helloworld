#include <asm/page.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h> 
#include <linux/uaccess.h>
#include <linux/gfp.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "remap"


unsigned long kernel_addr = 0;


void simple_vma_open(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA open, virt %lx, phys %lx\n",
			vma->vm_start, vma->vm_pgoff << PAGE_SHIFT);
}

void simple_vma_close(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA close.\n");
}

static struct vm_operations_struct simple_remap_vm_ops = {
	.open =  simple_vma_open,
	.close = simple_vma_close,
};

static int simple_remap_mmap(struct file *filp, struct vm_area_struct *vma)
{
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = __pa(kernel_addr)>>PAGE_SHIFT;
	
	if ( remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
		vma->vm_end - vma->vm_start,
		vma->vm_page_prot) )
		return -EAGAIN;
	
	vma->vm_ops = &simple_remap_vm_ops;
	vma->vm_flags |= VM_NONE;
	simple_vma_open(vma);
	
	return 0;	
}

static struct file_operations simple_remap_ops = {
	.owner   = THIS_MODULE,
	.mmap    = simple_remap_mmap,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &simple_remap_ops,
};

static int simple_init(void)
{
	int ret = misc_register(&misc);
	kernel_addr = __get_free_pages(GFP_KERNEL,1);
	SetPageReserved(virt_to_page(kernel_addr));
	return ret;
}

module_init(simple_init);

MODULE_AUTHOR("Jonathan Corbet");
MODULE_LICENSE("Dual BSD/GPL");

