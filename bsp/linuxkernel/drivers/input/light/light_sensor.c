#include <linux/platform_device.h>
#include <linux/input-polldev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <mach/adc.h>
#include <linux/kthread.h>
#include <linux/delay.h>
//#include <linux/saradc.h>

#define POLL_INTERVAL    993     /* poll for input every 2s*/
#define LUX_LEVEL    3            /* 0~4 report 5 levels*/
#define LUX_MAX 3300

static struct platform_device *pdev;
static struct input_dev *idev;
static struct input_polled_dev *light_sensor_idev;
static int32_t enable_als(uint32_t enable);
static struct completion thread_completion;
static bool bThreadRunning;
/*define for polling thread*/
static int polling_function(void* arg);
static struct task_struct *polling_tsk;

static const int sAdcValues[LUX_LEVEL] = {
    200,
      1000, 
    2300,
    3400,
};

#define SAMPLE_NUM 10

static int Sample_value[SAMPLE_NUM];

struct light_sensor_info {
    int lux_level;
    int suspend;
};
static struct light_sensor_info ls_info;

/* Sysfs Files */
static ssize_t light_sensor_enable_show(struct device *dev,
                 struct device_attribute *attr, char *buf)
{
    //return sprintf(buf, "(%d)\n",get_s3c_adc_convert(3));
    return sprintf(buf, "%d\n", bThreadRunning);
}

static ssize_t light_sensor_enable_store(struct device *dev,
                 struct device_attribute *attr, char *buf,size_t len)
{
    uint32_t value = simple_strtoul(buf, NULL, 10);
   printk("huabinbin test : Enable LS : %d\n",value);
    enable_als(value);
    return len;
}

static DEVICE_ATTR(ls_enable, 0666, light_sensor_enable_show, light_sensor_enable_store);

static struct attribute *light_sensor_attributes[] = {
    &dev_attr_ls_enable.attr,
    NULL,
};

static struct attribute_group light_sensor_attribute_group = {
    .attrs = light_sensor_attributes,
};

static void sample_vol(unsigned int vol)
{
    int i = 0;

    for(i = 0; i < SAMPLE_NUM -1; i++)
    Sample_value[i] = Sample_value[i+1];
    Sample_value[SAMPLE_NUM - 1]=vol;
    return; 
}

static int get_lux_average()
{
    int i,sum = 0;

    for(i = 0; i < SAMPLE_NUM-1; i++)
        sum += Sample_value[i];

    //printk("hbb test %s adc_val = %d\n",__func__,sum / SAMPLE_NUM);
    return (sum / SAMPLE_NUM);
}

static int polling_function(void* arg)
{
    int adc_val, i;
    init_completion(&thread_completion);

    while (1)
    {
        adc_val = get_s3c_adc_convert(3);
        //printk("hbb test %s adc_val = %d\n",__func__,adc_val);
        sample_vol(adc_val);
        #if 0
        
        for(i = 0; i <= LUX_LEVEL; i++) {
            if(adc_val < sAdcValues[i])
                break;
        }

        if(ls_info.lux_level != i) {
            ls_info.lux_level = i;    
            //input_report_abs(idev, ABS_X, ls_info.lux_level);
            input_report_abs(idev, ABS_MISC, ls_info.lux_level);
            input_sync(idev);
            
            printk(KERN_INFO "light_sensor: light_sensor_dev_poll lux_level = %d\n",sAdcValues[ls_info.lux_level]);
        }    
        #else
        input_report_abs(idev, ABS_MISC,get_lux_average());
        input_sync(idev);
        #endif
        if (bThreadRunning == false)
            break;
        msleep(POLL_INTERVAL);

    };
    complete(&thread_completion);
    return 0;
}

static int32_t enable_als(uint32_t enable)
{
    int32_t ret;
    if (enable)
    {

        if (bThreadRunning == 0)
        {
            bThreadRunning = 1;
            polling_tsk = kthread_run(polling_function,NULL,"ls_polling");
        }
        else
        {
         printk("huabinbin test : thread has running\n");
        }
    }
    else
    {
        if (bThreadRunning)
        {
            bThreadRunning = false;
            wait_for_completion(&thread_completion);
            polling_tsk = NULL;
        }
    }
    return ret;
}

/* Device model stuff */
static int light_sensor_probe(struct platform_device *dev)
{
    printk(KERN_INFO "light_sensor: device successfully initialized.\n");
    return 0;
}

#ifdef CONFIG_PM
static int light_sensor_suspend(struct platform_device *dev, pm_message_t state)
{
        ls_info.suspend = 1;
    return 0;
}

static int light_sensor_resume(struct platform_device *dev)
{
        ls_info.suspend = 0;
    return 0;
}
#else
    #define light_sensor_suspend NULL
    #define light_sensor_resume NULL
#endif

static struct platform_driver light_sensor_driver = {
    .probe = light_sensor_probe,
    .resume = light_sensor_resume,
    .suspend = light_sensor_suspend,
    .driver    = {
        .name = "light_sensor",
        .owner = THIS_MODULE,
    },
};

static void light_sensor_dev_poll(struct input_polled_dev *dev)
{
    //printk("huabinbin test light_sensor_dev_poll get adc %d\n",get_s3c_adc_convert(3));
    int adc_val, i;

    adc_val = get_s3c_adc_convert(3);
    for(i = 0; i < LUX_LEVEL; i++) {
        if(adc_val < sAdcValues[i])
            break;
    }

    //printk("huabinbin test get adc %d\n",get_s3c_adc_convert(3));
    
    if(ls_info.lux_level != i) {
        ls_info.lux_level = i;    
        input_report_abs(idev, ABS_X, ls_info.lux_level);
        input_sync(idev);
        
        //printk(KERN_INFO "light_sensor: light_sensor_dev_poll lux_level = %d\n",sAdcValues[ls_info.lux_level]);
    }    

}

/* Module stuff */
static int __init light_sensor_init(void)
{
    
    int ret;

    ret = platform_driver_register(&light_sensor_driver);
    if (ret)
        goto out;

    pdev = platform_device_register_simple("light_sensor", -1, NULL, 0);
    if (IS_ERR(pdev)) {
        ret = PTR_ERR(pdev);
        goto out_driver;
    }

    ret = sysfs_create_group(&pdev->dev.kobj, &light_sensor_attribute_group);
    if (ret)
        goto out_device;

//    light_sensor_idev = input_allocate_polled_device();
//    if (!light_sensor_idev) {
    //    ret = -ENOMEM;
    //    goto out_group;
    //}

    bThreadRunning = false;
    
    //light_sensor_idev->poll = light_sensor_dev_poll;
    //light_sensor_idev->poll_interval = POLL_INTERVAL;

    /* initialize the input class */
    //idev = light_sensor_idev->input;
    idev = input_allocate_device();
    idev->name = "light_sensor";
    idev->phys = "light_sensor/input0";
    idev->id.bustype = BUS_ISA;
    idev->dev.parent = &pdev->dev;
    idev->evbit[0] = BIT_MASK(EV_ABS);
    //input_set_abs_params(idev, ABS_MISC,0, LUX_LEVEL, 0, 1);
    input_set_abs_params(idev, ABS_MISC,0, LUX_MAX, 0, 1);

    ret = input_register_device(idev);
    if (ret)
        goto out_idev;

    
    printk(KERN_INFO "huabinbin test light_sensor: driver successfully loaded.\n");
    return 0;

out_idev:
     input_free_device(idev);
out_group:
    sysfs_remove_group(&pdev->dev.kobj, &light_sensor_attribute_group);
out_device:
    platform_device_unregister(pdev);
out_driver:
    platform_driver_unregister(&light_sensor_driver);
out:
    printk(KERN_WARNING "light_sensor: driver init failed (ret=%d)!\n", ret);
    return ret;
}

static void __exit light_sensor_exit(void)
{
    input_unregister_polled_device(light_sensor_idev);
    input_free_polled_device(light_sensor_idev);
    sysfs_remove_group(&pdev->dev.kobj, &light_sensor_attribute_group);
    platform_device_unregister(pdev);
    platform_driver_unregister(&light_sensor_driver);    

    printk(KERN_INFO "light_sensor: driver unloaded.\n");
}

module_init(light_sensor_init);
module_exit(light_sensor_exit);

MODULE_AUTHOR("bb.hua@unistrong.com");
MODULE_DESCRIPTION("Light Sensor Driver - po188");
MODULE_LICENSE("GPL");


