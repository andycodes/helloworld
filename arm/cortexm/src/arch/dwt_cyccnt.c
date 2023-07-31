#include "stdint.h"
#include "core_cm55.h"
#include "DWTDelay.h"
  
static int SYSCLK = 0;;
 
void DWT_INIT(int sys_clk)
{
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;

  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/*
 * Return:      void
 * Parameters:  Time: 延时时间
 * Description: 微秒延时
 */
void vDWTDelayUs(float fTime)
{
    volatile uint32_t uiTimeStop = 0u, uiTimeStart = 0u;
 
    uiTimeStart = DWT->CYCCNT;
    uiTimeStop  = (uint32_t)((SystemCoreClock / 1000000u) * fTime) + uiTimeStart;
 
    if(uiTimeStop >= uiTimeStart)
        while((DWT->CYCCNT > uiTimeStart) && (DWT->CYCCNT < uiTimeStop));
    else
        while(!((DWT->CYCCNT > uiTimeStop) && (DWT->CYCCNT < uiTimeStart)));
}

/*
 * Return:      void
 * Parameters:  Time: 延时时间
 * Description: 毫秒延时
 */
void vDWTDelayMs(float fTime)
{
    vDWTDelayUs(fTime * 1000.0f);
}

/*
 * Return:      void
 * Parameters:  Time: 延时时间
 * Description: 秒延时
 */
void vDWTDelayS(float fTime)
{
    int32_t iTime = fTime;
 
    while((iTime--) > 0)
    {
        vDWTDelayUs(1000000.0f);
    }
 
    fTime -= iTime;
    vDWTDelayUs(fTime * 1000000.0f);
}

void reset_timer(){
    DWT_CYCCNT   = (int *)0xE0001004; //address of the register
    DWT_CONTROL  = (int *)0xE0001000; //address of the register
    SCB_DEMCR    = (int *)0xE000EDFC; //address of the register
    *SCB_DEMCR   = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT  = 0; // reset the counter
    *DWT_CONTROL = 0; 
}
 
void start_timer(){
    *DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter
}
 
void stop_timer(){
    *DWT_CONTROL = *DWT_CONTROL | 0 ; // disable the counter    
}
 
unsigned int getCycles(){
    return *DWT_CYCCNT;
}

////////////////////////
 
/**
  ******************************************************************
  * @file    core_delay.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   使用内核寄存器精确延时
  ******************************************************************
  * @attention
  *
  ******************************************************************
  */
  
#include "./delay/core_delay.h"   

/*
**********************************************************************
*         时间戳相关寄存器定义
**********************************************************************
*/
/*
 在Cortex-M里面有一个外设叫DWT(Data Watchpoint and Trace)，
 该外设有一个32位的寄存器叫CYCCNT，它是一个向上的计数器，
 记录的是内核时钟运行的个数，最长能记录的时间为：
 10.74s=2的32次方/400000000
 (假设内核频率为400M，内核跳一次的时间大概为1/400M=2.5ns)
 当CYCCNT溢出之后，会清0重新开始向上计数。
 使能CYCCNT计数的操作步骤：
 1、先使能DWT外设，这个由另外内核调试寄存器DEMCR的位24控制，写1使能
 2、使能CYCCNT寄存器之前，先清0
 3、使能CYCCNT寄存器，这个由DWT_CTRL(代码上宏定义为DWT_CR)的位0控制，写1使能
 */


#define  DWT_CR      *(__IO uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(__IO uint32_t *)0xE0001004
#define  DEM_CR      *(__IO uint32_t *)0xE000EDFC


#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)


/**
  * @brief  初始化时间戳
  * @param  无
  * @retval 无
  * @note   使用延时函数前，必须调用本函数
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    /* 使能DWT外设 */
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;                

    /* DWT CYCCNT寄存器计数清0 */
    DWT_CYCCNT = (uint32_t)0u;

    /* 使能Cortex-M DWT CYCCNT寄存器 */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
  
    return HAL_OK;
}

/**
  * @brief  读取当前时间戳
  * @param  无
  * @retval 当前时间戳，即DWT_CYCCNT寄存器的值
  */
uint32_t CPU_TS_TmrRd(void)
{        
  return ((uint32_t)DWT_CYCCNT);
}

/**
  * @brief  读取当前时间戳
  * @param  无
  * @retval 当前时间戳，即DWT_CYCCNT寄存器的值
  */
uint32_t HAL_GetTick(void)
{        
  return ((uint32_t)DWT_CYCCNT/SysClockFreq*1000);
}


/**
  * @brief  采用CPU的内部计数实现精确延时，32位计数器
  * @param  us : 延迟长度，单位1 us
  * @retval 无
  * @note   使用本函数前必须先调用CPU_TS_TmrInit函数使能计数器，
            或使能宏CPU_TS_INIT_IN_DELAY_FUNCTION
            最大延时值为8秒，即8*1000*1000
  */
void CPU_TS_Tmr_Delay_US(uint32_t us)
{
  uint32_t ticks;
  uint32_t told,tnow,tcnt=0;

  /* 在函数内部初始化时间戳寄存器， */  
#if (CPU_TS_INIT_IN_DELAY_FUNCTION)  
  /* 初始化时间戳并清零 */
  HAL_InitTick(5);
#endif
  
  ticks = us * (GET_CPU_ClkFreq() / 1000000);  /* 需要的节拍数 */      
  tcnt = 0;
  told = (uint32_t)CPU_TS_TmrRd();         /* 刚进入时的计数器值 */

  while(1)
  {
    tnow = (uint32_t)CPU_TS_TmrRd();  
    if(tnow != told)
    { 
        /* 32位计数器是递增计数器 */    
      if(tnow > told)
      {
        tcnt += tnow - told;  
      }
      /* 重新装载 */
      else 
      {
        tcnt += UINT32_MAX - told + tnow; 
      } 
      
      told = tnow;

      /*时间超过/等于要延迟的时间,则退出 */
      if(tcnt >= ticks)break;
    }  
  }
}

/*********************************************END OF FILE**********************/

volatile uint32_t *DWT_CONTROL = (uint32_t *) 0xE0001000;
volatile uint32_t *DWT_CYCCNT = (uint32_t *) 0xE0001004;
volatile uint32_t *DEMCR = (uint32_t *) 0xE000EDFC;
volatile uint32_t *LAR  = (uint32_t *) 0xE0001FB0;   // <-- added lock access register

*DEMCR = *DEMCR | 0x01000000;     // enable trace
*LAR = 0xC5ACCE55;                // <-- added unlock access to DWT (ITM, etc.)registers 
*DWT_CYCCNT = 0;                  // clear DWT cycle counter
*DWT_CONTROL = *DWT_CONTROL | 1;  // enable DWT cycle counter
//////////////////////////////////////////
//address of the register
volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004;     

//address of the register
volatile unsigned int *DWT_CONTROL  = (volatile unsigned int *)0xE0001000;     

//address of the register
volatile unsigned int *DWT_LAR      = (volatile unsigned int *)0xE0001FB0;     

//address of the register
volatile unsigned int *SCB_DEMCR    = (volatile unsigned int *)0xE000EDFC;
...

*DWT_LAR = 0xC5ACCE55; // unlock (CM7)
*SCB_DEMCR |= 0x01000000;
*DWT_CYCCNT = 0; // reset the counter
*DWT_CONTROL |= 1 ; // enable the counter
/////////////////////////////////////////////////