#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */

typedef struct mylist {
    int num;
    struct list_head list;
} mylist_t;


static LIST_HEAD(list1); 
static LIST_HEAD(list2);

struct student{
    char name[20];  
    char sex;
}stu={"zhangsan",'m'};

static int __init hello_init(void)
{    
    mylist_t tmp_list1;
    mylist_t tmp_list2;
    struct student* p_sdu;
    INIT_LIST_HEAD(&list1);
    INIT_LIST_HEAD(&list2);
    tmp_list1.num = 1;
    tmp_list2.num = 2;
    list_add(&tmp_list1.list, &list1);
    list_del(&tmp_list1.list);
    list_add(&tmp_list1.list, &list1);
    list_add_tail(&tmp_list2.list, &list1);

    list_move_tail(&tmp_list2.list, &list2);
    list_splice_init(&list1, &list2);

    printk("%p\n",&stu);
    printk("%p\n",&stu.sex);
    p_sdu = container_of(&stu.sex,struct student, sex);
    printk("%p\n",p_sdu);
    return 0;
}

static void __exit hello_exit(void)
 {
    printk(KERN_ALERT "Goodbye, cruel world\n");
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

