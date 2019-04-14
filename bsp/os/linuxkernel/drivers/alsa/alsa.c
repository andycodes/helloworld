#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/moduleparam.h> 
#include <linux/pci.h> 

#define DRIVER_NAME "ENS1371" 
#define FUNC_LOG() printk(KERN_ERR "FUNC_LOG: [%d:][%s()]\n", __LINE__, __FUNCTION__) 

MODULE_DEVICE_TABLE(pci, snd_audiopci_ids); 

static struct pci_device_id snd_audiopci_ids[] = { 
//#ifdef CHIP1370 
//	{ 0x1274, 0x5000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },	/* ES1370 */ 
//#endif 
#ifdef CHIP1371 
	{ 0x1274, 0x1371, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },	/* ES1371 */ 
	{ 0x1274, 0x5880, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },	/* ES1373 - CT5880 */ 
	{ 0x1102, 0x8938, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, },	/* Ectiva EV1938 */ 
#endif 
	{ 0, } 
}; 

static int __devinit snd_audiopci_probe(struct pci_dev *pci, const struct pci_device_id *pci_id) 
{ 
	FUNC_LOG(); 
	return 0; 
} 
static void __devexit snd_audiopci_remove(struct pci_dev *pci) 
{ 
	FUNC_LOG(); 
} 


static struct pci_driver driver = { 
	.name = DRIVER_NAME, 
	.id_table = snd_audiopci_ids, 
	.probe = snd_audiopci_probe, 
	.remove = __devexit_p(snd_audiopci_remove), 
#ifdef CONFIG_PM 
	//.suspend = snd_ensoniq_suspend, 
	//.resume = snd_ensoniq_resume, 
#endif 
}; 

static int __init sound_init (void)
{
    FUNC_LOG();
    return pci_register_driver(&driver); 
}

static void __exit sound_exit (void)
{
    FUNC_LOG();
    pci_unregister_driver(&driver); 
}

module_init (sound_init);
module_exit (sound_exit);
MODULE_LICENSE ("GPL");

/*
** insmod alsa.ko
** lsmod |grep alsa
*/


