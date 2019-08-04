

#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h> /* Needed for all modules */
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/sysrq.h>
#include <linux/console.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/serial.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/cpufreq.h>

#define S3C24XX_SERIAL_NAME	"ttySAC"

static struct uart_port *cons_uart;


static void
s3c24xx_serial_console_putchar(struct uart_port *port, int ch)
{
    printk("%s\n",__func__);
}

static int __init
s3c24xx_serial_console_setup(struct console *co, char *options)
{
    printk("%s\n",__func__);
    return 0;
}

static void
s3c24xx_serial_console_write(struct console *co, const char *s,
			     unsigned int count)
{
	uart_console_write(cons_uart, s, count, s3c24xx_serial_console_putchar);
}

struct tty_driver *uart_console_device(struct console *co, int *index)
{
	struct uart_driver *p = co->data;
	*index = co->index;
	return p->tty_driver;
}

static struct console s3c24xx_serial_console = {
    .name       = S3C24XX_SERIAL_NAME,
    .device     = uart_console_device,
    .flags      = CON_PRINTBUFFER,
    .index      = -1,
    .write      = s3c24xx_serial_console_write,
    .setup      = s3c24xx_serial_console_setup
};

static  int __init console_init_(void)
{
    register_console(&s3c24xx_serial_console);
    return 0;
}

static void __exit console_exit(void)
 {
    unregister_console(&s3c24xx_serial_console);
 }

module_init(console_init_);
module_exit(console_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");


