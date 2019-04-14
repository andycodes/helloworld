#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/types.h>
#include <linux/slab.h>

/* Set ADC sample rate (30sec)*/
#define ADC_SAMPLE_RATE        30

#define OCVREG0                0       
#define OCVREG1                0     
#define OCVREG2                0       
#define OCVREG3                3       
#define OCVREG4                7       
#define OCVREG5                13       
#define OCVREG6                18       
#define OCVREG7                27     
#define OCVREG8                36      
#define OCVREG9                46      
#define OCVREGA                53       
#define OCVREGB                62       
#define OCVREGC                73       
#define OCVREGD                85        
#define OCVREGE                93        
#define OCVREGF                100        //4

/*AXP19 初始化开路电压*/
/*
    只针对AXP19，可以改变，注意和上表的剩余电量百分比一一对应
*/
#define OCVVOL0                3132
#define OCVVOL1                3273
#define OCVVOL2                3500
#define OCVVOL3                3555
#define OCVVOL4                3625
#define OCVVOL5                3660
#define OCVVOL6                3696
#define OCVVOL7                3731
#define OCVVOL8                3766
#define OCVVOL9                3801
#define OCVVOLA                3836
#define OCVVOLB                3872
#define OCVVOLC                3942
#define OCVVOLD                4012
#define OCVVOLE                4090//4083
#define OCVVOLF                4150//4150
 
#define  uint8   unsigned char
#define  uint16  unsigned short
#define  int16   short
#define  uint32  unsigned int
#define  int32   int
#define  uint64  unsigned long


typedef enum charger_type_t {
    CHARGER_BATTERY = 0,
    CHARGER_USB,
    CHARGER_AC
}charger_type_t;

struct emxx_battery_data {
    struct power_supply battery;
    struct power_supply usb;
    struct power_supply ac;


    unsigned int battery_present;
    uint16 voltage_level;
    uint16 battery_temp;
    unsigned int battery_voltage;
    
    charger_type_t charger;
    int usb_state;

    struct workqueue_struct *monitor_wqueue;
    struct delayed_work monitor_work;
};

static struct emxx_battery_data *battery_data;
unsigned int battery_vol;
static enum power_supply_property emxx_battery_props[] = {
    POWER_SUPPLY_PROP_STATUS,
    POWER_SUPPLY_PROP_HEALTH,
    POWER_SUPPLY_PROP_PRESENT,
    POWER_SUPPLY_PROP_TECHNOLOGY,
    POWER_SUPPLY_PROP_CAPACITY,    //电量
    POWER_SUPPLY_PROP_TEMP,            //温度
    POWER_SUPPLY_PROP_VOLTAGE_NOW,    //电压
};

static enum power_supply_property emxx_power_props[] = {
    POWER_SUPPLY_PROP_ONLINE, //外部供电查看是否存在AC或usb
};

static int emxx_battery_get_status(void)
{
    int ret;

    switch (battery_data->charger) {
    case CHARGER_BATTERY:
        ret = POWER_SUPPLY_STATUS_NOT_CHARGING;
        break;
    case CHARGER_USB:
    case CHARGER_AC:
        if (battery_data->voltage_level == 100)
            ret = POWER_SUPPLY_STATUS_FULL;//如果电池充满了则显示full状态
        else
            ret = POWER_SUPPLY_STATUS_CHARGING; //未满并且外部电源存在则显示充电状态，人为设置为CHARGER_AC
        break;
    default:
        ret = POWER_SUPPLY_STATUS_UNKNOWN;
    }
    return ret;
}    

static int emxx_battery_get_property(struct power_supply *psy,
                 enum power_supply_property psp,
                 union power_supply_propval *val)
{
    int ret = 0;

    switch (psp) {
    case POWER_SUPPLY_PROP_STATUS:        /* 0 */
        val->intval = emxx_battery_get_status();
        break;
    case POWER_SUPPLY_PROP_HEALTH:        /* 1 */
        val->intval = POWER_SUPPLY_HEALTH_GOOD;
        break;
    case POWER_SUPPLY_PROP_PRESENT:        /* 2 */
        val->intval = battery_data->battery_present;
        break;
    case POWER_SUPPLY_PROP_TECHNOLOGY:    /* 4 */
        val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
        break;
    case POWER_SUPPLY_PROP_CAPACITY:    /* 26 */
        val->intval = battery_data->voltage_level;
        break;    
    case POWER_SUPPLY_PROP_TEMP:
        val->intval = battery_data->battery_temp;
        break;
    case POWER_SUPPLY_PROP_VOLTAGE_NOW:    
        val->intval = battery_data->battery_voltage;
        break;    
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

/*根据电压获取当前电量，此算法简单实用，
根据不同电池需调节最大电压，
最小电压以及每段的电压及对应的电量，
可达到充电快慢的程度，实际中需要通过内阻，
开路电压及充放电电流按一定算法获取后并
经过库仑计校准得到电量，实际电量的计算
是很复杂的，往往无法达到理想的检测效果*/

static uint8_t axp_restcap(int ocv)
{
    if(ocv >= OCVVOLF)
    {
        return OCVREGF;
    }
    else if(ocv < OCVVOL0)
    {
        return OCVREG0;
    }
    else if(ocv < OCVVOL1)
    {
        return  (OCVREG1 - OCVREG0) * (ocv - OCVVOL0) / (OCVVOL1 - OCVVOL0);
    }
    else if(ocv < OCVVOL2)
    {
        return  (OCVREG2 - OCVREG1) * (ocv - OCVVOL1) / (OCVVOL2 - OCVVOL1);
    }
    else if(ocv < OCVVOL3)
    {
        return  (OCVREG3 - OCVREG2) * (ocv - OCVVOL2) / (OCVVOL3 - OCVVOL2);
    }
    else if(ocv < OCVVOL4)
    {
        return  (OCVREG4 - OCVREG3) * (ocv - OCVVOL3) / (OCVVOL4 - OCVVOL3);
    }
    else if(ocv < OCVVOL5)
    {
        return  (OCVREG5 - OCVREG4) * (ocv - OCVVOL4) / (OCVVOL5 - OCVVOL4);
    }
    else if(ocv < OCVVOL6)                               
    {
        return  (OCVREG6 - OCVREG5) * (ocv - OCVVOL5) / (OCVVOL6 - OCVVOL5);
    }
    else if(ocv < OCVVOL7)
    {
        return  (OCVREG7 - OCVREG6) * (ocv - OCVVOL6) / (OCVVOL7 - OCVVOL6);
    }
    else if(ocv < OCVVOL8)
    {
        return  (OCVREG8 - OCVREG7) * (ocv - OCVVOL7) / (OCVVOL8 - OCVVOL7);
    }
    else if(ocv < OCVVOL9)
    {
        return  (OCVREG9 - OCVREG8) * (ocv - OCVVOL8) / (OCVVOL9 - OCVVOL8);
    }
    else if(ocv < OCVVOLA)
    {
        return  (OCVREGA - OCVREG9) * (ocv - OCVVOL9) / (OCVVOLA - OCVVOL9);
    }
    else if(ocv < OCVVOLB)
    {
        return  (OCVREGB - OCVREGA) * (ocv - OCVVOLA) / (OCVVOLB - OCVVOLA);
    }
    else if(ocv < OCVVOLC)
    {
        return  (OCVREGC - OCVREGB) * (ocv - OCVVOLB) / (OCVVOLC - OCVVOLB);
    }
    else if(ocv < OCVVOLD)
    {
        return  (OCVREGD - OCVREGC) * (ocv - OCVVOLC) / (OCVVOLD - OCVVOLC);
    }
    else if(ocv < OCVVOLE)
    {
        return  (OCVREGE - OCVREGD) * (ocv - OCVVOLD) / (OCVVOLE - OCVVOLD);
    }
    else if(ocv < OCVVOLF)
    {
        return  (OCVREGF - OCVREGE) * (ocv - OCVVOLE) / (OCVVOLF - OCVVOLE);
    }
    else
    {
        return 0;
    }
}


static void Get_battery_preference(void)
{
    battery_data->voltage_level = axp_restcap(battery_vol);
    battery_vol = 5; //每30s轮询一次，电压加5mv
    battery_data->battery_temp = 30;
    
    if(battery_data->voltage_level > 100){
        battery_data->voltage_level = 100;
    }

    if(battery_vol > 4150){
        battery_vol = 4150;
    }
/*针对android的特性，当温度超过一定值时，
会自动关机，故要设定一阀值*/
    if(battery_data->battery_temp > 60){
        battery_data->battery_temp = 60;
    }
}

static void emxx_battery_work(struct work_struct *work)
{
    const int interval = HZ * ADC_SAMPLE_RATE;
    unsigned int old_voltage_level;
    unsigned int old_battery_voltage;
    unsigned int old_battery_temp;
    
    old_voltage_level = battery_data->voltage_level;
    old_battery_voltage = battery_data->battery_voltage;
    old_battery_temp = battery_data->battery_temp;
    
    Get_battery_preference();
  /*电压上报时需要扩大1000，温度需扩大10，
  才能用es任务管理器查看实际值*/
    battery_data->battery_voltage = battery_vol * 1000;
    battery_data->battery_temp = battery_data->battery_temp * 10;
    
    if(old_battery_temp > battery_data->battery_temp -100)
    {
        battery_data->battery_temp = old_battery_temp - 100;
    }
    else if(old_battery_temp < battery_data->battery_temp - 100)
    {
        battery_data->battery_temp = old_battery_temp -100;
    }
    
    /* If status have changed, update the status */
    if (old_voltage_level != battery_data->voltage_level || old_battery_voltage != battery_data->battery_voltage ||
        old_battery_temp != battery_data->battery_temp) {
        power_supply_changed(&battery_data->battery);  //当电压，温度，电量任意一个发生改变时，数据上报
    }
    queue_delayed_work(battery_data->monitor_wqueue,
            &(battery_data->monitor_work), interval);
}

static int emxx_power_get_property(struct power_supply *psy,
            enum power_supply_property psp,
            union power_supply_propval *val)
{
    charger_type_t charger;

    charger = battery_data->charger;

    switch (psp) {
    case POWER_SUPPLY_PROP_ONLINE:    /* 3 */
        if (psy->type == POWER_SUPPLY_TYPE_MAINS)
            val->intval = (charger ==  CHARGER_AC ? 1 : 0);
        else if (psy->type == POWER_SUPPLY_TYPE_USB) {
            if (battery_data->usb_state == 1)
                val->intval = 0;
            else
                val->intval = 1;
        } else
            val->intval = 0;
        break;
    default:
        return -EINVAL;
    }

    return 0;
}


static int emxx_battery_probe(struct platform_device *pdev)
{
    int ret;
    struct emxx_battery_data *data;

    data = devm_kzalloc(sizeof(*data), GFP_KERNEL);
    if (data == NULL) {
        ret = -ENOMEM;
        goto err_data_alloc_failed;
    }

    /* Battey */
  /*填充struct power_supply battery*/
    data->battery.name = "battery";
    data->battery.type = POWER_SUPPLY_TYPE_BATTERY;
    data->battery.properties = emxx_battery_props; //添加相应字段到battery目录下，包括电压，电量及温度。
    data->battery.num_properties = ARRAY_SIZE(emxx_battery_props);
    data->battery.get_property = emxx_battery_get_property; //注册回调函数，以此动态获取属性

    /* USB */
    data->usb.name = "usb";
    data->usb.type = POWER_SUPPLY_TYPE_USB;
    data->usb.properties = emxx_power_props;
    data->usb.num_properties = ARRAY_SIZE(emxx_power_props);
    data->usb.get_property = emxx_power_get_property;

    /* AC */
    data->ac.name = "ac";
    data->ac.type = POWER_SUPPLY_TYPE_MAINS;
    data->ac.properties = emxx_power_props;
    data->ac.num_properties = ARRAY_SIZE(emxx_power_props);
    data->ac.get_property = emxx_power_get_property;

    battery_data = data;    
   /*初始化电池电压为3700mv，温度为30*/
    battery_vol = 3700;
    battery_data->battery_temp = 30;

    battery_data->charger = CHARGER_AC;
    
    ret = power_supply_register(&pdev->dev, &data->battery);
    if (ret)
        goto err_battery_failed;

    ret = power_supply_register(&pdev->dev, &data->usb);
    if (ret)
        goto err_usb_failed;

    ret = power_supply_register(&pdev->dev, &data->ac);
    if (ret)
        goto err_ac_failed;

    INIT_DELAYED_WORK(&data->monitor_work, emxx_battery_work);
    data->monitor_wqueue =
        create_singlethread_workqueue("axp192");
    if (!data->monitor_wqueue) {
        ret = -ESRCH;
        goto err_workqueue_failed;
    }
    queue_delayed_work(data->monitor_wqueue, &data->monitor_work, HZ);

    platform_set_drvdata(pdev, data);
    return 0;

err_workqueue_failed:
    power_supply_unregister(&data->ac);
err_ac_failed:
    power_supply_unregister(&data->usb);
err_usb_failed:
    power_supply_unregister(&data->battery);
err_battery_failed:
err_data_alloc_failed:
    return ret;
}

static int emxx_battery_remove(struct platform_device *pdev)
{
    struct emxx_battery_data *data = platform_get_drvdata(pdev);

    printk(KERN_INFO "Battery driver remove...n");

    power_supply_unregister(&data->battery);
    power_supply_unregister(&data->usb);
    power_supply_unregister(&data->ac);

    kfree(data);
    battery_data = NULL;
    return 0;
}

#ifdef CONFIG_PM
static int emxx_battery_suspend(struct platform_device *pdev,
                  pm_message_t state)
{
    return 0;
}

static int emxx_battery_resume(struct platform_device *pdev)
{
    struct emxx_battery_data *data = platform_get_drvdata(pdev);
    power_supply_changed(&data->battery);

    cancel_delayed_work(&data->monitor_work);
    queue_delayed_work(data->monitor_wqueue, &data->monitor_work, HZ);


    return 0;
}


#else
#define emxx_battery_suspend NULL
#define emxx_battery_resume NULL
#endif /* CONFIG_PM */

static struct platform_driver emxx_battery_driver = {
    .probe        = emxx_battery_probe,
    .remove        = emxx_battery_remove,
    .suspend    = emxx_battery_suspend,
    .resume     = emxx_battery_resume,
    .driver = {
        .name = "emxx-battery"
    }
};

static int __init emxx_battery_init(void)
{
    return platform_driver_register(&emxx_battery_driver);
}

static void __exit emxx_battery_exit(void)
{
    platform_driver_unregister(&emxx_battery_driver);
}

module_init(emxx_battery_init);
module_exit(emxx_battery_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Battery driver for the EMMA Mobile series");

