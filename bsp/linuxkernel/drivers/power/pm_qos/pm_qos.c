#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/pm_qos.h>

static struct pm_qos_request  test_pm_qos_req;

static int __init hello_init(void)
{
	int latency_req;

	pm_qos_add_request(&test_pm_qos_req, PM_QOS_CPU_DMA_LATENCY,
			   PM_QOS_DEFAULT_VALUE);

	latency_req = pm_qos_request(PM_QOS_CPU_DMA_LATENCY);

	pr_info("%d\n",latency_req);

	pm_qos_update_request(&test_pm_qos_req,175);

	return 0;
}

static void __exit hello_exit(void)
 {
    pm_qos_remove_request(&test_pm_qos_req);
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

