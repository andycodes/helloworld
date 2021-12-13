#include "cmsdk_uart.h"
#include "testcase.h"
#include "os_stdio.h"
#include <stdint.h>


typedef int (*initcall_t)(void);

#define __define_initcall(fn, id) \
static initcall_t __initcall_##fn##id __used \
__attribute__((__section__(".initcall" #id ".init"))) = fn;

#define device_initcall(fn)		__define_initcall(fn, 6)


static int  its_pmsi_init(void)
{
    printk("fansaihua init fun\n");
    return 0;
}

device_initcall(its_pmsi_init);


extern unsigned long _init_fn_start;
extern unsigned long _init_fn_end;

void rt_components_board_init(void)
{
    volatile const initcall_t *fn_ptr;

    for (fn_ptr = &_init_fn_start; fn_ptr < &_init_fn_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
}


apError test_init(void)
{
    rt_components_board_init();
     return apERR_NONE;
}