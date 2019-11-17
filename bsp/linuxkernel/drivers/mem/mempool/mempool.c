#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/mempool.h>
#include <linux/gfp.h>
#include <linux/delay.h>

struct my_mempool{
    int val;
};
#define MY_MIN_MEMPOOL 20

struct kmem_cache * mempool_cachep = NULL;
mempool_t * my_pool = NULL;
struct my_mempool * mempool_object = NULL;

static int __init mempool_init(void){
    printk("memory pool test module init!\n");
    mempool_cachep = kmem_cache_create("mempool_cachep", sizeof(struct my_mempool), 0, 0, NULL);
    if(!mempool_cachep)
        return -ENOMEM;
    my_pool = mempool_create(MY_MIN_MEMPOOL, mempool_alloc_slab, mempool_free_slab, mempool_cachep);
    if(!my_pool)
        return -ENOMEM;
    mempool_object = (struct my_mempool *)mempool_alloc(my_pool, GFP_KERNEL);
    if(mempool_object)
        printk("one object has been allocated!\n");
    else
        goto fail;
    printk("memory pool curr_nr is %d, min_nr is %d\n", my_pool->curr_nr, my_pool->min_nr);
    mempool_free(mempool_object, my_pool);
    return 0;
fail:
    mempool_destroy(my_pool);
    kmem_cache_destroy(mempool_cachep);
    return -1;
}

static void __exit mempool_exit(void){
    printk("memory pool test module exit!\n");
    if(my_pool){
        mempool_destroy(my_pool);
        printk("mempool has been destroy!\n");
    }

    if(mempool_cachep){
        kmem_cache_destroy(mempool_cachep);
        printk("cache has been destroy!\n");
    }
}

module_init(mempool_init);
module_exit(mempool_exit);
MODULE_AUTHOR("embeddedlwp@163.com");
MODULE_LICENSE("GPL");

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

