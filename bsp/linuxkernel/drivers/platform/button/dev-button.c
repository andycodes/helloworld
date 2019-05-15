/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008 Florian Fainelli <florian@openwrt.org>
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <bcm63xx_cpu.h>

static struct resource button_resources[] = {
	{
		.start		= -1, /* filled at runtime */
		.end		= -1, /* filled at runtime */
		.flags		= IORESOURCE_MEM,
	},
};

static struct platform_device button_device = {
	.name		= "buttons",//bcm63xx-wdt
	.id		= -1,
	.num_resources	= ARRAY_SIZE(button_resources),
	.resource	= button_resources,
};

int __init buttons_register(void)
{
	button_resources[0].start = bcm63xx_regset_address(RSET_WDT);
	button_resources[0].end = button_resources[0].start;
	button_resources[0].end += RSET_WDT_SIZE - 1;

	return platform_device_register(&button_device);
}

arch_initcall(buttons_register);

