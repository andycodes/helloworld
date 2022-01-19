/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Mpu
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

/**
 * @defgroup mpu
 * @ingroup kernel
 */

#ifndef _ARCH_MPU_H
#define _ARCH_MPU_H

#include "los_base.h"
#include "los_task.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define MPU_DISABLE 0
#define MPU_ENABLE  0x7

/**
 * @ingroup mpu
 * MPU support number : MPU maximum number of region support(According to the cotex-m4 authority Guide)
 */
#define MPU_MAX_SUPPORT 8

/**
 * @ingroup mpu
 * Region size.
 */
#ifndef MPU_REGION_SIZE_32B
#define MPU_REGION_SIZE_32B   0x04
#endif

#ifndef MPU_REGION_SIZE_64B
#define MPU_REGION_SIZE_64B   0x05
#endif

#ifndef MPU_REGION_SIZE_128B
#define MPU_REGION_SIZE_128B  0x06
#endif

#ifndef MPU_REGION_SIZE_256B
#define MPU_REGION_SIZE_256B  0x07
#endif

#ifndef MPU_REGION_SIZE_512B
#define MPU_REGION_SIZE_512B  0x08
#endif

#ifndef MPU_REGION_SIZE_1KB
#define MPU_REGION_SIZE_1KB   0x09
#endif

#ifndef MPU_REGION_SIZE_2KB
#define MPU_REGION_SIZE_2KB   0x0A
#endif

#ifndef MPU_REGION_SIZE_4KB
#define MPU_REGION_SIZE_4KB   0x0B
#endif

#ifndef MPU_REGION_SIZE_8KB
#define MPU_REGION_SIZE_8KB   0x0C
#endif

#ifndef MPU_REGION_SIZE_16KB
#define MPU_REGION_SIZE_16KB  0x0D
#endif

#ifndef MPU_REGION_SIZE_32KB
#define MPU_REGION_SIZE_32KB  0x0E
#endif

#ifndef MPU_REGION_SIZE_64KB
#define MPU_REGION_SIZE_64KB  0x0F
#endif

#ifndef MPU_REGION_SIZE_128KB
#define MPU_REGION_SIZE_128KB 0x10
#endif

#ifndef MPU_REGION_SIZE_256KB
#define MPU_REGION_SIZE_256KB 0x11
#endif

#ifndef MPU_REGION_SIZE_512B
#define MPU_REGION_SIZE_512KB 0x12
#endif

#ifndef MPU_REGION_SIZE_1MB
#define MPU_REGION_SIZE_1MB   0x13
#endif

#ifndef MPU_REGION_SIZE_2MB
#define MPU_REGION_SIZE_2MB   0x14
#endif

#ifndef MPU_REGION_SIZE_4MB
#define MPU_REGION_SIZE_4MB   0x15
#endif

#ifndef MPU_REGION_SIZE_8MB
#define MPU_REGION_SIZE_8MB   0x16
#endif

#ifndef MPU_REGION_SIZE_16MB
#define MPU_REGION_SIZE_16MB  0x17
#endif

#ifndef MPU_REGION_SIZE_32MB
#define MPU_REGION_SIZE_32MB  0x18
#endif

#ifndef MPU_REGION_SIZE_64MB
#define MPU_REGION_SIZE_64MB  0x19
#endif

#ifndef MPU_REGION_SIZE_128MB
#define MPU_REGION_SIZE_128MB 0x1A
#endif

#ifndef MPU_REGION_SIZE_256MB
#define MPU_REGION_SIZE_256MB 0x1B
#endif

#ifndef MPU_REGION_SIZE_512MB
#define MPU_REGION_SIZE_512MB 0x1C
#endif

#ifndef MPU_REGION_SIZE_1GB
#define MPU_REGION_SIZE_1GB   0x1D
#endif

#ifndef MPU_REGION_SIZE_2GB
#define MPU_REGION_SIZE_2GB   0x1E
#endif

#ifndef MPU_REGION_SIZE_4GB
#define MPU_REGION_SIZE_4GB   0x1F
#endif

#ifndef MPU_REGION_ENABLE
#define MPU_REGION_ENABLE     0x01U
#endif

#ifndef MPU_REGION_DISABLE
#define MPU_REGION_DISABLE    0x00U
#endif

#ifndef MPU_INSTRUCTION_ACCESS_ENABLE
#define MPU_INSTRUCTION_ACCESS_ENABLE      0x00U
#endif

#ifndef MPU_INSTRUCTION_ACCESS_DISABLE
#define MPU_INSTRUCTION_ACCESS_DISABLE     0x01U
#endif

#ifndef MPU_ACCESS_SHAREABLE
#define MPU_ACCESS_SHAREABLE         0x01U
#endif

#ifndef MPU_ACCESS_NOT_SHAREABLE
#define MPU_ACCESS_NOT_SHAREABLE     0x00U
#endif

#ifndef MPU_ACCESS_CACHEABLE
#define MPU_ACCESS_CACHEABLE         0x01U
#endif

#ifndef MPU_ACCESS_NOT_CACHEABLE
#define MPU_ACCESS_NOT_CACHEABLE     0x00U
#endif

#ifndef MPU_ACCESS_BUFFERABLE
#define MPU_ACCESS_BUFFERABLE        0x01U
#endif

#ifndef MPU_ACCESS_NOT_BUFFERABLE
#define MPU_ACCESS_NOT_BUFFERABLE    0x00U
#endif

#ifndef MPU_HFNMIENA_ENABLE
#define MPU_HFNMIENA_ENABLE     0x01U
#endif

#ifndef MPU_HFNMIENA_DISABLE
#define MPU_HFNMIENA_DISABLE    0x00U
#endif

/**
 * @ingroup mpu
 * Access permission.
 */
#define MPU_DEFS_RASR_AP_NO_ACCESS       0 /* privilege level and user level are prohibited */
#define MPU_DEFS_RASR_AP_PRIV_RW         1 /* only privilege level can be read and write */
#define MPU_DEFS_RASR_AP_PRIV_RW_USER_RO 2 /* privilege level read and write, user level read only */
#define MPU_DEFS_RASR_AP_FULL_ACCESS     3 /* privilege level and user level can be read and write */
#define MPU_DEFS_RASR_AP_PRIV_RO         5 /* privilege level read only, user level is prohibited */
#define MPU_DEFS_RASR_AP_RO              6 /* privilege level and user level read only */

/**
 * @ingroup mpu
 * region info
 * uwBaseAddress must be in the range of RAM
 * uwAccessPermission and uwRegionSize are not arbitrary input, selected by the definition of the macro
 */
typedef struct {
    UINT8 number;             /* number of MPU register to be checked */
    UINT32 baseAddress;       /* set the base address of the protected region,
                                 the base address must be in the range of RAM */
    UINT32 accessPermission;  /* privilege level and user level access permission */
    BOOL sharable;            /* whether to share */
    BOOL cachable;            /* whether cache */
    BOOL buffable;            /* whether buffer */
    UINT32 regionSize;        /* region size */
    BOOL hfnmiena;            /* Whether in the NMI and hard fault service routine
                                 is not mandatory in addition to MPU */
    BOOL xn;                  /* To indicate whether instructions are fetchable in this region,
                                 0 fetchable; 1: otherwise */
} MPU_REGION_INFO;

/**
 * @ingroup mpu
 * MPU error code: The pointer to an input parameter is NULL.
 *
 * Value: 0x02001200
 *
 * Solution: Check whether the pointer to the input parameter is usable.
 */
#define LOS_ERRNO_MPU_PTR_NULL LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x00)

/**
 * @ingroup mpu
 * MPU error code: The base address is not aligned to the boundary of the region capacity.
 *
 * Value: 0x02001201
 *
 * Solution: Check base address.
 */
#define LOS_ERRNO_MPU_INVALID_BASE_ADDRESS LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x01)

/**
 * @ingroup mpu
 * MPU error code: Capacity less than 32 bytes.
 *
 * Value: 0x02001202
 *
 * Solution: Guaranteed that the capacity is greater than or equal to 32 bytes.
 */
#define LOS_ERRNO_MPU_INVALID_CAPACITY LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x02)

/**
 * @ingroup mpu
 * MPU error code: Chip is not configured MPU.
 *
 * Value: 0x02001203
 *
 * Solution: Make sure the chip is configured with MPU.
 */
#define LOS_ERRNO_MPU_NOT_CONFIGURED LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x03)

/**
 * @ingroup mpu
 * MPU error code: Invalid number.
 *
 * Value: 0x02001204
 *
 * Solution: Enter a valid number.
 */
#define LOS_ERRNO_MPU_INVALID_NUMBER LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x04)

/**
 * @ingroup mpu
 * MPU error code: Region has already been enabled.
 *
 * Value: 0x02001205
 *
 * Solution: If you want to re enable the region, please first in addition to the region.
 */
#define LOS_ERRNO_MPU_REGION_IS_ENABLED LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x05)

/**
 * @ingroup mpu
 * MPU error code: Region has already been disabled.
 *
 * Value: 0x02001206
 *
 * Solution: If you want to re enable the region, please first in addition to the region.
 */
#define LOS_ERRNO_MPU_REGION_IS_DISABLED LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x06)

/**
 * @ingroup mpu
 * MPU error code: Invalid access.
 *
 * Value: 0x02001207
 *
 * Solution: Checking whether the access is correct.
 */
#define LOS_ERRNO_MPU_REGION_INVALID_ACCESS LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x07)

/**
 * @ingroup mpu
 * MPU error code: Base address is not in RAM.
 *
 * Value: 0x02001208
 *
 * Solution: Checking base address
 */
#define LOS_ERRNO_MPU_BASE_ADDRESS_NOT_IN_RAM LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x08)

/**
 * @ingroup mpu
 * MPU error code: According to the current base address, the size of the application is too big.
 *
 * Value: 0x02001209
 *
 * Solution: baseAddress + regionSize must not exceed RAM Max address
 */
#define LOS_ERRNO_MPU_REGION_SIZE_IS_TOO_BIG LOS_ERRNO_OS_ERROR(LOS_MOD_MPU, 0x09)

/**
 * @ingroup mpu
 * @brief Obtain the set protection region.
 *
 * @par Description:
 * This API is used to set protection region.
 * @attention
 * <ul>
 * <li>the base address must be in the range of RAM.</li>
 * </ul>
 *
 * @param  mpuInfo     [IN] MPU_REGION_INFO. Set the related configuration information for the protected area
 *
 * @retval #LOS_ERRNO_MPU_TASK_PTR_NULL          0x02001200: The pointer to an input parameter is NULL.
 * @retval #LOS_ERRNO_MPU_INVALID_BASE_ADDRESS   0x02001201: The base address is not aligned to the boundary of the
 *                                                           region capacity.
 * @retval #LOS_ERRNO_MPU_INVALID_CAPACITY       0x02001202: Capacity less than 32 bytes.
 * @retval #LOS_ERRNO_MPU_NOT_CONFIGURED         0x02001203: Chip is not configured MPU.
 * @retval #LOS_ERRNO_MPU_INVALID_NUMBER         0x02001204: Invalid number.
 * @retval #LOS_ERRNO_MPU_REGION_IS_ENABLED      0x02001205: Region has already been enabled.
 * @retval #LOS_ERRNO_MPU_REGION_IS_DISABLED     0x02001206: Region has already been disabled.
 * @par Dependency:
 * <ul><li>mpu.h: the header file that contains the API declaration.</li></ul>
 * @since Huawei LiteOS V100R001C00
 */
extern UINT32 ArchProtectionRegionSet(MPU_REGION_INFO *mpuInfo);

/**
 * @ingroup mpu
 * @brief Obtain the set protection region.
 *
 * @par Description:
 * This API is used to set protection region.
 * @attention
 * <ul>
 * <li>.</li>
 * </ul>
 *
 * @param  number     [IN] UINT8.which region to be selected.
 *
 * @retval #LOS_ERRNO_MPU_INVALID_NUMBER         0x02001204: Invalid number.
 * @retval #LOS_ERRNO_MPU_REGION_IS_DISABLED     0x02001206: Region has already been disabled.
 * @par Dependency:
 * <ul><li>mpu.h: the header file that contains the API declaration.</li></ul>
 * @since Huawei LiteOS V100R001C00
 */
extern UINT32 ArchRegionDisable(UINT8 number);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _ARCH_MPU_H */
