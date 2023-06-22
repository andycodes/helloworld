#ifndef __ARCH_H__
#define __ARCH_H__

#include <stdint.h>
#include <ARMCM55.h>
#include <core_cm55.h>

//#define SystemCoreClock     (12000000UL)
#define NVIC_PENDSV_PRI     0x000000FF


#define MEM32(addr)         *(volatile uint32_t *)(addr)
#define MEM8(addr)          *(volatile uint8_t *)(addr)

extern uint32_t get_psp(void);
extern void set_psp(uint32_t psp);
extern uint32_t get_msp(void);
extern uint32_t get_control_reg(void);
extern uint32_t get_primask(void);
extern void set_primask(uint32_t primask);
extern void disable_irq(void);
extern void enable_irq(void);

extern void init_systick(uint32_t ms);
extern void pendsv_handler(void);
#endif /*__ARCH_H__*/
