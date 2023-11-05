#ifndef __OS_H__
#define __OS_H__

#include "riscv.h"
#include "lib.h"
#include "timer.h"
#include "task.h"

extern void user_init();
extern void os_loop(void);
extern void os_kernel();
extern int  os_main(void);

#endif
