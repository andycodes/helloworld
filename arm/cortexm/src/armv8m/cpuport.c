/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-10-21     Bernard      the first version.
 * 2011-10-27     aozima       update for cortex-M4 FPU.
 * 2011-12-31     aozima       fixed stack align issues.
 * 2012-01-01     aozima       support context switch load/store FPU register.
 * 2012-12-11     lgnq         fixed the coding style.
 * 2012-12-23     aozima       stack addr align to 8byte.
 * 2012-12-29     Bernard      Add exception hook.
 * 2013-06-23     aozima       support lazy stack optimized.
 * 2018-07-24     aozima       enhancement hard fault exception handler.
 * 2019-07-03     yangjie      add __rt_ffs() for armclang.
 */

#include <stdint.h>
#include <stdio.h>
#include "os_stdio.h"

/* exception and interrupt handler table */
uint32_t  rt_interrupt_from_thread;
uint32_t  rt_interrupt_to_thread;
uint32_t  rt_thread_switch_interrupt_flag;

/* exception hook */
static int (*rt_exception_hook)(void *context) = NULL;

struct exception_stack_frame
{
    uint32_t  r0;
    uint32_t  r1;
    uint32_t  r2;
    uint32_t  r3;
    uint32_t  r12;
    uint32_t  lr;
    uint32_t  pc;
    uint32_t  psr;
};

struct stack_frame
{
    uint32_t  tz;
    uint32_t  lr;
    uint32_t  psplim;
    uint32_t  control;

    /* r4 ~ r11 register */
    uint32_t  r4;
    uint32_t  r5;
    uint32_t  r6;
    uint32_t  r7;
    uint32_t  r8;
    uint32_t  r9;
    uint32_t  r10;
    uint32_t  r11;

    struct exception_stack_frame exception_stack_frame;
};

struct exception_stack_frame_fpu
{
    uint32_t  r0;
    uint32_t  r1;
    uint32_t  r2;
    uint32_t  r3;
    uint32_t  r12;
    uint32_t  lr;
    uint32_t  pc;
    uint32_t  psr;

#if USE_FPU
    /* FPU register */
    uint32_t  S0;
    uint32_t  S1;
    uint32_t  S2;
    uint32_t  S3;
    uint32_t  S4;
    uint32_t  S5;
    uint32_t  S6;
    uint32_t  S7;
    uint32_t  S8;
    uint32_t  S9;
    uint32_t  S10;
    uint32_t  S11;
    uint32_t  S12;
    uint32_t  S13;
    uint32_t  S14;
    uint32_t  S15;
    uint32_t  FPSCR;
    uint32_t  NO_NAME;
#endif
};

struct stack_frame_fpu
{
    uint32_t  flag;

    /* r4 ~ r11 register */
    uint32_t  r4;
    uint32_t  r5;
    uint32_t  r6;
    uint32_t  r7;
    uint32_t  r8;
    uint32_t  r9;
    uint32_t  r10;
    uint32_t  r11;

#if USE_FPU
    /* FPU register s16 ~ s31 */
    uint32_t  s16;
    uint32_t  s17;
    uint32_t  s18;
    uint32_t  s19;
    uint32_t  s20;
    uint32_t  s21;
    uint32_t  s22;
    uint32_t  s23;
    uint32_t  s24;
    uint32_t  s25;
    uint32_t  s26;
    uint32_t  s27;
    uint32_t  s28;
    uint32_t  s29;
    uint32_t  s30;
    uint32_t  s31;
#endif

    struct exception_stack_frame_fpu exception_stack_frame;
};

uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             uint8_t *stack_addr,
                             void       *texit)
{
    struct stack_frame *stack_frame;
    uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(uint32_t );
    stk  = (uint8_t *)RT_ALIGN_DOWN((uint32_t )stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(uint32_t ); i ++)
    {
        ((uint32_t  *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = (unsigned long)texit;     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    stack_frame->tz = 0x00;
    stack_frame->lr = 0xFFFFFFBC;
    stack_frame->psplim = 0x00;
    stack_frame->control = 0x00;

    /* return task's current stack address */
    return stk;
}

/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(int (*exception_handle)(void *context))
{
    rt_exception_hook = exception_handle;
}

#define SCB_CFSR        (*(volatile const unsigned *)0xE000ED28) /* Configurable Fault Status Register */
#define SCB_HFSR        (*(volatile const unsigned *)0xE000ED2C) /* HardFault Status Register */
#define SCB_MMAR        (*(volatile const unsigned *)0xE000ED34) /* MemManage Fault Address register */
#define SCB_BFAR        (*(volatile const unsigned *)0xE000ED38) /* Bus Fault Address Register */
#define SCB_AIRCR       (*(volatile unsigned long *)0xE000ED0C)  /* Reset control Address Register */
#define SCB_RESET_VALUE 0x05FA0004                               /* Reset value, write to SCB_AIRCR can reset cpu */

#define SCB_CFSR_MFSR   (*(volatile const unsigned char*)0xE000ED28)  /* Memory-management Fault Status Register */
#define SCB_CFSR_BFSR   (*(volatile const unsigned char*)0xE000ED29)  /* Bus Fault Status Register */
#define SCB_CFSR_UFSR   (*(volatile const unsigned short*)0xE000ED2A) /* Usage Fault Status Register */


static void usage_fault_track(void)
{
    printk("usage fault:\n");
    printk("SCB_CFSR_UFSR:0x%02X ", SCB_CFSR_UFSR);

    if(SCB_CFSR_UFSR & (1<<0))
    {
        /* [0]:UNDEFINSTR */
        printk("UNDEFINSTR ");
    }

    if(SCB_CFSR_UFSR & (1<<1))
    {
        /* [1]:INVSTATE */
        printk("INVSTATE ");
    }

    if(SCB_CFSR_UFSR & (1<<2))
    {
        /* [2]:INVPC */
        printk("INVPC ");
    }

    if(SCB_CFSR_UFSR & (1<<3))
    {
        /* [3]:NOCP */
        printk("NOCP ");
    }

    if(SCB_CFSR_UFSR & (1<<8))
    {
        /* [8]:UNALIGNED */
        printk("UNALIGNED ");
    }

    if(SCB_CFSR_UFSR & (1<<9))
    {
        /* [9]:DIVBYZERO */
        printk("DIVBYZERO ");
    }

    printk("\n");
}

static void bus_fault_track(void)
{
    printk("bus fault:\n");
    printk("SCB_CFSR_BFSR:0x%02X ", SCB_CFSR_BFSR);

    if(SCB_CFSR_BFSR & (1<<0))
    {
        /* [0]:IBUSERR */
        printk("IBUSERR ");
    }

    if(SCB_CFSR_BFSR & (1<<1))
    {
        /* [1]:PRECISERR */
        printk("PRECISERR ");
    }

    if(SCB_CFSR_BFSR & (1<<2))
    {
        /* [2]:IMPRECISERR */
        printk("IMPRECISERR ");
    }

    if(SCB_CFSR_BFSR & (1<<3))
    {
        /* [3]:UNSTKERR */
        printk("UNSTKERR ");
    }

    if(SCB_CFSR_BFSR & (1<<4))
    {
        /* [4]:STKERR */
        printk("STKERR ");
    }

    if(SCB_CFSR_BFSR & (1<<7))
    {
        printk("SCB->BFAR:%08X\n", SCB_BFAR);
    }
    else
    {
        printk("\n");
    }
}

static void mem_manage_fault_track(void)
{
    printk("mem manage fault:\n");
    printk("SCB_CFSR_MFSR:0x%02X ", SCB_CFSR_MFSR);

    if(SCB_CFSR_MFSR & (1<<0))
    {
        /* [0]:IACCVIOL */
        printk("IACCVIOL ");
    }

    if(SCB_CFSR_MFSR & (1<<1))
    {
        /* [1]:DACCVIOL */
        printk("DACCVIOL ");
    }

    if(SCB_CFSR_MFSR & (1<<3))
    {
        /* [3]:MUNSTKERR */
        printk("MUNSTKERR ");
    }

    if(SCB_CFSR_MFSR & (1<<4))
    {
        /* [4]:MSTKERR */
        printk("MSTKERR ");
    }

    if(SCB_CFSR_MFSR & (1<<7))
    {
        /* [7]:MMARVALID */
        printk("SCB->MMAR:%08X\n", SCB_MMAR);
    }
    else
    {
        printk("\n");
    }
}

static void hard_fault_track(void)
{
    if(SCB_HFSR & (1UL<<1))
    {
        /* [1]:VECTBL, Indicates hard fault is caused by failed vector fetch. */
        printk("failed vector fetch\n");
    }

    if(SCB_HFSR & (1UL<<30))
    {
        /* [30]:FORCED, Indicates hard fault is taken because of bus fault,
                        memory management fault, or usage fault. */
        if(SCB_CFSR_BFSR)
        {
            bus_fault_track();
        }

        if(SCB_CFSR_MFSR)
        {
            mem_manage_fault_track();
        }

        if(SCB_CFSR_UFSR)
        {
            usage_fault_track();
        }
    }

    if(SCB_HFSR & (1UL<<31))
    {
        /* [31]:DEBUGEVT, Indicates hard fault is triggered by debug event. */
        printk("debug event\n");
    }
}

struct exception_info
{
    uint32_t  exc_return;
    struct stack_frame stack_frame;
};

void rt_hw_hard_fault_exception(struct exception_info *exception_info)
{
    extern long list_thread(void);
    struct exception_stack_frame *exception_stack = &exception_info->stack_frame.exception_stack_frame;
    struct stack_frame *context = &exception_info->stack_frame;

    if (rt_exception_hook != NULL)
    {
        int result;

        result = rt_exception_hook(exception_stack);
        if (result == EOK) return;
    }

    printk("psr: 0x%08x\n", context->exception_stack_frame.psr);

    printk("r00: 0x%08x\n", context->exception_stack_frame.r0);
    printk("r01: 0x%08x\n", context->exception_stack_frame.r1);
    printk("r02: 0x%08x\n", context->exception_stack_frame.r2);
    printk("r03: 0x%08x\n", context->exception_stack_frame.r3);
    printk("r04: 0x%08x\n", context->r4);
    printk("r05: 0x%08x\n", context->r5);
    printk("r06: 0x%08x\n", context->r6);
    printk("r07: 0x%08x\n", context->r7);
    printk("r08: 0x%08x\n", context->r8);
    printk("r09: 0x%08x\n", context->r9);
    printk("r10: 0x%08x\n", context->r10);
    printk("r11: 0x%08x\n", context->r11);
    printk("r12: 0x%08x\n", context->exception_stack_frame.r12);
    printk(" lr: 0x%08x\n", context->exception_stack_frame.lr);
    printk(" pc: 0x%08x\n", context->exception_stack_frame.pc);

    if (exception_info->exc_return & (1 << 2))
    {
        printk("hard fault on thread: \r\n\r\n");
        //printk("hard fault on thread: %s\r\n\r\n", rt_thread_self()->name);

#ifdef RT_USING_FINSH
        list_thread();
#endif
    }
    else
    {
        printk("hard fault on handler\r\n\r\n");
    }

    if ( (exception_info->exc_return & 0x10) == 0)
    {
        printk("FPU active!\r\n");
    }

    hard_fault_track();
    while (1);
}

/**
 * shutdown CPU
 */
RT_WEAK void rt_hw_cpu_shutdown(void)
{
    printk("shutdown...\n");

    RT_ASSERT(0);
}

/**
 * reset CPU
 */
RT_WEAK void rt_hw_cpu_reset(void)
{
    SCB_AIRCR = SCB_RESET_VALUE;
}

