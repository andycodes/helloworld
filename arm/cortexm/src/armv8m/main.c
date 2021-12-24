#include <stdint.h>
#include <stdbool.h>
#include "os_stdio.h"
#include "uart.h"
#include "board.h"
#include "lib.h"
#include "module.h"

#include "system_ARMCM55.h"
#include "core_cm55.h"

typedef unsigned long                   rt_ubase_t;     /**< Nbit unsigned CPU related data type */

rt_ubase_t rt_trustzone_current_context;

void rt_trustzone_context_store(unsigned long context)
{

}

int rt_secure_svc_handle(int svc_id, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2)
{

}

void rt_trustzone_context_load(rt_ubase_t context)
{}

void SVC1_Handler(void)
{
    printk("hello %s ^-^^-^^-^^-^\n", __func__);
}

extern void rt_hw_show_memory(uint32_t addr, uint32_t size);


void __PROGRAM_START(void)
{
    clear_bss();
    board_init();
    printk("hello %s ^-^^-^^-^^-^\n", board_info());

 //int tzcall(int id, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2);

  //  rt_hw_show_memory(0x0, 128);

   // PendSV_set();

  //  svcall();

    module_init();
}



void disable_irq(void)
{}

void enable_irq(void)
{}

uint32_t get_primask(void)
{}


void set_primask(uint32_t primask)
{}

