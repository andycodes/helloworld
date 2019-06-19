#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>       /* printk() */
#include <linux/slab.h>         /* kmalloc() */
#include <linux/fs.h>           /* everything... */
#include <linux/errno.h>        /* error codes */
#include <linux/types.h>        /* size_t */
#include <linux/fcntl.h>        /* O_ACCMODE */
#include <asm/system.h>         /* cli(), *_flags */
#include <asm/uaccess.h>        /* copy_*_user */
#include <linux/ioctl.h>
#include <linux/device.h>

#include <linux/platform_device.h>
#include <linux/sysrq.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/serial.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/console.h>
#include <asm/io.h>
#include <asm/irq.h>

#ifdef ARCH_ARM
#include <asm/hardware.h>
#include <asm/plat-s3c/regs-serial.h>
#include <asm/arch/regs-gpio.h>
#else
#define IRQ_S3CUART_RX2  (10)
#endif



#define DEV_NAME            "gprs_uart"     /* �豸�� */
/* ���ｫ���ڵ����豸����Ϊ0,�򴮿��豸������ں˶�̬����;��Ҳ��ָ�����ڵ��豸��� */
#define GPRS_UART_MAJOR        0            /* ���豸�� */
#define GPRS_UART_MINOR        0            /* ���豸�� */
#define GPRS_UART_FIFO_SIZE    16           /* ����FIFO�Ĵ�С */
#define RXSTAT_DUMMY_READ    (0x10000000)
#define MAP_SIZE             (0x100)        /* Ҫӳ��Ĵ���IO�ڴ�����С */

/* ���ڷ����жϺ� */
#define TX_IRQ(port) ((port)->irq + 1)
/* ���ڽ����жϺ� */
#define RX_IRQ(port) ((port)->irq)

/* �����ڽ����ַ��ı�־ */
#define tx_enabled(port) ((port)->unused[0])
/* �����ڷ����ַ��ı�־ */
#define rx_enabled(port) ((port)->unused[1])

/* ��ȡ�Ĵ�����ַ */
#define portaddr(port, reg) ((port)->membase + (reg))

/* ��8λ��ļĴ��� */
#define rd_regb(port, reg) (ioread8(portaddr(port, reg)))
/* ��32λ��ļĴ��� */
#define rd_regl(port, reg) (ioread32(portaddr(port, reg)))
/* д8λ��ļĴ��� */
#define wr_regb(port, reg, val) \
    do { iowrite8(val, portaddr(port, reg)); } while(0)
/* д32λ��ļĴ��� */        
#define wr_regl(port, reg, val) \
    do { iowrite32(val, portaddr(port, reg)); } while(0)


/* ��ֹ���ڷ������� */
static void gprs_uart_stop_tx(struct uart_port *port)
{
    if (tx_enabled(port))            /* ���������������� */
    {        
        disable_irq(TX_IRQ(port));   /* ��ֹ�����ж� */
        tx_enabled(port) = 0;        /* ���ô���Ϊδ�������� */
    }
}

/* ʹ�ܴ��ڷ������� */
static void gprs_uart_start_tx(struct uart_port *port)
{
    if (!tx_enabled(port))           /* ������δ�������� */
    {
        enable_irq(TX_IRQ(port));    /* ʹ�ܷ����ж� */
        tx_enabled(port) = 1;        /* ���ô���Ϊ���������� */
    }    
}

/* ��ֹ���ڽ������� */
static void gprs_uart_stop_rx(struct uart_port *port)
{
    if (rx_enabled(port))            /* ���������������� */
    {
        disable_irq(RX_IRQ(port));   /* ��ֹ�����ж� */
        rx_enabled(port) = 0;        /* ���ô���Ϊδ�������� */
    }
}

/* ʹ��modem��״̬�ź� */
static void gprs_uart_enable_ms(struct uart_port *port)
{
}

/* ���ڵ�Tx FIFO�����Ƿ�Ϊ�� */
static unsigned int gprs_uart_tx_empty(struct uart_port *port)
{
#ifdef ARCH_ARM
    int ret = 1;
    unsigned long ufstat = rd_regl(port, S3C2410_UFSTAT);
    unsigned long ufcon = rd_regl(port, S3C2410_UFCON);

    if (ufcon & S3C2410_UFCON_FIFOMODE)    /* ��ʹ����FIFO */
    {
        if ((ufstat & S3C2410_UFSTAT_TXMASK) != 0 ||    /* 0 <FIFO <=15 */
                (ufstat & S3C2410_UFSTAT_TXFULL))       /* FIFO�� */
            ret = 0;
    }
    else    /* ��δʹ����FIFO,���жϷ��ͻ���ͷ�����λ�Ĵ����Ƿ��Ϊ�� */
    {
        ret = rd_regl(port, S3C2410_UTRSTAT) & S3C2410_UTRSTAT_TXE;
    }
            
    return ret;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

/* ��ȡ����modem����,��Ϊuart2��modem����,����CTS��DSRֱ�ӷ�����Ч */
static unsigned int gprs_uart_get_mctrl(struct uart_port *port)
{
    return (TIOCM_CTS | TIOCM_DSR | TIOCM_CAR);
}

/* ���ô���modem���� */
static void gprs_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{

}

/* ����break�ź� */
static void gprs_uart_break_ctl(struct uart_port *port, int break_state)
{
#ifdef ARCH_ARM
    unsigned long flags;
    unsigned int ucon;

    spin_lock_irqsave(&port->lock, flags);

    ucon = rd_regl(port, S3C2410_UCON);

    if (break_state)
        ucon |= S3C2410_UCON_SBREAK;
    else
        ucon &= ~S3C2410_UCON_SBREAK;

    wr_regl(port, S3C2410_UCON, ucon);

    spin_unlock_irqrestore(&port->lock, flags);
#else
        printk("%s %d\n",__FUNCTION__,__LINE__);
#endif
}

/* ����Rx FIFO�Ѵ�������� */
static int gprs_uart_rx_fifocnt(unsigned long ufstat)
{
#ifdef ARCH_ARM
    /* ��Rx FIFO����,����FIFO�Ĵ�С */
    if (ufstat & S3C2410_UFSTAT_RXFULL)
        return GPRS_UART_FIFO_SIZE;

    /* ��FIFOδ��,����Rx FIFO�Ѵ��˶����ֽ����� */
    return (ufstat & S3C2410_UFSTAT_RXMASK) >> S3C2410_UFSTAT_RXSHIFT;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

#define S3C2410_UERSTAT_PARITY (0x1000)

/* ���ڽ����жϴ�����,��ȡ���ڽ��յ�������,������Щ���ݵݽ����й���� */
static irqreturn_t gprs_uart_rx_chars(int irq, void *dev_id)
{
#ifdef ARCH_ARM
    struct uart_port *port = dev_id;
    struct tty_struct *tty = port->info->tty;
    unsigned int ufcon, ch, flag, ufstat, uerstat;
    int max_count = 64;

    /* ѭ����������,���һ���жϽ���64�ֽ����� */
    while (max_count-- > 0)
    {
        ufcon = rd_regl(port, S3C2410_UFCON);
        ufstat = rd_regl(port, S3C2410_UFSTAT);

        /* ��Rx FIFO��������,����ѭ�� */
        if (gprs_uart_rx_fifocnt(ufstat) == 0)
            break;

        /* ��ȡRx error״̬�Ĵ��� */
        uerstat = rd_regl(port, S3C2410_UERSTAT);
        /* ��ȡ�ѽ��ܵ������� */
        ch = rd_regb(port, S3C2410_URXH);

        /* insert the character into the buffer */
        /* �Ƚ�tty��־��Ϊ���� */
        flag = TTY_NORMAL;
        /* ���������ַ������� */
        port->icount.rx++;

        /* �ж��Ƿ����Rx error
         * if (unlikely(uerstat & S3C2410_UERSTAT_ANY))��ͬ��
         * if (uerstat & S3C2410_UERSTAT_ANY)
         * ֻ��unlikely��ʾuerstat & S3C2410_UERSTAT_ANY��ֵΪ�ٵĿ����Դ�һЩ
         * ���⻹��һ��likely(value)��ʾvalue��ֵΪ��Ŀ����Ը���һЩ
         */
        if (unlikely(uerstat & S3C2410_UERSTAT_ANY))
        {
            /* ��break����,����icount.brk������ */
            if (uerstat & S3C2410_UERSTAT_BREAK)
            {
                port->icount.brk++;
                if (uart_handle_break(port))
                 goto ignore_char;
            }

            /* ��frame����,����icount.frame������ */
            if (uerstat & S3C2410_UERSTAT_FRAME)
                port->icount.frame++;
            /* ��overrun����,����icount.overrun������ */
            if (uerstat & S3C2410_UERSTAT_OVERRUN)
                port->icount.overrun++;

            /* �鿴�����Ƿ���ĸ�Rx error
             * port->read_status_mask���������Ǹ���Ȥ��Rx error status
             */
            uerstat &= port->read_status_mask;

            /* �����ǹ��ĸ�Rx error,��flag����Ϊ��Ӧ��error flag */
            if (uerstat & S3C2410_UERSTAT_BREAK)
                flag = TTY_BREAK;
            else if (uerstat & S3C2410_UERSTAT_PARITY)
                flag = TTY_PARITY;
            else if (uerstat & ( S3C2410_UERSTAT_FRAME | S3C2410_UERSTAT_OVERRUN))
                flag = TTY_FRAME;
        }

        /* ����sys�ַ� */
        if (uart_handle_sysrq_char(port, ch))
            goto ignore_char;

        /* �����յ����ַ����뵽tty�豸��flip���� */
        uart_insert_char(port, uerstat, S3C2410_UERSTAT_OVERRUN, ch, flag);

ignore_char:
        continue;
    }
    
    /* ˢ��tty�豸��flip����,�����ܵ������ݴ����й���� */
    tty_flip_buffer_push(tty);

    return IRQ_HANDLED;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

/* ���ڷ����жϴ�����,���û��ռ������(�����ڻ��λ���xmit��)���ͳ�ȥ */
static irqreturn_t gprs_uart_tx_chars(int irq, void *dev_id)
{
#ifdef ARCH_ARM
    struct uart_port *port = dev_id;
    struct circ_buf *xmit = &port->info->xmit;        /* ��ȡ���߻��� */
    int count = 256;

    /* ��������xChar�ַ� */
    if (port->x_char)
    {
        /* ����xChar���ͳ�ȥ */
        wr_regb(port, S3C2410_UTXH, port->x_char);
        /* �������ͼ��� */
        port->icount.tx++;
        /* ���xChar */        
        port->x_char = 0;
        /* �˳��жϴ��� */        
        goto out;
    }

    /* ���û�и�����ַ���Ҫ����(���λ���Ϊ��)��
     * ����uart Tx��ֹͣ��
     * ��ֹͣuart���˳��жϴ�����
     */
    if (uart_circ_empty(xmit) || uart_tx_stopped(port))
    {
        gprs_uart_stop_tx(port);
        goto out;
    }

    /* ѭ����������,ֱ�����λ���Ϊ��,���һ���жϷ���256�ֽ����� */
    while (!uart_circ_empty(xmit) && count-- > 0)
    {
        /* ��Tx FIFO����,�˳�ѭ�� */
        if (rd_regl(port, S3C2410_UFSTAT) & S3C2410_UFSTAT_TXFULL)
            break;

        /* ��Ҫ���͵�����д��Tx FIFO */
        wr_regb(port, S3C2410_UTXH, xmit->buf[xmit->tail]);
        /* ����ѭ����������һҪ���͵����� */
        xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
        port->icount.tx++;
    }

    /* ������λ�������ʣ����ַ�����WAKEUP_CHARS�������ϲ� */    
    if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
        uart_write_wakeup(port);

    /* ������λ���Ϊ�գ���ֹͣ���� */
    if (uart_circ_empty(xmit))
        gprs_uart_stop_tx(port);

 out:
    return IRQ_HANDLED;
#else
        printk("%s %d\n",__FUNCTION__,__LINE__);
        return IRQ_HANDLED;
#endif
}

/* �������ڶ˿�,�ڴ򿪸��������豸�ļ�ʱ����øú��������봮���ж�,�����ô���Ϊ�ɽ���,Ҳ�ɷ��� */
static int gprs_uart_startup(struct uart_port *port)
{
    unsigned long flags;
    int ret;
    const char *portname = to_platform_device(port->dev)->name;

    /* ���ô���Ϊ���ɽ���,Ҳ���ɷ��� */
    rx_enabled(port) = 0;
    tx_enabled(port) = 0;

    spin_lock_irqsave(&port->lock, flags);

    /* ��������ж� */
    ret = request_irq(RX_IRQ(port), gprs_uart_rx_chars, 0, portname, port);
    if (ret != 0)
    {
        printk(KERN_ERR "cannot get irq %d\n", RX_IRQ(port));
        return ret;
    }    

    /* ���ô���Ϊ������� */
    rx_enabled(port) = 1;

    /* ���뷢���ж� */
    ret = request_irq(TX_IRQ(port), gprs_uart_tx_chars, 0, portname, port);
    if (ret)
    {
        printk(KERN_ERR "cannot get irq %d\n", TX_IRQ(port));
        rx_enabled(port) = 0;
        free_irq(RX_IRQ(port), port);
        goto err;
    }    
    
    /* ���ô���Ϊ������ */
    tx_enabled(port) = 1;

err:
    spin_unlock_irqrestore(&port->lock, flags);
    return ret;
}

/* �رմ���,�ڹر��������豸�ļ�ʱ����øú���,�ͷŴ����ж� */
static void gprs_uart_shutdown(struct uart_port *port)
{
    rx_enabled(port) = 0;                /* ���ô���Ϊ���������    */
    free_irq(RX_IRQ(port), port);        /* �ͷŽ����ж�    */
    tx_enabled(port) = 0;                /* ���ô���Ϊ��������    */
    free_irq(TX_IRQ(port), port);        /* �ͷŷ����ж�    */
}

/* ���ô��ڲ��� */
static void gprs_uart_set_termios(struct uart_port *port,
                 struct ktermios *termios,
                 struct ktermios *old)
{
#ifdef ARCH_ARM
    unsigned long flags;
    unsigned int baud, quot;
    unsigned int ulcon, ufcon = 0;

    /* ��֧��moden�����ź���
     * HUPCL:    �ر�ʱ�Ҷ�moden
     * CMSPAR:    mark or space (stick) parity
     * CLOCAL:    �����κ�moden������
     */
    termios->c_cflag &= ~(HUPCL | CMSPAR);
    termios->c_cflag |= CLOCAL;

    /* ��ȡ�û����õĴ��ڲ�����,�������Ƶ��(���ڲ����ʳ���quot) */
    baud = uart_get_baud_rate(port, termios, old, 0, 115200*8);
    if (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
        quot = port->custom_divisor;
    else
        quot = port->uartclk / baud / 16 - 1;

    /* ���������ֳ� */
    switch (termios->c_cflag & CSIZE)
    {
    case CS5:
        ulcon = S3C2410_LCON_CS5;
        break;
    case CS6:
        ulcon = S3C2410_LCON_CS6;
        break;
    case CS7:
        ulcon = S3C2410_LCON_CS7;
        break;
    case CS8:
    default:
        ulcon = S3C2410_LCON_CS8;
        break;
    }

    /* �Ƿ�Ҫ����������ֹͣλ(CSTOPB) */        
    if (termios->c_cflag & CSTOPB)
        ulcon |= S3C2410_LCON_STOPB;

    /* �Ƿ�ʹ����ż���� */
    if (termios->c_cflag & PARENB)
    {
        if (termios->c_cflag & PARODD)  /* ��У�� */
            ulcon |= S3C2410_LCON_PODD;
        else                            /* żУ�� */
            ulcon |= S3C2410_LCON_PEVEN;
    }
    else                                /* ��У�� */
    {
        ulcon |= S3C2410_LCON_PNONE;
    }

    if (port->fifosize > 1)
        ufcon |= S3C2410_UFCON_FIFOMODE | S3C2410_UFCON_RXTRIG8;

    spin_lock_irqsave(&port->lock, flags);

    /* ����FIFO���ƼĴ������߿��ƼĴ����Ͳ����ʳ����Ĵ��� */
    wr_regl(port, S3C2410_UFCON, ufcon);
    wr_regl(port, S3C2410_ULCON, ulcon);
    wr_regl(port, S3C2410_UBRDIV, quot);

    /* ���´���FIFO�ĳ�ʱʱ�� */
    uart_update_timeout(port, termios->c_cflag, baud);

    /* �������Ǹ���Ȥ��Rx error */
    port->read_status_mask = S3C2410_UERSTAT_OVERRUN;
    if (termios->c_iflag & INPCK)
        port->read_status_mask |= S3C2410_UERSTAT_FRAME | S3C2410_UERSTAT_PARITY;

    /* �������Ǻ��Ե�Rx error */
    port->ignore_status_mask = 0;
    if (termios->c_iflag & IGNPAR)
        port->ignore_status_mask |= S3C2410_UERSTAT_OVERRUN;
    if (termios->c_iflag & IGNBRK && termios->c_iflag & IGNPAR)
        port->ignore_status_mask |= S3C2410_UERSTAT_FRAME;

    /* ��δ����CREAD(ʹ�ý�����),���������Rx error*/
    if ((termios->c_cflag & CREAD) == 0)
        port->ignore_status_mask |= RXSTAT_DUMMY_READ;

    spin_unlock_irqrestore(&port->lock, flags);
#else
        printk("%s %d\n",__FUNCTION__,__LINE__);
#endif
}

/* ��ȡ�������� */
static const char *gprs_uart_type(struct uart_port *port)
{/* ���������������͵��ַ���ָ�� */
    return port->type == PORT_S3C2410 ? "gprs_uart:s3c2410_uart2" : NULL;
}

/* ���봮��һЩ��Ҫ����Դ,��IO�˿�/IO�ڴ���Դ,��Ҫʱ����������ӳ�䴮�ڶ˿� */
static int gprs_uart_request_port(struct uart_port *port)
{
    struct resource *res;
    const char *name = to_platform_device(port->dev)->name;

    /* request_mem_region�������IO�ڴ�,�ӿ�ʼport->mapbase,��СMAP_SIZE
     * port->mapbase���浱ǰ���ڵļĴ�������ַ(����)
     * uart2: 0x50008000
     */
    res = request_mem_region(port->mapbase, MAP_SIZE, name);
    if (res == NULL)
    {
        printk(KERN_ERR"request_mem_region error: %p\n", res);
        return -EBUSY;
    }
    
    return 0;
}

/* �ͷŴ����������IO�˿�/IO�ڴ���Դ,��Ҫʱ����iounmap */
static void gprs_uart_release_port(struct uart_port *port)
{
    /* �ͷ��ѷ���IO�ڴ� */
    release_mem_region(port->mapbase, MAP_SIZE);
}

/* ִ�д���������Զ����� */
static void gprs_uart_config_port(struct uart_port *port, int flags)
{    
    int retval;

    /* ���󴮿� */
    retval = gprs_uart_request_port(port);
    /* ���ô������� */
    if (flags & UART_CONFIG_TYPE && retval == 0)
        port->type = PORT_S3C2410;
}

/* The UART operations structure */
static struct uart_ops gprs_uart_ops = {
    .start_tx        = gprs_uart_start_tx,      /* Start transmitting */
    .stop_tx        = gprs_uart_stop_tx,        /* Stop transmission */
    .stop_rx        = gprs_uart_stop_rx,        /* Stop reception */
    .enable_ms        = gprs_uart_enable_ms,    /* Enable modem status signals */
    .tx_empty        = gprs_uart_tx_empty,      /* Transmitter busy? */
    .get_mctrl        = gprs_uart_get_mctrl,    /* Get modem control */
    .set_mctrl        = gprs_uart_set_mctrl,    /* Set modem control */
    .break_ctl        = gprs_uart_break_ctl,    /* Set break signal */
    .startup        = gprs_uart_startup,        /* App opens GPRS_UART */
    .shutdown        = gprs_uart_shutdown,      /* App closes GPRS_UART */
    .set_termios    = gprs_uart_set_termios,    /* Set termios */
    .type            = gprs_uart_type,          /* Get UART type */
    .request_port    = gprs_uart_request_port,  /* Claim resources associated with a GPRS_UART port */
    .release_port    = gprs_uart_release_port,  /* Release resources associated with a GPRS_UART port */
    .config_port    = gprs_uart_config_port,    /* Configure when driver adds a GPRS_UART port */
};

/* Uart driver for GPRS_UART */
static struct uart_driver gprs_uart_driver = {
    .owner = THIS_MODULE,                /* Owner */
    .driver_name = DEV_NAME,             /* Driver name */
    .dev_name = DEV_NAME,                /* Device node name */
    .major = GPRS_UART_MAJOR,            /* Major number */
    .minor = GPRS_UART_MINOR,            /* Minor number start */
    .nr = 1,                             /* Number of UART ports */
};

/* Uart port for GPRS_UART port */
static struct uart_port gprs_uart_port = {
        .irq        = IRQ_S3CUART_RX2,           /* IRQ */
        .fifosize    = GPRS_UART_FIFO_SIZE,      /* Size of the FIFO */
        .iotype        = UPIO_MEM,               /* IO memory */
        .flags        = UPF_BOOT_AUTOCONF,       /* UART port flag */
        .ops        = &gprs_uart_ops,            /* UART operations */
        .line        = 0,                        /* UART port number */
        .lock        = __SPIN_LOCK_UNLOCKED(gprs_uart_port.lock),
};

/* ��ʼ��ָ�����ڶ˿� */
static int gprs_uart_init_port(struct uart_port *port, struct platform_device *platdev)
{
#ifdef ARCH_ARM
    unsigned long flags;
    unsigned int gphcon;
    
    if (platdev == NULL)
        return -ENODEV;

    port->dev        = &platdev->dev;

    /* ���ô��ڲ�����ʱ��Ƶ�� */
    port->uartclk    = clk_get_rate(clk_get(&platdev->dev, "pclk"));

    /* ���ô��ڵļĴ�������ַ(����): 0x50008000 */
    port->mapbase    = S3C2410_PA_UART2;
    
    /* ���õ�ǰ���ڵļĴ�������ַ(����): 0xF5008000 */        
    port->membase    = S3C24XX_VA_UART + (S3C2410_PA_UART2 - S3C24XX_PA_UART);

    spin_lock_irqsave(&port->lock, flags);

    wr_regl(port, S3C2410_UCON, S3C2410_UCON_DEFAULT);
    wr_regl(port, S3C2410_ULCON, S3C2410_LCON_CS8 | S3C2410_LCON_PNONE);
    wr_regl(port, S3C2410_UFCON, S3C2410_UFCON_FIFOMODE
        | S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_RESETBOTH);

    /* ��I/O port H��gph6��gph7����ΪTXD2��RXD2 */
    gphcon = readl(S3C2410_GPHCON);
    gphcon &= ~((0x5) << 12);
    writel(gphcon, S3C2410_GPHCON);
    
    spin_unlock_irqrestore(&port->lock, flags);
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
#endif
    return 0;
}

/* Platform driver probe */
static int __init gprs_uart_probe(struct platform_device *dev)
{
    int ret;
    
    /* ��ʼ������ */
    ret = gprs_uart_init_port(&gprs_uart_port, dev);
    if (ret < 0)
    {
        printk(KERN_ERR"gprs_uart_probe: gprs_uart_init_port error: %d\n", ret);
        return ret;
    }    

    /* ��Ӵ��� */
    ret = uart_add_one_port(&gprs_uart_driver, &gprs_uart_port);
    if (ret < 0)
    {
        printk(KERN_ERR"gprs_uart_probe: uart_add_one_port error: %d\n", ret);
        return ret;    
    }

    /* ������uart_port�ṹ�屣����platform_device->dev->driver_data�� */
    platform_set_drvdata(dev, &gprs_uart_port);

    return 0;
}

/* Called when the platform driver is unregistered */
static int gprs_uart_remove(struct platform_device *dev)
{
    platform_set_drvdata(dev, NULL);

    /* �Ƴ����� */
    uart_remove_one_port(&gprs_uart_driver, &gprs_uart_port);
    return 0;
}

/* Suspend power management event */
static int gprs_uart_suspend(struct platform_device *dev, pm_message_t state)
{
    uart_suspend_port(&gprs_uart_driver, &gprs_uart_port);
    return 0;
}

/* Resume after a previous suspend */
static int gprs_uart_resume(struct platform_device *dev)
{
    uart_resume_port(&gprs_uart_driver, &gprs_uart_port);
    return 0;
}

/* Platform driver for GPRS_UART */
static struct platform_driver gprs_plat_driver = {
    .probe = gprs_uart_probe,                /* Probe method */
    .remove = __exit_p(gprs_uart_remove),    /* Detach method */
    .suspend = gprs_uart_suspend,            /* Power suspend */
    .resume = gprs_uart_resume,              /* Resume after a suspend */
    .driver = {
        .owner    = THIS_MODULE,
        .name = DEV_NAME,                    /* Driver name */
    },
};

/* Platform device for GPRS_UART */
struct platform_device *gprs_plat_device; 

static int __init gprs_init_module(void)
{
    int retval;

    /* Register uart_driver for GPRS_UART */
    retval = uart_register_driver(&gprs_uart_driver);
    if (0 != retval)
    {
        printk(KERN_ERR "gprs_init_module: can't register the GPRS_UART driver %d\n", retval);
        return retval;
    }

    /* Register platform device for GPRS_UART. Usually called
    during architecture-specific setup */
    gprs_plat_device = platform_device_register_simple(DEV_NAME, 0, NULL, 0);
    if (IS_ERR(gprs_plat_device)) 
    {
        retval = PTR_ERR(gprs_plat_device);
        printk(KERN_ERR "gprs_init_module: can't register platform device %d\n", retval);
        goto fail_reg_plat_dev;
    }

    /* Announce a matching driver for the platform
    devices registered above */
    retval = platform_driver_register(&gprs_plat_driver);
    if (0 != retval)
    {
        printk(KERN_ERR "gprs_init_module: can't register platform driver %d\n", retval);
        goto fail_reg_plat_drv;
    }

    return 0; /* succeed */

fail_reg_plat_drv:
    platform_device_unregister(gprs_plat_device);
fail_reg_plat_dev:
    uart_unregister_driver(&gprs_uart_driver);
    return retval;
}

static void __exit gprs_exit_module(void)
{
    /* The order of unregistration is important. Unregistering the
    UART driver before the platform driver will crash the system */

    /* Unregister the platform driver */
    platform_driver_unregister(&gprs_plat_driver);

    /* Unregister the platform devices */
    platform_device_unregister(gprs_plat_device);

    /* Unregister the GPRS_UART driver */
    uart_unregister_driver(&gprs_uart_driver);
}

module_init(gprs_init_module);
module_exit(gprs_exit_module);

MODULE_AUTHOR("lingd");
MODULE_LICENSE("Dual BSD/GPL");

