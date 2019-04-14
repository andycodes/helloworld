#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/thermal.h>


struct andy_thermal_dev
{
    struct thermal_zone_device *tz;
    enum thermal_device_mode mode;
};

struct andy_thermal_dev  g_andy_thermal_dev;

static int andy_cdev_bind(struct thermal_zone_device *thermal,
		struct thermal_cooling_device *cdev)
{
	int ret = -EINVAL;
       unsigned long max_state, upper, lower;
       int trips = 0;


	cdev->ops->get_max_state(cdev, &max_state);
       pr_err("%s max_state %lu\n",__func__,max_state);
       
    	upper =  max_state ;
       lower = 0;
       trips = 0;
       
	ret = thermal_zone_bind_cooling_device(thermal, trips, cdev,
			upper, lower);
       pr_err("%s ret %d\n",__func__,ret);

	return 0;
}

static int andy_cdev_unbind(struct thermal_zone_device *thermal,
		struct thermal_cooling_device *cdev)
{
	int ret = -EINVAL;
       int trips = 0;

    	ret = thermal_zone_unbind_cooling_device(thermal, trips, cdev);

	return ret;
}

static int andy_get_temp(struct thermal_zone_device *thermal,
			  unsigned long *temp)
{
    *temp  = 37000;
    pr_err("%s temp %lu\n",__func__,*temp);
    return 0;
}

static int db8500_sys_get_trend(struct thermal_zone_device *thermal,
		int trip, enum thermal_trend *trend)
{

	*trend = 1;

	return 0;
}

/* Callback to get thermal zone mode */
static int andy_get_mode(struct thermal_zone_device *thermal,
		enum thermal_device_mode *mode)
{

	*mode = g_andy_thermal_dev.mode;

	return 0;
}

/* Callback to set thermal zone mode */
static int andy_set_mode(struct thermal_zone_device *thermal,
		enum thermal_device_mode mode)
{
       g_andy_thermal_dev.mode = mode;
	return 0;
}

static int rcar_thermal_get_trip_type(struct thermal_zone_device *zone,
				      int trip, enum thermal_trip_type *type)
{
	switch (trip) {
	case 0: /* +90 <= temp */
		*type = THERMAL_TRIP_CRITICAL;
		break;
	default:
		pr_err("rcar driver trip error\n");
		return -EINVAL;
	}

	return 0;
}

static int rcar_thermal_get_trip_temp(struct thermal_zone_device *zone,
				      int trip, unsigned long *temp)
{
	switch (trip) {
	case 0: /* +90 <= temp */
		*temp = 90*1000;
		break;
	default:
		pr_err("rcar driver trip error\n");
		return -EINVAL;
	}

	return 0;
}

/* Callback to get critical trip point temperature */
static int db8500_sys_get_crit_temp(struct thermal_zone_device *thermal,
		unsigned long *temp)
{
    return 0;
}

static int rcar_thermal_notify(struct thermal_zone_device *zone,
			       int trip, enum thermal_trip_type type)
{

	switch (type) {
	case THERMAL_TRIP_CRITICAL:
		/* FIXME */
		pr_err("Thermal reached to critical temperature\n");
		break;
	default:
		break;
	}

	return 0;
}

static struct thermal_zone_device_ops andy_thermal_ops = {
	.bind = andy_cdev_bind,
	.unbind = andy_cdev_unbind,
       .get_temp = andy_get_temp,
	.get_trend = db8500_sys_get_trend,
	.get_mode = andy_get_mode,
	.set_mode = andy_set_mode,
     	.get_trip_type	= rcar_thermal_get_trip_type,
     	.get_trip_temp = rcar_thermal_get_trip_temp,
     	.get_crit_temp = db8500_sys_get_crit_temp,
	.notify		= rcar_thermal_notify,

};

static struct thermal_zone_params andy_thermal_params = {
	.governor_name = "user_space",
	.no_hwmon = true,
};

static int __init hello_init(void)
{
	g_andy_thermal_dev.tz = thermal_zone_device_register("andy_thermal", 1, 0,
					       NULL, &andy_thermal_ops, 
					       &andy_thermal_params, 0, 0);
	if (IS_ERR(g_andy_thermal_dev.tz)) {
		pr_err("Failed to register thermal zone device\n");
		return PTR_ERR(g_andy_thermal_dev.tz);
	}

	return 0;
}

static void __exit hello_exit(void)
 {
    thermal_zone_device_unregister(g_andy_thermal_dev.tz);
    printk(KERN_ALERT "Goodbye, cruel world\n");
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

