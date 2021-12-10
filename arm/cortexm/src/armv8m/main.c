#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "cmsis_gcc.h"
#include "core_cm55.h"

extern int testcase_task();

extern uint32_t _bss;
extern uint32_t _ebss;
extern void testcase(void);

static inline void clear_bss(void)
{
    uint8_t *start = (uint8_t *)_bss;
    while ((uint32_t)start < _ebss) {
        *start = 0;
        start++;
    }
}

// Secure SysTick handler
void SysTick_Handler (void) {
#if 0
  static unsigned int Milliseconds; 
  
  Milliseconds++ ;
  if (Milliseconds >= 1000) {
    Seconds++;
    Milliseconds = 0;
  }
  
  if (Timeout != 0) { 
    Timeout-- ;
    if (Timeout == 0) {
      LogIncident (IR_WDTEXP, 0, IS_SECURE);
      PerformReset ();
    }
  }
#endif
printk("hello SysTick_Handler ^-^^-^^-^^-^\n");
}

extern uint32_t SystemCoreClock;

void __PROGRAM_START(void)
{
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());
    //printk("hello %u \n", SystemCoreClock);
    SysTick_Config (5000000UL * 5 / 1000); 
    testcase_task();
    testcase();
}
