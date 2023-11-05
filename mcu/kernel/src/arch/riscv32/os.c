#include "os.h"

extern void trap_init(void);

void panic(char *s)
{
	lib_puts(s);
	for (;;)
	{
	}
}

void os_kernel()
{
	task_os();
}

void os_start()
{
	uart_init();
	lib_puts("OS start\n");
	user_init();
	trap_init();
	plic_init();
	timer_init(); // start timer interrupt ...
}

int os_main(void)
{
	os_start();

	int current_task = 0;
	while (1)
	{
		lib_puts("OS: Activate next task\n");
		task_go(current_task);
		lib_puts("OS: Back to OS\n");
		current_task = (current_task + 1) % taskTop; // Round Robin Scheduling
		lib_puts("\n");
	}
	return 0;
}
