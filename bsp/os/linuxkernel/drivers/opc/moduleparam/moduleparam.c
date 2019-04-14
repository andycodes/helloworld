#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static char *who;
static int  times;

static int __init hello_init(void)
{
	int i;

	for(i = 1;i <= times;i++)
		printk("%d  %s!\n",i,who);

	return 0;
}
static void __exit hello_exit(void)
{
	 printk("Goodbye,%s!\n",who);
}


/*
perm:

    权限,有:

    #define S_IRUSR    00400 文件所有者可读
           #define S_IWUSR   00200 文件所有者可写
           #define S_IXUSR    00100 文件所有者可执行
           #define S_IRGRP   00040 与文件所有者同组的用户可读
           #define S_IWGRP  00020
           #define S_IXGRP   00010
           #define S_IROTH   00004 与文件所有者不同组的用户可读
           #define S_IWOTH  00002
           #define S_IXOTH   00001

    将数字最后三位转化为二进制:xxx xxx xxx,高位往低位依次看,第一位为1表示文件所有者可读,第二位为1表示文件所有者可写,第三位为1表示文件所有者可执行;接下来三位表示文件所有者同组成员的权限;再下来三位为不同组用戶权限.

    00400 ==> 400 ==> 100 000 000

*/
module_param(who,charp,0644);
module_param(times,int,0644);


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

/*
*insmod  moduleparam.ko  who=fansaihua times=8
*
*/

/*
[  588.002049] 1  fansaihua!
[  588.002059] 2  fansaihua!
[  588.002066] 3  fansaihua!
[  588.002073] 4  fansaihua!
[  588.002080] 5  fansaihua!
[  588.002087] 6  fansaihua!
[  588.002094] 7  fansaihua!
[  588.002101] 8  fansaihua!

*/

