#include "stdint.h"
#include "arch.h"

const unsigned int SysClockFreq = 10000000; 

void dwt_init(void)
{
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;

  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void dwt_start(void)
{
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
 
void dwt_stop(void)
{
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; 
}


uint32_t dwt_get(void)
{        
  return ((uint32_t)DWT->CYCCNT);
}


uint32_t dwt_get_tick(void)
{        
  return ((uint32_t)DWT->CYCCNT/SysClockFreq*1000);
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