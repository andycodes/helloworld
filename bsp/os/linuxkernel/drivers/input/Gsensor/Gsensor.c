/*
 *  Driver for Freescale's 3-Axis Accelerometer MMA8450
 *
 *  Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input-polldev.h>
#include <linux/of_device.h>
#include <linux/random.h>
#include <linux/hwmon-sysfs.h>


#define MMA8450_DRV_NAME	"mma8450"

#define MODE_CHANGE_DELAY_MS	100
#define POLL_INTERVAL		100
#define POLL_INTERVAL_MAX	500

/* register definitions */
#define MMA8450_STATUS		0x00
#define MMA8450_STATUS_ZXYDR	0x08

#define MMA8450_OUT_X8		0x01
#define MMA8450_OUT_Y8		0x02
#define MMA8450_OUT_Z8		0x03

#define MMA8450_OUT_X_LSB	0x05
#define MMA8450_OUT_X_MSB	0x06
#define MMA8450_OUT_Y_LSB	0x07
#define MMA8450_OUT_Y_MSB	0x08
#define MMA8450_OUT_Z_LSB	0x09
#define MMA8450_OUT_Z_MSB	0x0a

#define MMA8450_XYZ_DATA_CFG	0x16

#define MMA8450_CTRL_REG1	0x38
#define MMA8450_CTRL_REG2	0x39

static int debug;
#define DBG(msg...) do { \
	if (debug) \
		printk(KERN_INFO msg); \
	} while (0)

/* mma8450 status */
struct mma8450 {
	struct i2c_client	*client;
	struct input_polled_dev	*idev;
};


struct i2c_client  i2c_client_tmp;
u8 orientation ;

static int mma8450_read(struct mma8450 *m, unsigned off)
{
	return MMA8450_STATUS_ZXYDR;
}

static int mma_read_xyz(int i, s8* off)
{
	return MMA8450_STATUS_ZXYDR;
}

static int mma8450_write(struct mma8450 *m, unsigned off, u8 v)
{
	return 0;
}

static int mma8450_read_block(struct mma8450 *m, unsigned off,
			      u8 *buf, size_t size)
{
    get_random_bytes(buf,size);
    return 0;
}

void mma7660_read_tilt(u8* data)
{

}
ssize_t show_xyz_force(struct device *dev, struct device_attribute *attr, char *buf)  
{  
    int i;  
    s8 xyz[3]={0};  
  
    for (i=0; i<3; i++)  
        mma_read_xyz(i, &xyz[i]);  
  
    return sprintf(buf, "(%d,%d,%d)\n", xyz[0], xyz[1], xyz[2]);  
} 

ssize_t show_axis_force(struct device *dev, struct device_attribute *attr, char *buf)  
{  
    s8 force = 0;  
    int n = to_sensor_dev_attr(attr)->index;  
    mma_read_xyz(n, &force);  
    return sprintf(buf, "%d\n", force);  
}  

ssize_t show_orientation(struct device *dev, struct device_attribute *attr, char *buf)  
{  
    int result;  
    u8 tilt = 0, new_orientation;  
  
    mma7660_read_tilt(&tilt);  
    DBG("tilt [0x%x]\n", tilt);  
    new_orientation = tilt & 0x1f;  
    if (orientation!=new_orientation)  
        orientation = new_orientation;  
  
    switch ((orientation>>2)&0x07) {  
        case 1:  
            result = sprintf(buf, "Left\n");  
            break;  
        case 2:  
            result = sprintf(buf, "Right\n");  
            break;  
        case 5:  
            result = sprintf(buf, "Downward\n");  
            break;  
        case 6:  
            result = sprintf(buf, "Upward\n");  
            break;  
        default:  
            switch(orientation & 0x03) {  
                case 1:  
                    result = sprintf(buf, "Front\n");  
                    break;  
                case 2:  
                    result = sprintf(buf, "Back\n");  
                    break;  
                default:  
                    result = sprintf(buf, "Unknown\n");  
        }  
    }  
    return result;  
}   

static SENSOR_DEVICE_ATTR(all_axis_force, S_IRUGO, show_xyz_force, NULL, 0);  
static SENSOR_DEVICE_ATTR(x_axis_force, S_IRUGO, show_axis_force, NULL, 0);  
static SENSOR_DEVICE_ATTR(y_axis_force, S_IRUGO, show_axis_force, NULL, 1);  
static SENSOR_DEVICE_ATTR(z_axis_force, S_IRUGO, show_axis_force, NULL, 2);  
static SENSOR_DEVICE_ATTR(orientation, S_IRUGO, show_orientation, NULL, 0);  

static struct attribute* mma_sensor_attrs[] =  
{  
    &sensor_dev_attr_all_axis_force.dev_attr.attr,  
    &sensor_dev_attr_x_axis_force.dev_attr.attr,  
    &sensor_dev_attr_y_axis_force.dev_attr.attr,  
    &sensor_dev_attr_z_axis_force.dev_attr.attr,  
    &sensor_dev_attr_orientation.dev_attr.attr,  
    NULL  
};  

static const struct attribute_group mma_sensor_group =  
{  
    .attrs = mma_sensor_attrs,  
};  

static void mma8450_poll(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;
	int x, y, z;
	int ret;
	u8 buf[6];

	ret = mma8450_read(m, MMA8450_STATUS);
	if (ret < 0)
		return;

	if (!(ret & MMA8450_STATUS_ZXYDR))
		return;

	ret = mma8450_read_block(m, MMA8450_OUT_X_LSB, buf, sizeof(buf));
	if (ret < 0)
		return;

	x = ((int)(s8)buf[1] << 4) | (buf[0] & 0xf);
	y = ((int)(s8)buf[3] << 4) | (buf[2] & 0xf);
	z = ((int)(s8)buf[5] << 4) | (buf[4] & 0xf);

	input_report_abs(dev->input, ABS_X, x);
	input_report_abs(dev->input, ABS_Y, y);
	input_report_abs(dev->input, ABS_Z, z);
	input_sync(dev->input);
}

/* Initialize the MMA8450 chip */
static void mma8450_open(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;
	int err;

	/* enable all events from X/Y/Z, no FIFO */
	err = mma8450_write(m, MMA8450_XYZ_DATA_CFG, 0x07);
	if (err)
		return;

	/*
	 * Sleep mode poll rate - 50Hz
	 * System output data rate - 400Hz
	 * Full scale selection - Active, +/- 2G
	 */
	err = mma8450_write(m, MMA8450_CTRL_REG1, 0x01);
	if (err < 0)
		return;

	msleep(MODE_CHANGE_DELAY_MS);
}

static void mma8450_close(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;

	mma8450_write(m, MMA8450_CTRL_REG1, 0x00);
	mma8450_write(m, MMA8450_CTRL_REG2, 0x01);
}

/*
 * I2C init/probing/exit functions
 */
static int mma8450_probe(struct i2c_client *c,
				   const struct i2c_device_id *id)
{
	struct input_polled_dev *idev;
	struct mma8450 *m;
	int err;
    int result;

	m = kzalloc(sizeof(struct mma8450), GFP_KERNEL);
	idev = input_allocate_polled_device();
	if (!m || !idev) {
		err = -ENOMEM;
		goto err_free_mem;
	}

	m->client = c;
	m->idev = idev;

	idev->private		= m;
	idev->input->name	= MMA8450_DRV_NAME;
	idev->input->id.bustype	= BUS_I2C;
	idev->poll		= mma8450_poll;
	idev->poll_interval	= POLL_INTERVAL;
	idev->poll_interval_max	= POLL_INTERVAL_MAX;
	idev->open		= mma8450_open;
	idev->close		= mma8450_close;

	__set_bit(EV_ABS, idev->input->evbit);
	input_set_abs_params(idev->input, ABS_X, -2048, 2047, 32, 32);
	input_set_abs_params(idev->input, ABS_Y, -2048, 2047, 32, 32);
	input_set_abs_params(idev->input, ABS_Z, -2048, 2047, 32, 32);

	err = input_register_polled_device(idev);
	if (err) {
		dev_err(&c->dev, "failed to register polled input device\n");
		goto err_free_mem;
	}

    result = sysfs_create_group(&c->dev.kobj, &mma_sensor_group);  
    if (result != 0) 
    {  
        dev_err(&c->dev,"sysfs_create_group err\n");  
        goto err_free_mem;  
    }  

	return 0;

err_free_mem:
	input_free_polled_device(idev);
	kfree(m);
	return err;
}

static int mma8450_remove(struct i2c_client *c)
{
	struct mma8450 *m = i2c_get_clientdata(c);
	struct input_polled_dev *idev = m->idev;

	input_unregister_polled_device(idev);
	input_free_polled_device(idev);
	kfree(m);

	return 0;
}


static int __init hello_init(void)
{
    mma8450_remove(&i2c_client_tmp);
 printk(KERN_ALERT "Hello, world!\n");
 return 0;
}

static void __exit hello_exit(void)
 {
    struct i2c_device_id id;
    mma8450_probe(&i2c_client_tmp,&id);
    printk(KERN_ALERT "Goodbye, cruel world\n");
 }

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MMA8450 3-Axis Accelerometer Driver");
MODULE_LICENSE("GPL");
