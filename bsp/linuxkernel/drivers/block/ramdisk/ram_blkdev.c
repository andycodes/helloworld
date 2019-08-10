#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>//������һЩ���õĺ���ԭ��
#include <linux/fs.h>//
#include <linux/errno.h>//һЩ����ĳ������ŵĺ�
#include <linux/types.h>//������һЩ�������������͡��������;�����Ϊ�ʵ����������ͳ��ȡ�
#include <linux/fcntl.h>//�ļ�����ѡ��ͷ�ļ���
#include <linux/vmalloc.h>
#include <linux/hdreg.h>//������һЩ��Ӳ�̿��������б�̵�һЩ��������š�
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <asm/uaccess.h>


/*�豸���ƣ��δ�С���豸��С����Ϣ�Ķ���*/
#define GAO_RD_DEV_NAME "gao_rd" //�豸����
#define GAO_RD_DEV_MAJOR 220  //���豸��
#define GAO_RD_MAX_DEVICE 2    //����豸��
#define GAO_BLOCKSIZE  1024
#define GAO_RD_SECTOR_SIZE 512   //������С
#define GAO_RD_SIZE (4*1024*1024)  //�ܴ�С
#define GAO_RD_SECTOR_TOTAL (GAO_RD_SIZE/GAO_RD_SECTOR_SIZE)  //��������

typedef struct
{
    unsigned char *data;
    struct request_queue *queue;
    struct gendisk *gd;
}gao_rd_device;

static char *vdisk[GAO_RD_MAX_DEVICE];

static gao_rd_device device[GAO_RD_MAX_DEVICE];

static void gao_rd_make_request(struct request_queue *q, struct bio *bio)/*����������*/
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
        
        bio_for_each_segment(bvec, bio, i)/*ѭ�������ĺ�*/
        {
            
            pBuffer = kmap(bvec->bv_page) + bvec->bv_offset;//kmap()����������
            
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
        /*������������ֹgao_rd_make_request����*/
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


//block_device_operations �ṹ���ǶԿ��豸�����ļ���
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
    /*ע��vrd�豸��������*/
    if(register_blkdev(GAO_RD_DEV_MAJOR, GAO_RD_DEV_NAME))//�Դ˿��豸����ע��
    {
        err = -EIO;
            goto out;
    }

    for(i = 0; i < GAO_RD_MAX_DEVICE; i++)
    {
        device[i].data = vdisk[i];    
        /*����gendisk��gendisk�ṹ����ע��block �豸����Ϣ�ṹ��*/
        device[i].gd = alloc_disk(1);

                if (!device[i].gd)
                goto out;

        device[i].queue = blk_alloc_queue(GFP_KERNEL);//GFP_KERNEL �����������ں� 
        if (!device[i].queue)
        {
                put_disk(device[i].gd);
                goto out;
            }

        blk_queue_make_request(device[i].queue, &gao_rd_make_request);
        blk_queue_max_hw_sectors(device[i].queue,GAO_BLOCKSIZE);//�̿��С
        
        device[i].gd->major = GAO_RD_DEV_MAJOR;
        device[i].gd->first_minor = i;
        device[i].gd->fops = &vrd_fops;//���豸�����ṹ��
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
        del_gendisk(device[i].gd);//ɾ��gendisk�ṹ��    
        put_disk(device[i].gd);//����gendisk�ṹ������ü���
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
���ڣ���Ŀ¼�»���һ��gao_rd.ko���ļ���
������Ǳ�������Ŀ��Լ��ص�ģ���ļ���
��insmod������ش�ģ���
��/proc/modules�ļ���ͻῴ����ģ���ѱ����ء�

5����������ģ��
       ������ģ�鱻���ص��ں��к�Ϳ�����
       �ô�ģ�鴴��һ����������豸�ˡ�
       ��Ҫ�������£�

       1��#mkdir  /root/Desktop/ramdisk/gao_rd

              �������������Ǵ���һ���ļ��У�
              ����������ļ�����Ϊ��������豸�Ĺ��ص㡣     

       2��#mknod  /dev/gao_rd0 b 220 0

              ����һ�����豸��ָ�����豸������
              ������220�����豸���Զ����䡣���ڣ�
              ��/devĿ¼�¾ͻ���һ�����豸����Ϊgao_rd0��

       3��#mke2fs /dev/gao_rd0

              ��ext2��ʽ�Դ��豸���и�ʽ����

       ���ˣ��������һ����������豸�Ĵ�����

       4��#mount /dev/gao_rd0 /root/Desktop/ramdisk/gao_rd

           �������������ǽ��ոմ�������
           ������豸���ص���һ�������Ĺ��ص��ϡ�
           ���������������̾Ϳ���ʹ���ˡ�
           ���ǿ�����ls�������鿴�����������豸��


*/

