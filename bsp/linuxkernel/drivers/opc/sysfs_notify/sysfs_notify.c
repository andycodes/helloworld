#include <linux/init.h>
#include <linux/module.h>
//#include <linux/kernel.h>
//#include <linux/types.h>
//#include <linux/string.h>
//#include <linux/netfilter_ipv4.h>
//#include <asm/uaccess.h>
//#include <linux/notifier.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static int foo;
static int baz;
static int bar;

/*
 * The "foo" file where a static variable is read from and written to.
 */
static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
            char *buf)
{
    return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
             const char *buf, size_t count)
{
    sscanf(buf, "%du", &foo);
    return count;
}

static struct kobj_attribute foo_attribute =
    __ATTR(foo, 0666, foo_show, foo_store);

/*
 * More complex function where we determine which variable is being accessed by
 * looking at the attribute for the "baz" and "bar" files.
 */
static ssize_t b_show(struct kobject *kobj, struct kobj_attribute *attr,
              char *buf)
{
    int var;

    if (strcmp(attr->attr.name, "baz") == 0)
        var = baz;
    else
        var = bar;
    return sprintf(buf, "%d\n", var);
}

static ssize_t b_store(struct kobject *kobj, struct kobj_attribute *attr,
               const char *buf, size_t count)
{
    int var;

    sscanf(buf, "%du", &var);
    if (strcmp(attr->attr.name, "baz") == 0)
        baz = var;
    else
        bar = var;
    return count;
}

static struct kobj_attribute baz_attribute =
    __ATTR(baz, 0666, b_show, b_store);
static struct kobj_attribute bar_attribute =
    __ATTR(bar, 0666, b_show, b_store);


/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
static struct attribute *attrs[] = {
    &foo_attribute.attr,
    &baz_attribute.attr,
    &bar_attribute.attr,
    NULL,   /* need to NULL terminate the list of attributes */
};

/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specify a name, a subdirectory will be
 * created for the attributes with the directory being the name of the
 * attribute group.
 */
static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int __init init(void) {
    struct kobject *example_kobj = NULL;
    int retval;
/*
    struct kobject *kernel_kobj;
    EXPORT_SYMBOL_GPL(kernel_kobj);
*/
    /*kobject_fansaihua_example 作为 /sys/kernel/kobject_fansaihua_example对象目录[一个文件夹]*/
    example_kobj = kobject_create_and_add("kobject_fansaihua_example", kernel_kobj);
    if(NULL == example_kobj) {
        return -ENOMEM;
    }

    retval = sysfs_create_group(example_kobj, &attr_group);
    if (retval) {
        /*操作kobject的一个重要的
        函数是为包含它的对象设
        置引用计数，只要对象的
        引用计数不为0，那么对
        象就不能被释放。*/
        /*kobject_put来减少其引用计数(-1)，
        并且当引用计数为0时，
        kobject_put还会调用
        kobject_cleanup来释放该对象。另外，注意*/
            kobject_put(example_kobj);
        }

	sysfs_notify(example_kobj, NULL, "actual_brightness");

	return 0;
}

static void __exit fini(void)
{

}

module_init(init);
module_exit(fini);

MODULE_AUTHOR("fansaihua");
MODULE_LICENSE("Dual BSD/GPL");

