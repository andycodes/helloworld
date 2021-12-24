#include "cmsdk_uart.h"
#include "system_ARMCM55.h"
#include "core_cm55.h"
#include "os_stdio.h"
#include <stdint.h>

uint32_t Seconds = 0;

void SysTick_Handler (void) {
  static unsigned int Milliseconds; 
  
  Milliseconds++ ;
  if (Milliseconds >= 1000) {
    Seconds++;
    Milliseconds = 0;
  }

  printk("SysTick_Handler \n");
}

void test_systick(void)
{
    //printk("SystemCoreClock %u \n", SystemCoreClock);
    SysTick_Config (SystemCoreClock / 1000);    /* 1 ms interval */
}