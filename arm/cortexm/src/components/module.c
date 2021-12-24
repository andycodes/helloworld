#include "module.h"


extern unsigned long _init_fn_start;
extern unsigned long _init_fn_end;

void module_init(void)
{
    volatile const initcall_t *fn_ptr;

    for (fn_ptr = &_init_fn_start; fn_ptr < &_init_fn_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
}
