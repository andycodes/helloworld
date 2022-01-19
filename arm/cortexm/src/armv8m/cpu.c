#include "cpu.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* support cpu vendors */
CpuVendor g_cpuTable[] = {
    /* armv7-m */
    { 0xC20, "Cortex-M0" },
    { 0xC21, "Cortex-M1" },
    { 0xC23, "Cortex-M3" },
    { 0xC24, "Cortex-M4" },
    { 0xC27, "Cortex-M7" },
    { 0xD21, "Cortex-M33" },
};

#define LOSCFG_KERNEL_CORE_NUM 1

/* logical cpu mapping */
uint64_t  g_cpuMap[LOSCFG_KERNEL_CORE_NUM] = {
    [0 ... LOSCFG_KERNEL_CORE_NUM - 1] = (uint64_t )(-1)
};

const char *ArchCpuInfo(VOID)
{
    uint32_t  midr = OsMainIDGet();
    /* [15:4] is the primary part number */
    uint32_t  partNo = (midr & 0xFFF0) >> 0x4;

    for (uint32_t  i = 0; i < (sizeof(g_cpuTable) / sizeof(CpuVendor)); i++) {
        if (partNo == g_cpuTable[i].partNo) {
            return g_cpuTable[i].cpuName;
        }
    }

    return "unknown";
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */