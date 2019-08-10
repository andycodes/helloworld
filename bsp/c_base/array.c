#include <stdio.h>

#define REG_MAX  4
#define BIT_MAX  3

typedef enum __CPU_TYPE__
{
    ACPU_TYPE = 4,
    BCPU_TYPE,
    CCPU_TYPE,
    DCPU_TYPE,
    ECPU_TYPE,
    FCPU_TYPE,
    CPU_BUTTOM
}CPU_TYPE;

typedef struct __AT_CPU_TYPE__
{
    int        reg_id;
    int        bit_id;
    CPU_TYPE   cpu_id;
    char *name;
}AT_CPU_TYPE;

int a[]= {1,2,3};

AT_CPU_TYPE  which_cpu[]=
{
    {1,3,ACPU_TYPE,"ACPU"},
    {2,1,BCPU_TYPE,"BCPU"},
    {1,2,CCPU_TYPE,"CCPU"},
    {1,1,DCPU_TYPE,"DCPU"},
    {1,1,ECPU_TYPE,"ECPU"},
    {1,2,FCPU_TYPE,"FCPU"},
};

/*2维数组  [4][3] --必须指定*/
AT_CPU_TYPE  which_double_cpu[2][3]=
{
    [0][0] = {1,3,ACPU_TYPE},/*数组初始化必须加标号 [0][0]*/
    [0][1] = {2,1,BCPU_TYPE},
    [0][2] = {1,2,CCPU_TYPE},
    
    [1][0] = {1,1,DCPU_TYPE},
    [1][1] = {1,1,ECPU_TYPE},
    [1][2] = {1,2,FCPU_TYPE},
};

void cpu_scan(int reg_id,int reg_bit)
{
    unsigned int scan_size = sizeof(which_cpu)/sizeof(which_cpu[0]);
    unsigned int scan_id = 0;

    for(scan_id = 0;scan_id <scan_size; scan_id++)
    {
        if((reg_id == which_cpu[scan_id].reg_id)&&
            (reg_bit == which_cpu[scan_id].bit_id))
        {
            printf("current is %s\n",which_cpu[scan_id].name);
        }
    }
}
    

int main(void)
{
    int* pa = a;
    AT_CPU_TYPE*  witch_cpu = &which_cpu[0];
    AT_CPU_TYPE*  double_cpu = &which_double_cpu[0][0];
    
    printf("pa %p a %p\n *p %d a[0] %d\n",pa,a,*pa,a[0]);

    witch_cpu++;
    printf(" cpu_id %d witch_cpu->cpu_id %d\n",which_cpu[0].cpu_id, witch_cpu->cpu_id);

    double_cpu+=2;
    printf("which_double_cpu[0][1].cpu_id %d double_cpu->cpu_id %d\n",
    which_double_cpu[0][1].cpu_id, double_cpu->cpu_id);

    cpu_scan(2,1);
    
    return 0;
}

#if 0
#define CLKDEV_INIT(d, n, c)    \
    {           \
        .dev_id = d,    \
        .con_id = n,    \
        .clk = c,   \
    }
static struct clk_lookup s3c64xx_clk_lookup[] = {
    CLKDEV_INIT(NULL, "clk_uart_baud2", &clk_p),
    CLKDEV_INIT(NULL, "clk_uart_baud3", &clk_sclk_uclk.clk),
    CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.0", &clk_hsmmc0),
    CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.0", &clk_hsmmc1),
    CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.0", &clk_hsmmc2),
    CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.2", &clk_sclk_mmc0.clk),
    CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.2", &clk_sclk_mmc1.clk),
    CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.2", &clk_sclk_mmc2.clk),
    CLKDEV_INIT(NULL, "spi_busclk0", &clk_p),
    CLKDEV_INIT("s3c6410-spi.0", "spi_busclk1", &clk_sclk_spi0.clk),
    CLKDEV_INIT("s3c6410-spi.0", "spi_busclk2", &clk_48m_spi0),
    CLKDEV_INIT("s3c6410-spi.1", "spi_busclk1", &clk_sclk_spi1.clk),
    CLKDEV_INIT("s3c6410-spi.1", "spi_busclk2", &clk_48m_spi1),
    CLKDEV_INIT("samsung-i2s.0", "i2s_opclk0", &clk_i2s0),
    CLKDEV_INIT("samsung-i2s.0", "i2s_opclk1", &clk_audio_bus0.clk),
    CLKDEV_INIT("samsung-i2s.1", "i2s_opclk0", &clk_i2s1),
    CLKDEV_INIT("samsung-i2s.1", "i2s_opclk1", &clk_audio_bus1.clk),
#ifdef CONFIG_CPU_S3C6410
    CLKDEV_INIT("samsung-i2s.2", "i2s_opclk0", &clk_i2s2),
    CLKDEV_INIT("samsung-i2s.2", "i2s_opclk1", &clk_audio_bus2.clk),
#endif
};
#endif

