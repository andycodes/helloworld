#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/i2c.h>

static int ds3232_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
    printk("i2c probe\n");
    return 0;
}


static int ds3232_remove(struct i2c_client *client)
{
    return 0;
}

static const struct i2c_device_id ds3232_id[] = {
	{ "ds3232", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, ds3232_id);

static struct i2c_driver ds3232_driver = {
	.driver = {
		.name = "ds3232",
		.owner = THIS_MODULE,
	},
	.probe = ds3232_probe,
	.remove = ds3232_remove,
	.id_table = ds3232_id,
};

module_i2c_driver(ds3232_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

