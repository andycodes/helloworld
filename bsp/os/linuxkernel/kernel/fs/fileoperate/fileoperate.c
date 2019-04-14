#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/syscalls.h>


#if 0
SYSCALL_DEFINE3(write, unsigned int, fd, const char __user *, buf,
		size_t, count)
{
	struct fd f = fdget(fd);
	ssize_t ret = -EBADF;

	if (f.file) {
		loff_t pos = file_pos_read(f.file);
		ret = vfs_write(f.file, buf, count, &pos);
		file_pos_write(f.file, pos);
		fdput(f);
	}

	return ret;
}
#endif

#define KERNEL_FILE "/project/kernel_file"
 

static char buf[] = "HELLO FANSAIHUA\n"; 
char buf1[24] = {0}; 
  
int   fs_operations(void) 
{ 
   struct file *fp; 
    mm_segment_t old_fs; 
    loff_t pos; 
    size_t f_size = 0;
    size_t r_size = 0;
    
    old_fs = get_fs(); 
    set_fs(KERNEL_DS); 
    //set_fs(get_ds); //get_ds获得kernel的内存访问地址范围ARM LINUX 4G
    
    /*O_CREAT: IF not exist ,Creat it*/
    fp = filp_open(KERNEL_FILE, O_RDWR | O_CREAT, 0644); 
    
   if (IS_ERR(fp)) 
    { 
       printk("create file error:%s\n",KERNEL_FILE); 
       goto ERROR_EXIT;
    } 
   

    pos = 4; 

///////////////////////////////////////////////
/*write*/    
/*以下两种方法都可以
**建议使用vfs_write
*/
#if 1
    printk("fp->f_pos %lld\n", fp->f_pos); 
    vfs_write(fp, buf, sizeof(buf), &pos);
//    vfs_write(fp, buf, sizeof(buf), &fp->f_pos);
    printk("fp->f_pos %lld\n", fp->f_pos); 
#else
    fp->f_op->write(fp, (char *)buf, sizeof(buf), &fp->f_pos);
#endif

/*read*/
    pos = 0; 
    r_size=vfs_read(fp, buf1, sizeof(buf), &pos);
    if(r_size != sizeof(buf))
        {
            printk("vfs_read error\n");
        }
    
    printk("read: %s\n", buf1); 

/*get file size*/
    f_size = vfs_llseek(fp, 0, SEEK_END);//SEEK_SET为定位到文件头
    printk(" The file size is %d\n", f_size);
    
    filp_close(fp, NULL); 
    set_fs(old_fs); 
    
   return 0; 
  ERROR_EXIT:
    {
         set_fs(old_fs); 
          return -1; 
    }
} 

int __init kernel_fs_operate_init(void)
{
   (void)fs_operations();
    return 0;//module_init 必须要RETURN ;不然INSMOD 的时候报错
}

void __exit hello_exit(void) 
{ 
   //sys_unlink(KERNEL_FILE);
} 
 
module_init(kernel_fs_operate_init); 
module_exit(hello_exit); 

MODULE_LICENSE("GPL");

