#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/netfilter_ipv4.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/notifier.h>




static int __init init(void)
{
    char *envp[2];
    struct kobject kobj;
    envp[0] = "SOURCE=hotkey";
    envp[1] = NULL;
    kobject_uevent_env(&kobj, KOBJ_ADD, envp);
    kobject_uevent(&kobj, KOBJ_CHANGE);
    return 0;
}

static void __exit fini(void)
{

}

module_init(init);
module_exit(fini);

MODULE_AUTHOR("fansaihua");
MODULE_LICENSE("Dual BSD/GPL");

