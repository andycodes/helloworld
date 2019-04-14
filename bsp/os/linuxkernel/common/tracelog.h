#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/errno.h>  
#include <linux/platform_device.h>  
#include <linux/irqflags.h>  
#include <linux/slab.h>  
#include <linux/init.h>  
#include <linux/idr.h>  
#include <linux/mutex.h>  
#include <linux/miscdevice.h>  

//#include <stdio.h>
//#define printlog    printf

#define KERNEL_FILE "/project/kernel_file"
#define TRACE_FILE_MAX_SIZE  (2048)
#define LOG_MSG_MAX_SIZE  (1024)
#define LOG_USR_MSG_MAX_SIZE  (512)

#define LOG_CONF_NO_LOG 0

#define PRINK_CONF(x)       (x&(1<<1))
#define FILE_CONF(x)          (x&(1<<2))

#define PRINK_SET_CONF(x)       (x|(1<<1))
#define FILE__SET_CONF(x)       (x|(1<<2))

void  tracelog(char* log_msg,int msg_size) ;

