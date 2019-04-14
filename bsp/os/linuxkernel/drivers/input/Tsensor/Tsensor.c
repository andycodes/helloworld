#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h>  
#include <linux/platform_device.h>  
#include <linux/slab.h>  
#include <linux/input-polldev.h> 

#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>

#define POLL_INTERVAL   2000    //set poll time 

struct temperature_drvdata { 
    struct iio_dev *indio_dev; 
    struct input_polled_dev *poll_input; 
    //....reserved  
};

struct platform_device android_temperature_device = { 
    .name="android-temperature", 
    //.id=-1, 
}; 

static ssize_t temperature_show_name(struct device *dev,struct device_attribute *attr, char *buf) 
{    
    return sprintf(buf, "%s\n", "android-temperature sensor"); 
} 

static IIO_DEVICE_ATTR(name, S_IRUGO, temperature_show_name, NULL,0);

static struct attribute *temperature_attributes[] = { 
    &iio_dev_attr_name.dev_attr.attr, 
    NULL 
}; 
 
static const struct attribute_group temperature_attr_group = { 
    .attrs = temperature_attributes, 
}; 
 
static int tempValue; 
static void temperature_dev_poll(struct input_polled_dev *dev) 
{ 
    printk(KERN_INFO "Current Temperature: %d\n",tempValue); 
    if((tempValue++)==100) 
        tempValue=0; 
    input_event(dev->input,EV_ABS,ABS_PRESSURE,tempValue); 
    input_sync(dev->input); 
}

static int temperature_probe(struct platform_device *pdev) 
{ 
    struct temperature_drvdata *ddata; 
    struct input_dev *idev; 
    int err=0; 
    printk(KERN_INFO "%s\n",__FUNCTION__); 
    ddata=kzalloc(sizeof(struct temperature_drvdata),GFP_KERNEL); 
    if(!ddata) { 
        printk(KERN_INFO "failed to allocate memory...\n"); 
        err=-ENOMEM; 
        goto exit; 
    } 
    //----for iio device  
    ddata->indio_dev= iio_device_alloc(sizeof(struct temperature_drvdata)); 
    if(!ddata->indio_dev){ 
        printk(KERN_INFO "error to allocate iio device memory....\n"); 
        goto exit_iio_alloc; 
    } 
    ddata->indio_dev->chan_attr_group.attrs = temperature_attributes; 
    ddata->indio_dev->dev.parent = &pdev->dev; 
    ddata->indio_dev->modes = INDIO_DIRECT_MODE; 
    err = iio_device_register(ddata->indio_dev); 
    if(err){ 
        printk(KERN_INFO "iio device register failed....\n"); 
        goto exit_iio_reg; 
    } 
    //-----for input device  
    ddata->poll_input=input_allocate_polled_device(); 
    if(!(ddata->poll_input)){  
        err=-ENOMEM; 
        printk(KERN_INFO "input poll allocate failed...\n"); 
        goto exit_iio_reg; 
    } 
    ddata->poll_input->poll=temperature_dev_poll; 
    ddata->poll_input->poll_interval = POLL_INTERVAL; 
    idev=ddata->poll_input->input; 
    idev->name = "Android Temperature Sensor"; 
    idev->phys = "temperature-sensor/input0"; 
    idev->dev.parent=&pdev->dev; 
    idev->id.bustype=BUS_HOST; 
    idev->id.vendor=0x1234; 
    idev->id.product=0x0123; 
    idev->id.version=0x0012; 
    __set_bit(EV_ABS,idev->evbit); 
    __set_bit(ABS_PRESSURE,idev->absbit); 
    __set_bit(EV_SYN,idev->evbit); 
    input_set_abs_params(idev,ABS_PRESSURE,0,65535,0,0); 
    err=input_register_polled_device(ddata->poll_input); 
    if(err){ 
        printk(KERN_INFO "input register poll device failed....\n"); 
        goto err_reg_poll; 
    } 
    platform_set_drvdata(pdev,ddata); 
    return 0; 
err_reg_poll: 
    input_free_polled_device(ddata->poll_input); 
exit_iio_reg: 
    iio_device_free(ddata->indio_dev); 
exit_iio_alloc: 
    kfree(ddata); 
exit: 
    return err; 
}

struct platform_driver temperature_device_driver = {
       .probe            =     temperature_probe,
//     .remove          =     __devexit_p(temperature_remove),
       .driver            = {
              .name = "android-temperature",
              .owner= THIS_MODULE,
       },
};

static int __init temperature_init(void) 
{ 
    printk(KERN_INFO "temperature init...\n"); 

    platform_device_register(&android_temperature_device);
    
    return platform_driver_register(&temperature_device_driver); 
} 

static void __exit temperature_exit(void) 
{ 
    platform_driver_unregister(&temperature_device_driver); 
    platform_device_unregister(&android_temperature_device);
} 

module_init(temperature_init);
module_exit(temperature_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");

