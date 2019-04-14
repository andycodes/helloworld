#include <linux/init.h>
#include <linux/module.h>
#include <linux/mount.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/fd.h>
#include <linux/fs_struct.h>
#include <asm/uaccess.h>
#include <linux/nfs_fs.h>
#include <linux/nfs_fs_sb.h>
#include <linux/nfs_mount.h>
#include <linux/syscalls.h>/*sys_mount*/


/*
*在内核挂载文件系统
*sys_mkdir("/app",S_IRWXU|S_IRWXU|S_IRWXG|SIRWXO);
*sys_mkdir("/dev/block",....);
*sys_mknod("/dev/block/mtdblock1",S_IFBLK|S_IRWXU|S_IRWXG|S_IRWXO,0xlf01);
*sys_mount("/dev/block/mtdblock1","/app","yaffs2",0,NULL);
*/
static int __init mount_init(void)
{
	int err;
    char options[] = "mode=0755";
    char* mntdir = "dev";
    printk("proc fs module_init\n");
    err = sys_mount("devtmpfs", (char *)mntdir, "devtmpfs", MS_SILENT, options);
    return 0;
}

static void  __exit mount_exit(void)
{
    printk("proc ko exit\n");
}

module_init(mount_init);
module_exit(mount_exit);

MODULE_AUTHOR("fansaihua");
MODULE_DESCRIPTION("Proc Test Module");
MODULE_LICENSE("GPL");

