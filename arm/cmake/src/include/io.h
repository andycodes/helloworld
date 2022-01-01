#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

static inline void __raw_writel(uint32_t  value, volatile void *addr)
{
	*(volatile uint32_t  *)addr = value;
}

static inline void writel(uint32_t  value, volatile void *addr)
{
	__raw_writel(value, addr);
	do { } while (0);
}

#endif /*__IO_H__*/