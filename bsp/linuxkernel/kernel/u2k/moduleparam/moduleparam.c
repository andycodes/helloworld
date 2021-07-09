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

    Ȩ��,��:

    #define S_IRUSR    00400 �ļ������߿ɶ�
           #define S_IWUSR   00200 �ļ������߿�д
           #define S_IXUSR    00100 �ļ������߿�ִ��
           #define S_IRGRP   00040 ���ļ�������ͬ����û��ɶ�
           #define S_IWGRP  00020
           #define S_IXGRP   00010
           #define S_IROTH   00004 ���ļ������߲�ͬ����û��ɶ�
           #define S_IWOTH  00002
           #define S_IXOTH   00001

    �����������λת��Ϊ������:xxx xxx xxx,��λ����λ���ο�,��һλΪ1��ʾ�ļ������߿ɶ�,�ڶ�λΪ1��ʾ�ļ������߿�д,����λΪ1��ʾ�ļ������߿�ִ��;��������λ��ʾ�ļ�������ͬ���Ա��Ȩ��;��������λΪ��ͬ���Ñ�Ȩ��.

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

