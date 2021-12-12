#include "cmsdk_uart.h"
#include "testcase.h"
#include "os_stdio.h"
#include <stdint.h>

#if 0
typedef int (*initcall_t)(void);

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

/* Format: <counter>_<line>_<fn> */
#define __initcall_id(fn)					\
	__PASTE(__COUNTER__,					\
	__PASTE(_,						\
	__PASTE(__LINE__,					\
	__PASTE(_, fn))))

/* Format: __<prefix>__<iid><id> */
#define __initcall_name(prefix, __iid, id)			\
	__PASTE(__,						\
	__PASTE(prefix,						\
	__PASTE(__,						\
	__PASTE(__iid, id))))

#define ____define_initcall(fn, __name, __sec)	\
	static initcall_t __name __used __attribute__((__section__(__sec))) = fn;

#define __initcall_section(__sec)	#__sec".init.fn"

#define __unique_initcall(fn, id, __sec, __iid)			\
	____define_initcall(fn,					\
		__initcall_name(initcall, __iid, id),		\
		__initcall_section(__sec))

#define ___define_initcall(fn, id, __sec)	__unique_initcall(fn, id, __sec, __initcall_id(fn))

#define __define_initcall(fn, id) ___define_initcall(fn, id, id)

#define early_initcall(fn)	__define_initcall(fn, early)
#endif

#if 1
typedef int (*initcall_t)(void);

#define __define_initcall(fn, id) \
static initcall_t __initcall_##fn##id __used \
__attribute__((__section__(".initcall" #id ".init"))) = fn;

#define device_initcall(fn)		__define_initcall(fn, 6)
#endif

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