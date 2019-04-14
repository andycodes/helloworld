/* 
 * Sample disk driver, from the beginning. 
 */ 

#include <linux/module.h> 
#include <linux/moduleparam.h> 


#include <linux/init.h> 
#include <linux/sched.h> 
#include <linux/kernel.h>    /* printk() */ 
#include <linux/slab.h>        /* kmalloc() */ 
#include <linux/fs.h>        /* everything... */ 
#include <linux/errno.h>    /* error codes */ 
#include <linux/timer.h> 
#include <linux/types.h>    /* size_t */ 
#include <linux/fcntl.h>    /* O_ACCMODE */ 
#include <linux/hdreg.h>    /* HDIO_GETGEO */ 
#include <linux/kdev_t.h> 
#include <linux/vmalloc.h> 
#include <linux/genhd.h> 
#include <linux/blkdev.h> 
#include <linux/buffer_head.h>    /* invalidate_bdev */ 
#include <linux/bio.h> 

MODULE_LICENSE("Dual BSD/GPL"); 

static int sbull_major = 0; 
module_param(sbull_major, int, 0); 
static int hardsect_size = 512; 
module_param(hardsect_size, int, 0); 
static int nsectors = 25600;    /* How big the drive is */ 
module_param(nsectors, int, 0); 
static int ndevices = 1; 
module_param(ndevices, int, 0); 

/* 
 * The different "request modes" we can use. 
 */ 
enum { 
    RM_SIMPLE  = 0,    /* The extra-simple request function */ 
    RM_FULL    = 1,    /* The full-blown version */ 
    RM_NOQUEUE = 2,    /* Use make_request */ 
}; 
//static int request_mode = RM_FULL; 
static int request_mode = RM_SIMPLE; 
//static int request_mode = RM_SIMPLE; 
module_param(request_mode, int, 0); 

int debug = 1;

#define SKB_DBG(msg...) do { \
    if (debug) \
        printk(KERN_INFO msg); \
    } while (0)

/* 
 * Minor number and partition management. 
 */ 
#define SBULL_MINORS    16 
#define MINOR_SHIFT    4 
#define DEVNUM(kdevnum)    (MINOR(kdev_t_to_nr(kdevnum)) >> MINOR_SHIFT 

/* 
 * We can tweak our hardware sector size, but the kernel talks to us 
 * in terms of small sectors, always. 
 */ 
#define KERNEL_SECTOR_SIZE    512 

/* 
 * After this much idle time, the driver will simulate a media change. 
 */ 
#define INVALIDATE_DELAY    60*HZ 

/* 
 * The internal representation of our device. 
 */ 
struct sbull_dev { 
        int size;                       /* Device size in sectors */ 
        // data 是本程序模拟的块设备，是一片连续的虚拟空间 
        // 在初始化函数里分配的虚拟地址连续的内存空间 
        u8 *data;                       /* The data array */ 
        short users;                    /* How many users */ 
        short media_change;             /* Flag a media change? */ 
        spinlock_t lock;                /* For mutual exclusion */ 
        struct request_queue *queue;    /* The device request queue */ 
        struct gendisk *gd;             /* The gendisk structure */ 
        struct timer_list timer;        /* For simulated media changes */ 
}; 

static struct sbull_dev *Devices = NULL; 

/* 
 * Handle an I/O request. 
 */ 
static void sbull_transfer(struct sbull_dev *dev, unsigned long sector, 
        unsigned long nsect, char *buffer, int write) 
{ 
    unsigned long offset = sector*KERNEL_SECTOR_SIZE;     // 需要读写的扇区的偏移地址 
    unsigned long nbytes = nsect*KERNEL_SECTOR_SIZE;        // 需要读写的字节数 
    
    if ((offset + nbytes) > dev->size) {      // 判断输入参数是否合法，是否超出边界 
        printk (KERN_NOTICE "Beyond-end write (%ld %ld)\n", offset, nbytes); 
        return; 
    } 
    // 实际的读写操作 
    // 由于本程序是用一片连续的内存空间模拟块设备 
    // 所以这里对硬件(内存空间)的读写操作，就是复制内存 
    // 在具体点，就是下面的memcpy 
    // 具体的项目，需修改为具体的接口函数 
    if (write) 
        // 写 
        memcpy(dev->data + offset, buffer, nbytes); 
    else 
        // 读 
        memcpy(buffer, dev->data + offset, nbytes); 
} 

/*The simple form of the request function.*/ 

static void sbull_request(struct request_queue *q) 
{ 
    printk("sbull_request\n");
} 


/* 
 * Transfer a single BIO. 
 */ 
static int sbull_xfer_bio(struct sbull_dev *dev, struct bio *bio) 
{ 
    return 0; /* Always "succeed" */ 
} 

/* 
 * Transfer a full request. 
 */ 
static int sbull_xfer_request(struct sbull_dev *dev, struct request *req) 
{ 
    struct bio *bio; 
    int nsect = 0; 

    // steps through each bio that makes up a request. 
    // 遍历 
    __rq_for_each_bio(bio, req) { 
        sbull_xfer_bio(dev, bio); 
        nsect += bio->bi_size/KERNEL_SECTOR_SIZE; 
    } 
    return nsect; 
} 


/* 
 * Smarter request function that "handles clustering". 
 */ 
static void sbull_full_request(struct request_queue *q) 
{ 

} 

//The direct make request version 
static int sbull_make_request(struct request_queue *q, struct bio *bio) 
{ 
    struct sbull_dev *dev = q->queuedata; 
    int status; 

    status = sbull_xfer_bio(dev, bio); 
    bio_endio(bio, status); 
    return 0; 
} 


/* 
 * Open and close. 
 */ 

static int sbull_open(struct inode *inode, struct file *filp) 
{ 
    struct sbull_dev *dev = inode->i_bdev->bd_disk->private_data; 
    //printk("<0>" "fdfjdlksjfdlkj\n");    
    del_timer_sync(&dev->timer); 
    filp->private_data = dev; 
    spin_lock(&dev->lock); 
    if (! dev->users) 
        check_disk_change(inode->i_bdev); 
    dev->users++; 
    spin_unlock(&dev->lock); 
    return 0; 
} 

static int sbull_release(struct inode *inode, struct file *filp) 
{ 
    struct sbull_dev *dev = inode->i_bdev->bd_disk->private_data; 

    spin_lock(&dev->lock); 
    dev->users--; 

    if (!dev->users) { 
        dev->timer.expires = jiffies + INVALIDATE_DELAY; 
        add_timer(&dev->timer); 
    } 
    spin_unlock(&dev->lock); 

    return 0; 
} 

/* 
 * Look for a (simulated) media change. 
 */ 
int sbull_media_changed(struct gendisk *gd) 
{ 
    struct sbull_dev *dev = gd->private_data; 
    
    return dev->media_change; 
} 

/* 
 * Revalidate.  WE DO NOT TAKE THE LOCK HERE, for fear of deadlocking 
 * with open.  That needs to be reevaluated. 
 */ 
int sbull_revalidate(struct gendisk *gd) 
{ 
    struct sbull_dev *dev = gd->private_data; 
    
    if (dev->media_change) { 
        dev->media_change = 0; 
        memset (dev->data, 0, dev->size); 
    } 
    return 0; 
} 

/* 
 * The "invalidate" function runs out of the device timer; it sets 
 * a flag to simulate the removal of the media. 
 */ 
void sbull_invalidate(unsigned long ldev) 
{ 
    struct sbull_dev *dev = (struct sbull_dev *) ldev; 

    spin_lock(&dev->lock); 
    if (dev->users || !dev->data) 
        printk (KERN_WARNING "sbull: timer sanity check failed\n"); 
    else 
        dev->media_change = 1; 
    spin_unlock(&dev->lock); 
} 

/* 
 * The ioctl() implementation 
 */ 

int sbull_ioctl (struct inode *inode, struct file *filp, 
                 unsigned int cmd, unsigned long arg) 
{ 
    long size; 
    struct hd_geometry geo; 
    struct sbull_dev *dev = filp->private_data; 

    switch(cmd) { 
        case HDIO_GETGEO: 
            /* 
         * Get geometry: since we are a virtual device, we have to make 
         * up something plausible.  So we claim 16 sectors, four heads, 
         * and calculate the corresponding number of cylinders.  We set the 
         * start of data at sector four. 
         */ 
        //printk("<0>""-------------size=%d\n",size); 
        /****************for early version************/ 
        //size = dev->size*(hardsect_size/KERNEL_SECTOR_SIZE); 
        //printk("<0>""-------------size=%d\n",size); 
        //geo.cylinders = (size & ~0x3f) >> 6; 
        //geo.cylinders=2000; 
        //geo.heads = 4; 
        //geo.sectors = 16; 
        //geo.sectors=2560; 
        //geo.start = 0; 
        //if (copy_to_user((void __user *) arg, &geo, sizeof(geo))) 
        //    return -EFAULT; 
        return 0; 
    } 

    return -ENOTTY; /* unknown command */ 
} 

static int sbull_getgeo(struct block_device *bdev, struct hd_geometry *geo) 
{ 
    unsigned long size; 
    struct sbull_dev *pdev = bdev->bd_disk->private_data; 

    size = pdev->size; 
    geo->cylinders = (size & ~0x3f) >> 6; 
    geo->heads    = 4; 
    geo->sectors = 16; 
    geo->start = 0; 
    return 0; 
} 


/* 
 * The device operations structure. 
 */ 
static struct block_device_operations sbull_ops = { 
    .owner           = THIS_MODULE, 
    .open              = sbull_open, 
    .release      = sbull_release, 
    .media_changed   = sbull_media_changed, 
    .revalidate_disk = sbull_revalidate, 
    .ioctl             = sbull_ioctl, 
    .getgeo            = sbull_getgeo, 
}; 


/* 
 * Set up our internal device. 
 */ 
// 初始化设备结构体 static struct sbull_dev *Devices中的成员 
static void setup_device(struct sbull_dev *dev, int which) 
{ 
    /* 
     * Get some memory. 
     */ 
    memset (dev, 0, sizeof (struct sbull_dev)); 
    dev->size = nsectors*hardsect_size; 
    // 分配一片虚拟地址连续的内存空间，作为块设备。 
    dev->data = vmalloc(dev->size);   
    if (dev->data == NULL) { 
        printk (KERN_NOTICE "vmalloc failure.\n"); 
        return; 
    } 
    spin_lock_init(&dev->lock); 
    
    /* 
     * The timer which "invalidates" the device. 
     */ 
    init_timer(&dev->timer); 
    dev->timer.data = (unsigned long) dev; 
    dev->timer.function = sbull_invalidate; 
    
    /* 
     * The I/O queue, depending on whether we are using our own 
     * make_request function or not. 
     */ 
    switch (request_mode) { 
        case RM_NOQUEUE: 
        dev->queue = blk_alloc_queue(GFP_KERNEL); 
        if (dev->queue == NULL) 
            goto out_vfree; 
        blk_queue_make_request(dev->queue, sbull_make_request); 
        break; 

        case RM_FULL: 
        dev->queue = blk_init_queue(sbull_full_request, &dev->lock); 
        if (dev->queue == NULL) 
            goto out_vfree; 
        break; 

        default: 
        printk(KERN_NOTICE "Bad request mode %d, using simple\n", request_mode); 
            /* fall into.. */ 
    
        case RM_SIMPLE: 
        dev->queue = blk_init_queue(sbull_request, &dev->lock); 
        if (dev->queue == NULL) 
            goto out_vfree; 
        break; 
    } 

    dev->queue->queuedata = dev; 
    /* 
     * And the gendisk structure. 
     */ 
    dev->gd = alloc_disk(SBULL_MINORS); 
    if (! dev->gd) { 
        printk (KERN_NOTICE "alloc_disk failure\n"); 
        goto out_vfree; 
    } 
    dev->gd->major = sbull_major; 
    dev->gd->first_minor = which*SBULL_MINORS; 
    dev->gd->fops = &sbull_ops; 
    dev->gd->queue = dev->queue; 
    dev->gd->private_data = dev; 
    snprintf (dev->gd->disk_name, 32, "sbull%c", which + 'a'); 
    set_capacity(dev->gd, nsectors*(hardsect_size/KERNEL_SECTOR_SIZE)); 
    add_disk(dev->gd); 
    return; 

  out_vfree: 
    if (dev->data) 
        vfree(dev->data); 
} 

 void ramdisk_make_request(void)
 {
    SKB_DBG("ramdisk_make_request\n");
 }

static int __init sbull_init(void) 
{ 
    int i; 
    struct request_queue*  p_queue = NULL;
    
    sbull_major = register_blkdev(sbull_major, "sbull"); 
    if (sbull_major <= 0) { 
        printk(KERN_WARNING "sbull: unable to get major number\n"); 
        return -EBUSY; 
    } 
    /* 
     * Allocate the device array, and initialize each one. 
     */ 
    Devices = kmalloc(ndevices*sizeof (struct sbull_dev), GFP_KERNEL); 
    if (Devices == NULL) 
        goto out_unregister; 
    for (i = 0; i < ndevices; i++) 
        setup_device(Devices + i, i); 

    p_queue=blk_alloc_queue(GFP_KERNEL); //申请请求队列
    if(NULL == p_queue)
    {
            SKB_DBG("blk_alloc_queue\n");
            return -ENOMEM; 
    }

    blk_queue_make_request(p_queue,ramdisk_make_request);
    
    return 0; 

  out_unregister: 
    unregister_blkdev(sbull_major, "sbd"); 
 OUT1:
    return -ENOMEM; 
} 

static void sbull_exit(void) 
{ 
    int i; 

    for (i = 0; i < ndevices; i++) 
    { 
        struct sbull_dev *dev = Devices + i; 

        del_timer_sync(&dev->timer); 

        if (dev->gd) 
       { 
            del_gendisk(dev->gd); 
            put_disk(dev->gd); 
        }
        
        if (dev->queue) 
       { 
            if (request_mode == RM_NOQUEUE) 
            //    blk_put_queue(dev->queue); 
            kobject_put(&(dev->queue)->kobj); 
            else 
                blk_cleanup_queue(dev->queue); 
        }
        
        if (dev->data) 
            vfree(dev->data); 
    } 
    
    unregister_blkdev(sbull_major, "sbull"); 
    kfree(Devices); 
} 
    
module_init(sbull_init); 
module_exit(sbull_exit); 


#if 0
将模块插入内核（2.6.27） 
root@linuxidc :/source/workplace/test/sbull_linuxidc# insmod sbull.ko 
用lsmod查看模块是否成功插入内核 
root@linuxidc :/source/workplace/test/sbull_linuxidc# lsmod | grep sbu 
sbull                  13452  0 
出现上面结果，说明成功了 
用ls查看/dev下是否有sbull设备 
root@linuxidc :/source/workplace/test/sbull_linuxidc# ls /dev | grep sbu 
sbulla 
出现上面结果，说明有了，如果没有，用命令 
mknod /dev/sbulla b 254 0 
手动创建 
至此，已经有一个块设备了 
下面用fdisk对虚拟块设备分区 
root@linuxidc :/source/workplace/test/sbull_linuxidc# fdisk /dev/sbulla 
Device contains neither a valid DOS partition table, nor Sun, SGI or OSF disklabel 
Building a new DOS disklabel with disk identifier 0x14d0973f. 
Changes will remain in memory only, until you decide to write them. 
After that, of course, the previous content won't be recoverable. 

Warning: invalid flag 0x0000 of partition table 4 will be corrected by w(rite) 

Command (m for help): n        这里选择n，新建 
Command action 
   e   extended 
   p   primary partition (1-4)  这里选p，主分区 
p 
Partition number (1-4): 1   这里选1，第一个分区 
First cylinder (1-400, default 1): 1 
Last cylinder, +cylinders or +size{K,M,G} (1-400, default 400): 
Using default value 400 

Command (m for help): w  这里选w，保存并推出 
The partition table has been altered! 

Calling ioctl() to re-read partition table. 
Syncing disks. 
接着将其格式化为ext2 

root@linuxidc :/source/workplace/test/sbull_linuxidc# mkfs.ext2 /dev/sbulla1 
mke2fs 1.41.3 (12-Oct-2008) 
Filesystem label= 
OS type: Linux 
Block size=1024 (log=0) 
Fragment size=1024 (log=0) 
3200 inodes, 12792 blocks 
639 blocks (5.00%) reserved for the super user 
First data block=1 
Maximum filesystem blocks=13107200 
2 block groups 
8192 blocks per group, 8192 fragments per group 
1600 inodes per group 
Superblock backups stored on blocks: 
        8193 

Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done 

This filesystem will be automatically checked every 29 mounts or 
180 days, whichever comes first.  Use tune2fs -c or -i to override. 
新建一个文件夹，作为此处模拟的块设备的挂载点 
root@linuxidc :/source/workplace/test/sbull_linuxidc# ls /mnt/ 
hgfs  initrd 
root@linuxidc :/source/workplace/test/sbull_linuxidc# mkdir /mnt/sbulla1 
挂载 
root@linuxidc :/source/workplace/test/sbull_linuxidc# mount /dev/sbulla1 /mnt/sbulla1 
进入目录，新建一个文件，测试一下 
root@linuxidc :/source/workplace/test/sbull_linuxidc# cd /mnt/sbulla1/ 
root@linuxidc :/mnt/sbulla1# ls 
lost+found 
root@linuxidc :/mnt/sbulla1# echo hi > hello.c 
root@linuxidc :/mnt/sbulla1# ls 
hello.c  lost+found 
root@linuxidc :/mnt/sbulla1# cat hello.c 
hi 
root@linuxidc :/mnt/sbulla1# 
#endif
