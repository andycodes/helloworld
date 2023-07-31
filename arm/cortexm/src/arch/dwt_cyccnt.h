#ifndef _DWT_CYCCNT_H_
#define _DWT_CYCCNT_H_

#ifndef _DWTDELAY_H_
 
#define _DWTDELAY_H_
 
// 根据MCU做修改
#define MY_MCU_SYSCLK           (72000000)
 
 
 
void DWT_INIT(int sys_clk);
 
// 微秒延时
void DWT_DELAY_uS(int uSec);
 
#define DWT_DELAY_mS(mSec)    DWT_DELAY_uS( mSec*1000 )
 
#endif // _DWTDELAY_H_

#endif /*_DWT_CYCCNT_H_*/
