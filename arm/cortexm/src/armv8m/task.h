/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Task Operations HeadFile
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
 * @defgroup los_task
 * @ingroup kernel
 */

#ifndef _ARCH_TASK_H
#define _ARCH_TASK_H

//#include "los_typedef.h"
#include "cpu.h"
#include "regs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#if ((defined(__CC_ARM) && defined(__TARGET_FPU_VFP))                         \
     || (defined(__CLANG_ARM) && defined(__VFP_FP__) && !defined(__SOFTFP__)) \
     || (defined(__ICCARM__) && defined(__ARMVFP__ ))                          \
     || (defined(__GNUC__) && defined(__VFP_FP__) && !defined(__SOFTFP__)))
#define FPU_USED   1
#else
#define FPU_USED   0
#endif

#define LOSCFG_STACK_POINT_ALIGN_SIZE (sizeof(UINTPTR) * 2)

extern void *g_runTask;
extern void *g_oldTask;

static  inline void *ArchCurrTaskGet(void)
{
    return g_runTask;
}

static  inline void ArchCurrTaskSet(void *val)
{
    g_runTask = val;
}

typedef struct tagContext {
    unsigned int R4;
    unsigned int R5;
    unsigned int R6;
    unsigned int R7;
    unsigned int R8;
    unsigned int R9;
    unsigned int R10;
    unsigned int R11;
    unsigned int PriMask;
#if FPU_USED
    unsigned int excReturn;
#endif
    unsigned int R0;
    unsigned int R1;
    unsigned int R2;
    unsigned int R3;
    unsigned int R12;
    unsigned int LR;
    unsigned int PC;
    unsigned int xPSR;
} TaskContext;

/*
 * Description : task stack initialization
 * Input       : taskId    -- task ID
 *               stackSize -- task stack size
 *               topStack  -- stack top of task (low address)
 * Return      : pointer to the task context
 */
extern void *OsTaskStackInit(unsigned int taskId, unsigned int stackSize, void *topStack);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _ARCH_TASK_H */
