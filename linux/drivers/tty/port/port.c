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

#define CONFIG_SERIAL_SAMSUNG_UARTS 3

struct s3c24xx_uart_clksrc {
	const char	*name;
	unsigned int	divisor;
	unsigned int	min_baud;
	unsigned int	max_baud;
};

struct s3c2410_uartcfg {
	unsigned char	   hwport;	 /* hardware port number */
	unsigned char	   unused;
	unsigned short	   flags;
	upf_t		   uart_flags;	 /* default uart flags */
	unsigned int	   clk_sel;

	unsigned int	   has_fracval;

	unsigned long	   ucon;	 /* value of ucon for port */
	unsigned long	   ulcon;	 /* value of ulcon for port */
	unsigned long	   ufcon;	 /* value of ufcon for port */
};

struct s3c24xx_uart_info {
	char			*name;
	unsigned int		type;
	unsigned int		fifosize;
	unsigned long		rx_fifomask;
	unsigned long		rx_fifoshift;
	unsigned long		rx_fifofull;
	unsigned long		tx_fifomask;
	unsigned long		tx_fifoshift;
	unsigned long		tx_fifofull;

	/* uart port features */

	unsigned int		has_divslot:1;

	/* clock source control */

	int (*get_clksrc)(struct uart_port *, struct s3c24xx_uart_clksrc *clk);
	int (*set_clksrc)(struct uart_port *, struct s3c24xx_uart_clksrc *clk);

	/* uart controls */
	int (*reset_port)(struct uart_port *, struct s3c2410_uartcfg *);
};

struct s3c24xx_uart_port {
	unsigned char			rx_claimed;
	unsigned char			tx_claimed;
	unsigned int			pm_level;
	unsigned long			baudclk_rate;

	unsigned int			rx_irq;
	unsigned int			tx_irq;

	struct s3c24xx_uart_info	*info;
	struct s3c24xx_uart_clksrc	*clksrc;
	struct clk			*clk;
	struct clk			*baudclk;
	struct uart_port		port;

#ifdef CONFIG_CPU_FREQ
	struct notifier_block		freq_transition;
#endif
};


static void s3c24xx_serial_pm(struct uart_port *port, unsigned int level,
			      unsigned int old)
{

}

static unsigned int s3c24xx_serial_tx_empty(struct uart_port *port)
{
    return 0;
}

static unsigned int s3c24xx_serial_get_mctrl(struct uart_port *port)
{
    return 0;
}

static void s3c24xx_serial_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	/* todo - possibly remove AFC and do manual CTS */
}

static void s3c24xx_serial_stop_tx(struct uart_port *port)
{
    
}


static void s3c24xx_serial_start_tx(struct uart_port *port)
{

}

static void s3c24xx_serial_enable_ms(struct uart_port *port)
{
}

static void s3c24xx_serial_break_ctl(struct uart_port *port, int break_state)
{

}

static int s3c24xx_serial_startup(struct uart_port *port)
{

}

static void s3c24xx_serial_shutdown(struct uart_port *port)
{

}

static void s3c24xx_serial_set_termios(struct uart_port *port,
				       struct ktermios *termios,
				       struct ktermios *old)
{

}


static const char *s3c24xx_serial_type(struct uart_port *port)
{
    return NULL;
}

static void s3c24xx_serial_release_port(struct uart_port *port)
{}

static int s3c24xx_serial_request_port(struct uart_port *port)
{}

static void s3c24xx_serial_config_port(struct uart_port *port, int flags)
{}

static int
s3c24xx_serial_verify_port(struct uart_port *port, struct serial_struct *ser)
{}

static struct uart_ops s3c24xx_serial_ops = {
	.pm		= s3c24xx_serial_pm,
	.tx_empty	= s3c24xx_serial_tx_empty,
	.get_mctrl	= s3c24xx_serial_get_mctrl,
	.set_mctrl	= s3c24xx_serial_set_mctrl,
	.stop_tx	= s3c24xx_serial_stop_tx,
	.start_tx	= s3c24xx_serial_start_tx,
	.stop_rx	= s3c24xx_serial_stop_rx,
	.enable_ms	= s3c24xx_serial_enable_ms,
	.break_ctl	= s3c24xx_serial_break_ctl,
	.startup	= s3c24xx_serial_startup,
	.shutdown	= s3c24xx_serial_shutdown,
	.set_termios	= s3c24xx_serial_set_termios,
	.type		= s3c24xx_serial_type,
	.release_port	= s3c24xx_serial_release_port,
	.request_port	= s3c24xx_serial_request_port,
	.config_port	= s3c24xx_serial_config_port,
	.verify_port	= s3c24xx_serial_verify_port,
};

static struct s3c24xx_uart_port s3c24xx_serial_ports[CONFIG_SERIAL_SAMSUNG_UARTS] = {
	[0] = {
		.port = {
			.lock		= __SPIN_LOCK_UNLOCKED(s3c24xx_serial_ports[0].port.lock),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fifosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 0,
		}
	},
	[1] = {
		.port = {
			.lock		= __SPIN_LOCK_UNLOCKED(s3c24xx_serial_ports[1].port.lock),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fifosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 1,
		}
	},
#if CONFIG_SERIAL_SAMSUNG_UARTS > 2

	[2] = {
		.port = {
			.lock		= __SPIN_LOCK_UNLOCKED(s3c24xx_serial_ports[2].port.lock),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fifosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 2,
		}
	},
#endif
#if CONFIG_SERIAL_SAMSUNG_UARTS > 3
	[3] = {
		.port = {
			.lock		= __SPIN_LOCK_UNLOCKED(s3c24xx_serial_ports[3].port.lock),
			.iotype		= UPIO_MEM,
			.uartclk	= 0,
			.fifosize	= 16,
			.ops		= &s3c24xx_serial_ops,
			.flags		= UPF_BOOT_AUTOCONF,
			.line		= 3,
		}
	}
#endif
};

static  int __init port_init(void)
{
    return 0;
}

static void __exit port_init(void)
 {
 
 }

module_init(port_init);
module_exit(port_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");


