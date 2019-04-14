#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>//定义了一些常用的函数原型
#include <linux/fs.h>//
#include <linux/errno.h>//一些出错的常量符号的宏
#include <linux/types.h>//定义了一些基本的数据类型。所有类型均定义为适当的数字类型长度。
#include <linux/fcntl.h>//文件控制选项头文件，
#include <linux/vmalloc.h>
#include <linux/hdreg.h>//定义了一些对硬盘控制器进行编程的一些命令常量符号。
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <asm/uaccess.h>


/*设备名称，段大小，设备大小等信息的定义*/
#define GAO_RD_DEV_NAME "gao_rd" //设备名称
#define GAO_RD_DEV_MAJOR 220  //主设备号
#define GAO_RD_MAX_DEVICE 2    //最大设备数
#define GAO_BLOCKSIZE  1024
#define GAO_RD_SECTOR_SIZE 512   //扇区大小
#define GAO_RD_SIZE (4*1024*1024)  //总大小
#define GAO_RD_SECTOR_TOTAL (GAO_RD_SIZE/GAO_RD_SECTOR_SIZE)  //总扇区数

typedef struct
{
    unsigned char *data;
    struct request_queue *queue;
    struct gendisk *gd;
}gao_rd_device;

static char *vdisk[GAO_RD_MAX_DEVICE];

static gao_rd_device device[GAO_RD_MAX_DEVICE];

static void gao_rd_make_request(struct request_queue *q, struct bio *bio)/*制造请求函数*/
{
    gao_rd_device *pdevice;    
    char *pVHDDData;
    char *pBuffer;
    struct bio_vec *bvec;
    int i;
    
    if(((bio->bi_sector*GAO_RD_SECTOR_SIZE) + bio->bi_size) > GAO_RD_SIZE)
    {
        bio_io_error(bio/*, bio->bi_size*/);
        return ;
    }
    else
    {
        
        pdevice = (gao_rd_device *) bio->bi_bdev->bd_disk->private_data;
        pVHDDData = pdevice->data + (bio->bi_sector*GAO_RD_SECTOR_SIZE);
        
        bio_for_each_segment(bvec, bio, i)/*循环遍历的宏*/
        {
            
            pBuffer = kmap(bvec->bv_page) + bvec->bv_offset;//kmap()函数？？？
            
            switch(bio_data_dir(bio))
            {
                case READA :    
                case READ : memcpy(pBuffer, pVHDDData, bvec->bv_len);
                break;
                case WRITE : memcpy(pVHDDData, pBuffer, bvec->bv_len);
                break;
                default : kunmap(bvec->bv_page);
                    bio_io_error(bio);
                    return ;            
            }
            
            kunmap(bvec->bv_page);
            pVHDDData += bvec->bv_len;
        }
        /*结束处理，并终止gao_rd_make_request函数*/
        bio_endio(bio, /*bio->bi_size, */0);
        return ;
    }    
}

static int gao_rd_open(struct block_device *bdev, fmode_t mode)
{
    return 0;
}

static int gao_rd_release(struct gendisk *disk, fmode_t mode)
{
    return 0;
}


//block_device_operations 结构体是对块设备操作的集合
static struct block_device_operations vrd_fops =
{
    .owner = THIS_MODULE,
    .open = gao_rd_open,
    .release = gao_rd_release,
};
int gao_rd_init(void)
{
    int i;    
    int err = -ENOMEM;
    for(i=0; i < GAO_RD_MAX_DEVICE; i++)
    {
        vdisk[i] = vmalloc(GAO_RD_SIZE);
    }    
    /*注册vrd设备驱动程序*/
    if(register_blkdev(GAO_RD_DEV_MAJOR, GAO_RD_DEV_NAME))//对此块设备进行注册
    {
        err = -EIO;
            goto out;
    }

    for(i = 0; i < GAO_RD_MAX_DEVICE; i++)
    {
        device[i].data = vdisk[i];    
        /*分配gendisk，gendisk结构题是注册block 设备的信息结构体*/
        device[i].gd = alloc_disk(1);

                if (!device[i].gd)
                goto out;

        device[i].queue = blk_alloc_queue(GFP_KERNEL);//GFP_KERNEL 分配正常的内核 
        if (!device[i].queue)
        {
                put_disk(device[i].gd);
                goto out;
            }

        blk_queue_make_request(device[i].queue, &gao_rd_make_request);
        blk_queue_max_hw_sectors(device[i].queue,GAO_BLOCKSIZE);//盘块大小
        
        device[i].gd->major = GAO_RD_DEV_MAJOR;
        device[i].gd->first_minor = i;
        device[i].gd->fops = &vrd_fops;//块设备操作结构体
        device[i].gd->queue = device[i].queue;
        device[i].gd->private_data = &device[i];
        sprintf(device[i].gd->disk_name, "gao_rd%c" , 'a'+i);//
        set_capacity(device[i].gd,GAO_RD_SECTOR_TOTAL);
        
        add_disk(device[i].gd);
    }
    
    printk("RAMDISK driver initialized!");
    
    return 0;
out:
   while (i--) {
       put_disk(device[i].gd);
       blk_cleanup_queue(device[i].queue);
   }
   return err;
}

void gao_rd_exit(void)
{
    int i;    
    for(i = 0; i < GAO_RD_MAX_DEVICE; i++)
    {
        del_gendisk(device[i].gd);//删除gendisk结构体    
        put_disk(device[i].gd);//减少gendisk结构体的引用计数
        blk_cleanup_queue(device[i].queue);
    }
    unregister_blkdev(GAO_RD_DEV_MAJOR, GAO_RD_DEV_NAME);
    for(i=0;i < GAO_RD_MAX_DEVICE; i++)
    {
        vfree(vdisk[i]);
    }
}
module_init(gao_rd_init);
module_exit(gao_rd_exit);

MODULE_LICENSE("Dual BSD/GPL");


/*
现在，在目录下回有一个gao_rd.ko的文件，
这个就是编译出来的可以加载的模块文件。
用insmod命令加载此模块后，
在/proc/modules文件里就会看到此模块已被加载。

5、测试驱动模块
       此驱动模块被加载到内核中后就可以利
       用此模块创建一个虚拟磁盘设备了。
       主要步骤如下：

       1）#mkdir  /root/Desktop/ramdisk/gao_rd

              这个命令的作用是创建一个文件夹，
              我们用这个文件夹作为虚拟磁盘设备的挂载点。     

       2）#mknod  /dev/gao_rd0 b 220 0

              创建一个块设备，指定块设备的主设
              备号是220，次设备号自动分配。现在，
              在/dev目录下就会多出一个块设备，名为gao_rd0。

       3）#mke2fs /dev/gao_rd0

              用ext2格式对此设备进行格式化。

       至此，就完成了一个虚拟磁盘设备的创建。

       4）#mount /dev/gao_rd0 /root/Desktop/ramdisk/gao_rd

           这个命令的作用是将刚刚创建的虚
           拟磁盘设备挂载到第一步创建的挂载点上。
           这样，这个虚拟磁盘就可以使用了。
           我们可以用ls命令来查看这块虚拟磁盘设备。


*/

