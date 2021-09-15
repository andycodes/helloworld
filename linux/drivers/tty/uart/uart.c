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



#define DEV_NAME            "gprs_uart"     /* 设备名 */
/* 这里将串口的主设备号设为0,则串口设备编号由内核动态分配;你也可指定串口的设备编号 */
#define GPRS_UART_MAJOR        0            /* 主设备号 */
#define GPRS_UART_MINOR        0            /* 次设备号 */
#define GPRS_UART_FIFO_SIZE    16           /* 串口FIFO的大小 */
#define RXSTAT_DUMMY_READ    (0x10000000)
#define MAP_SIZE             (0x100)        /* 要映射的串口IO内存区大小 */

/* 串口发送中断号 */
#define TX_IRQ(port) ((port)->irq + 1)
/* 串口接收中断号 */
#define RX_IRQ(port) ((port)->irq)

/* 允许串口接收字符的标志 */
#define tx_enabled(port) ((port)->unused[0])
/* 允许串口发送字符的标志 */
#define rx_enabled(port) ((port)->unused[1])

/* 获取寄存器地址 */
#define portaddr(port, reg) ((port)->membase + (reg))

/* 读8位宽的寄存器 */
#define rd_regb(port, reg) (ioread8(portaddr(port, reg)))
/* 读32位宽的寄存器 */
#define rd_regl(port, reg) (ioread32(portaddr(port, reg)))
/* 写8位宽的寄存器 */
#define wr_regb(port, reg, val) \
    do { iowrite8(val, portaddr(port, reg)); } while(0)
/* 写32位宽的寄存器 */        
#define wr_regl(port, reg, val) \
    do { iowrite32(val, portaddr(port, reg)); } while(0)


/* 禁止串口发送数据 */
static void gprs_uart_stop_tx(struct uart_port *port)
{
    if (tx_enabled(port))            /* 若串口已启动发送 */
    {        
        disable_irq(TX_IRQ(port));   /* 禁止发送中断 */
        tx_enabled(port) = 0;        /* 设置串口为未启动发送 */
    }
}

/* 使能串口发送数据 */
static void gprs_uart_start_tx(struct uart_port *port)
{
    if (!tx_enabled(port))           /* 若串口未启动发送 */
    {
        enable_irq(TX_IRQ(port));    /* 使能发送中断 */
        tx_enabled(port) = 1;        /* 设置串口为已启动发送 */
    }    
}

/* 禁止串口接收数据 */
static void gprs_uart_stop_rx(struct uart_port *port)
{
    if (rx_enabled(port))            /* 若串口已启动接收 */
    {
        disable_irq(RX_IRQ(port));   /* 禁止接收中断 */
        rx_enabled(port) = 0;        /* 设置串口为未启动接收 */
    }
}

/* 使能modem的状态信号 */
static void gprs_uart_enable_ms(struct uart_port *port)
{
}

/* 串口的Tx FIFO缓存是否为空 */
static unsigned int gprs_uart_tx_empty(struct uart_port *port)
{
#ifdef ARCH_ARM
    int ret = 1;
    unsigned long ufstat = rd_regl(port, S3C2410_UFSTAT);
    unsigned long ufcon = rd_regl(port, S3C2410_UFCON);

    if (ufcon & S3C2410_UFCON_FIFOMODE)    /* 若使能了FIFO */
    {
        if ((ufstat & S3C2410_UFSTAT_TXMASK) != 0 ||    /* 0 <FIFO <=15 */
                (ufstat & S3C2410_UFSTAT_TXFULL))       /* FIFO满 */
            ret = 0;
    }
    else    /* 若未使能了FIFO,则判断发送缓存和发送移位寄存器是否均为空 */
    {
        ret = rd_regl(port, S3C2410_UTRSTAT) & S3C2410_UTRSTAT_TXE;
    }
            
    return ret;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

/* 获取串口modem控制,因为uart2无modem控制,所以CTS、DSR直接返回有效 */
static unsigned int gprs_uart_get_mctrl(struct uart_port *port)
{
    return (TIOCM_CTS | TIOCM_DSR | TIOCM_CAR);
}

/* 设置串口modem控制 */
static void gprs_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{

}

/* 设置break信号 */
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

/* 返回Rx FIFO已存多少数据 */
static int gprs_uart_rx_fifocnt(unsigned long ufstat)
{
#ifdef ARCH_ARM
    /* 若Rx FIFO已满,返回FIFO的大小 */
    if (ufstat & S3C2410_UFSTAT_RXFULL)
        return GPRS_UART_FIFO_SIZE;

    /* 若FIFO未满,返回Rx FIFO已存了多少字节数据 */
    return (ufstat & S3C2410_UFSTAT_RXMASK) >> S3C2410_UFSTAT_RXSHIFT;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

#define S3C2410_UERSTAT_PARITY (0x1000)

/* 串口接收中断处理函数,获取串口接收到的数据,并将这些数据递交给行规则层 */
static irqreturn_t gprs_uart_rx_chars(int irq, void *dev_id)
{
#ifdef ARCH_ARM
    struct uart_port *port = dev_id;
    struct tty_struct *tty = port->info->tty;
    unsigned int ufcon, ch, flag, ufstat, uerstat;
    int max_count = 64;

    /* 循环接收数据,最多一次中断接收64字节数据 */
    while (max_count-- > 0)
    {
        ufcon = rd_regl(port, S3C2410_UFCON);
        ufstat = rd_regl(port, S3C2410_UFSTAT);

        /* 若Rx FIFO无数据了,跳出循环 */
        if (gprs_uart_rx_fifocnt(ufstat) == 0)
            break;

        /* 读取Rx error状态寄存器 */
        uerstat = rd_regl(port, S3C2410_UERSTAT);
        /* 读取已接受到的数据 */
        ch = rd_regb(port, S3C2410_URXH);

        /* insert the character into the buffer */
        /* 先将tty标志设为正常 */
        flag = TTY_NORMAL;
        /* 递增接收字符计数器 */
        port->icount.rx++;

        /* 判断是否存在Rx error
         * if (unlikely(uerstat & S3C2410_UERSTAT_ANY))等同于
         * if (uerstat & S3C2410_UERSTAT_ANY)
         * 只是unlikely表示uerstat & S3C2410_UERSTAT_ANY的值为假的可能性大一些
         * 另外还有一个likely(value)表示value的值为真的可能性更大一些
         */
        if (unlikely(uerstat & S3C2410_UERSTAT_ANY))
        {
            /* 若break错误,递增icount.brk计算器 */
            if (uerstat & S3C2410_UERSTAT_BREAK)
            {
                port->icount.brk++;
                if (uart_handle_break(port))
                 goto ignore_char;
            }

            /* 若frame错误,递增icount.frame计算器 */
            if (uerstat & S3C2410_UERSTAT_FRAME)
                port->icount.frame++;
            /* 若overrun错误,递增icount.overrun计算器 */
            if (uerstat & S3C2410_UERSTAT_OVERRUN)
                port->icount.overrun++;

            /* 查看我们是否关心该Rx error
             * port->read_status_mask保存着我们感兴趣的Rx error status
             */
            uerstat &= port->read_status_mask;

            /* 若我们关心该Rx error,则将flag设置为对应的error flag */
            if (uerstat & S3C2410_UERSTAT_BREAK)
                flag = TTY_BREAK;
            else if (uerstat & S3C2410_UERSTAT_PARITY)
                flag = TTY_PARITY;
            else if (uerstat & ( S3C2410_UERSTAT_FRAME | S3C2410_UERSTAT_OVERRUN))
                flag = TTY_FRAME;
        }

        /* 处理sys字符 */
        if (uart_handle_sysrq_char(port, ch))
            goto ignore_char;

        /* 将接收到的字符插入到tty设备的flip缓冲 */
        uart_insert_char(port, uerstat, S3C2410_UERSTAT_OVERRUN, ch, flag);

ignore_char:
        continue;
    }
    
    /* 刷新tty设备的flip缓冲,将接受到的数据传给行规则层 */
    tty_flip_buffer_push(tty);

    return IRQ_HANDLED;
#else
    printk("%s %d\n",__FUNCTION__,__LINE__);
    return 0;
#endif
}

/* 串口发送中断处理函数,将用户空间的数据(保存在环形缓冲xmit里)发送出去 */
static irqreturn_t gprs_uart_tx_chars(int irq, void *dev_id)
{
#ifdef ARCH_ARM
    struct uart_port *port = dev_id;
    struct circ_buf *xmit = &port->info->xmit;        /* 获取环线缓冲 */
    int count = 256;

    /* 若设置了xChar字符 */
    if (port->x_char)
    {
        /* 将该xChar发送出去 */
        wr_regb(port, S3C2410_UTXH, port->x_char);
        /* 递增发送计数 */
        port->icount.tx++;
        /* 清除xChar */        
        port->x_char = 0;
        /* 退出中断处理 */        
        goto out;
    }

    /* 如果没有更多的字符需要发送(环形缓冲为空)，
     * 或者uart Tx已停止，
     * 则停止uart并退出中断处理函数
     */
    if (uart_circ_empty(xmit) || uart_tx_stopped(port))
    {
        gprs_uart_stop_tx(port);
        goto out;
    }

    /* 循环发送数据,直到环形缓冲为空,最多一次中断发送256字节数据 */
    while (!uart_circ_empty(xmit) && count-- > 0)
    {
        /* 若Tx FIFO已满,退出循环 */
        if (rd_regl(port, S3C2410_UFSTAT) & S3C2410_UFSTAT_TXFULL)
            break;

        /* 将要发送的数据写入Tx FIFO */
        wr_regb(port, S3C2410_UTXH, xmit->buf[xmit->tail]);
        /* 移向循环缓冲中下一要发送的数据 */
        xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
        port->icount.tx++;
    }

    /* 如果环形缓冲区中剩余的字符少于WAKEUP_CHARS，唤醒上层 */    
    if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
        uart_write_wakeup(port);

    /* 如果环形缓冲为空，则停止发送 */
    if (uart_circ_empty(xmit))
        gprs_uart_stop_tx(port);

 out:
    return IRQ_HANDLED;
#else
        printk("%s %d\n",__FUNCTION__,__LINE__);
        return IRQ_HANDLED;
#endif
}

/* 启动串口端口,在打开该驱动的设备文件时会调用该函数来申请串口中断,并设置串口为可接受,也可发送 */
static int gprs_uart_startup(struct uart_port *port)
{
    unsigned long flags;
    int ret;
    const char *portname = to_platform_device(port->dev)->name;

    /* 设置串口为不可接受,也不可发送 */
    rx_enabled(port) = 0;
    tx_enabled(port) = 0;

    spin_lock_irqsave(&port->lock, flags);

    /* 申请接收中断 */
    ret = request_irq(RX_IRQ(port), gprs_uart_rx_chars, 0, portname, port);
    if (ret != 0)
    {
        printk(KERN_ERR "cannot get irq %d\n", RX_IRQ(port));
        return ret;
    }    

    /* 设置串口为允许接收 */
    rx_enabled(port) = 1;

    /* 申请发送中断 */
    ret = request_irq(TX_IRQ(port), gprs_uart_tx_chars, 0, portname, port);
    if (ret)
    {
        printk(KERN_ERR "cannot get irq %d\n", TX_IRQ(port));
        rx_enabled(port) = 0;
        free_irq(RX_IRQ(port), port);
        goto err;
    }    
    
    /* 设置串口为允许发送 */
    tx_enabled(port) = 1;

err:
    spin_unlock_irqrestore(&port->lock, flags);
    return ret;
}

/* 关闭串口,在关闭驱动的设备文件时会调用该函数,释放串口中断 */
static void gprs_uart_shutdown(struct uart_port *port)
{
    rx_enabled(port) = 0;                /* 设置串口为不允许接收    */
    free_irq(RX_IRQ(port), port);        /* 释放接收中断    */
    tx_enabled(port) = 0;                /* 设置串口为不允许发送    */
    free_irq(TX_IRQ(port), port);        /* 释放发送中断    */
}

/* 设置串口参数 */
static void gprs_uart_set_termios(struct uart_port *port,
                 struct ktermios *termios,
                 struct ktermios *old)
{
#ifdef ARCH_ARM
    unsigned long flags;
    unsigned int baud, quot;
    unsigned int ulcon, ufcon = 0;

    /* 不支持moden控制信号线
     * HUPCL:    关闭时挂断moden
     * CMSPAR:    mark or space (stick) parity
     * CLOCAL:    忽略任何moden控制线
     */
    termios->c_cflag &= ~(HUPCL | CMSPAR);
    termios->c_cflag |= CLOCAL;

    /* 获取用户设置的串口波特率,并计算分频数(串口波特率除数quot) */
    baud = uart_get_baud_rate(port, termios, old, 0, 115200*8);
    if (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
        quot = port->custom_divisor;
    else
        quot = port->uartclk / baud / 16 - 1;

    /* 设置数据字长 */
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

    /* 是否要求设置两个停止位(CSTOPB) */        
    if (termios->c_cflag & CSTOPB)
        ulcon |= S3C2410_LCON_STOPB;

    /* 是否使用奇偶检验 */
    if (termios->c_cflag & PARENB)
    {
        if (termios->c_cflag & PARODD)  /* 奇校验 */
            ulcon |= S3C2410_LCON_PODD;
        else                            /* 偶校验 */
            ulcon |= S3C2410_LCON_PEVEN;
    }
    else                                /* 无校验 */
    {
        ulcon |= S3C2410_LCON_PNONE;
    }

    if (port->fifosize > 1)
        ufcon |= S3C2410_UFCON_FIFOMODE | S3C2410_UFCON_RXTRIG8;

    spin_lock_irqsave(&port->lock, flags);

    /* 设置FIFO控制寄存器、线控制寄存器和波特率除数寄存器 */
    wr_regl(port, S3C2410_UFCON, ufcon);
    wr_regl(port, S3C2410_ULCON, ulcon);
    wr_regl(port, S3C2410_UBRDIV, quot);

    /* 更新串口FIFO的超时时限 */
    uart_update_timeout(port, termios->c_cflag, baud);

    /* 设置我们感兴趣的Rx error */
    port->read_status_mask = S3C2410_UERSTAT_OVERRUN;
    if (termios->c_iflag & INPCK)
        port->read_status_mask |= S3C2410_UERSTAT_FRAME | S3C2410_UERSTAT_PARITY;

    /* 设置我们忽略的Rx error */
    port->ignore_status_mask = 0;
    if (termios->c_iflag & IGNPAR)
        port->ignore_status_mask |= S3C2410_UERSTAT_OVERRUN;
    if (termios->c_iflag & IGNBRK && termios->c_iflag & IGNPAR)
        port->ignore_status_mask |= S3C2410_UERSTAT_FRAME;

    /* 若未设置CREAD(使用接收器),则忽略所有Rx error*/
    if ((termios->c_cflag & CREAD) == 0)
        port->ignore_status_mask |= RXSTAT_DUMMY_READ;

    spin_unlock_irqrestore(&port->lock, flags);
#else
        printk("%s %d\n",__FUNCTION__,__LINE__);
#endif
}

/* 获取串口类型 */
static const char *gprs_uart_type(struct uart_port *port)
{/* 返回描述串口类型的字符串指针 */
    return port->type == PORT_S3C2410 ? "gprs_uart:s3c2410_uart2" : NULL;
}

/* 申请串口一些必要的资源,如IO端口/IO内存资源,必要时还可以重新映射串口端口 */
static int gprs_uart_request_port(struct uart_port *port)
{
    struct resource *res;
    const char *name = to_platform_device(port->dev)->name;

    /* request_mem_region请求分配IO内存,从开始port->mapbase,大小MAP_SIZE
     * port->mapbase保存当前串口的寄存器基地址(物理)
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

/* 释放串口已申请的IO端口/IO内存资源,必要时还需iounmap */
static void gprs_uart_release_port(struct uart_port *port)
{
    /* 释放已分配IO内存 */
    release_mem_region(port->mapbase, MAP_SIZE);
}

/* 执行串口所需的自动配置 */
static void gprs_uart_config_port(struct uart_port *port, int flags)
{    
    int retval;

    /* 请求串口 */
    retval = gprs_uart_request_port(port);
    /* 设置串口类型 */
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

/* 初始化指定串口端口 */
static int gprs_uart_init_port(struct uart_port *port, struct platform_device *platdev)
{
#ifdef ARCH_ARM
    unsigned long flags;
    unsigned int gphcon;
    
    if (platdev == NULL)
        return -ENODEV;

    port->dev        = &platdev->dev;

    /* 设置串口波特率时钟频率 */
    port->uartclk    = clk_get_rate(clk_get(&platdev->dev, "pclk"));

    /* 设置串口的寄存器基地址(物理): 0x50008000 */
    port->mapbase    = S3C2410_PA_UART2;
    
    /* 设置当前串口的寄存器基地址(虚拟): 0xF5008000 */        
    port->membase    = S3C24XX_VA_UART + (S3C2410_PA_UART2 - S3C24XX_PA_UART);

    spin_lock_irqsave(&port->lock, flags);

    wr_regl(port, S3C2410_UCON, S3C2410_UCON_DEFAULT);
    wr_regl(port, S3C2410_ULCON, S3C2410_LCON_CS8 | S3C2410_LCON_PNONE);
    wr_regl(port, S3C2410_UFCON, S3C2410_UFCON_FIFOMODE
        | S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_RESETBOTH);

    /* 将I/O port H的gph6和gph7设置为TXD2和RXD2 */
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
    
    /* 初始化串口 */
    ret = gprs_uart_init_port(&gprs_uart_port, dev);
    if (ret < 0)
    {
        printk(KERN_ERR"gprs_uart_probe: gprs_uart_init_port error: %d\n", ret);
        return ret;
    }    

    /* 添加串口 */
    ret = uart_add_one_port(&gprs_uart_driver, &gprs_uart_port);
    if (ret < 0)
    {
        printk(KERN_ERR"gprs_uart_probe: uart_add_one_port error: %d\n", ret);
        return ret;    
    }

    /* 将串口uart_port结构体保存在platform_device->dev->driver_data中 */
    platform_set_drvdata(dev, &gprs_uart_port);

    return 0;
}

/* Called when the platform driver is unregistered */
static int gprs_uart_remove(struct platform_device *dev)
{
    platform_set_drvdata(dev, NULL);

    /* 移除串口 */
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

