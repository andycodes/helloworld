

/**
 * @defgroup los_hw Hardware
 * @ingroup kernel
 */

#ifndef _ARCH_CPU_H
#define _ARCH_CPU_H

#include <stdint.h>
#include "type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define CPUID_BASE              0xE000ED00    /* Main ID Register */
#define ARM_SYSREG_READ(addr)   (*(volatile unsigned *)(uintptr_t)(addr))

typedef struct {
    const uint32_t  partNo;
    const char *cpuName;
} CpuVendor;

extern const char *ArchCpuInfo(VOID);

static inline uint32_t  OsMainIDGet(VOID)
{
    return ARM_SYSREG_READ(CPUID_BASE);
}

static inline uint32_t  ArchCurrCpuid(void)
{
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _ARCH_CPU_H */
