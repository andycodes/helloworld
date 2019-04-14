#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/delay.h>

void print_time(void)
{
	struct timeval tv;
	do_gettimeofday(&tv);
	pr_info("tv_sec %ld,tv_usec: %06ld\n", tv.tv_sec, tv.tv_usec);
	/*√Î= jiffies/HZ*/
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);
	msleep(1000);
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);
	ssleep(1);
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);
}

static int __init mytimer_init(void)
{
    print_time();
    return 0;
}

static void __exit mytimer_exit(void)
{

}

module_init(mytimer_init);
module_exit(mytimer_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FANSAIHUA");

