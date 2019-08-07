#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timekeeping.h>

void print_time(void)
{
	time64_t local_time;
	struct tm tm;

	/*√Î= jiffies/HZ*/
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);
	msleep(1000);
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);
	ssleep(1);
	pr_info("jiffies/HZ %lu\n",jiffies/HZ);

	local_time = ktime_get_real_seconds();
	time64_to_tm(local_time, -sys_tz.tz_minuteswest * 60, &tm);
	pr_info("%04ld.%02d.%02d %02d:%02d:%02d\n",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		 tm.tm_hour, tm.tm_min, tm.tm_sec);


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

