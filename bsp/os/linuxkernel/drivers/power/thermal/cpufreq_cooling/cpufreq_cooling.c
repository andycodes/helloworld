/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/cpu_cooling.h>
#include <linux/cpufreq.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

struct thermal_cooling_device * g_cdev = NULL;

static int andy_cpufreq_cooling_probe(void)
{
	struct cpumask mask_val;

	/* make sure cpufreq driver has been initialized */
	if (!cpufreq_frequency_get_table(0))
		return -EPROBE_DEFER;

	cpumask_set_cpu(0, &mask_val);
	g_cdev = cpufreq_cooling_register(&mask_val);

	if (IS_ERR(g_cdev)) {
		pr_err("Failed to register cooling device\n");
		return PTR_ERR(g_cdev);
	}

	return 0;
}

static void __exit andy_cpufreq_cooling_exit(void)
 {
    cpufreq_cooling_unregister(g_cdev);
 }

module_init(andy_cpufreq_cooling_probe);
module_exit(andy_cpufreq_cooling_exit);

MODULE_AUTHOR("fansaihua");
MODULE_DESCRIPTION("ANDY cpufreq cooling driver");
MODULE_LICENSE("GPL");
