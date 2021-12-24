#ifndef __MODULE_H__
#define __MODULE_H__

typedef int (*initcall_t)(void);

#define __define_initcall(fn, id) \
static initcall_t __initcall_##fn##id \
__attribute__((used, __section__(".initcall" #id ".init"))) = fn;

#define device_initcall(fn)		__define_initcall(fn, 6)



#endif /*__MODULE_H__*/
