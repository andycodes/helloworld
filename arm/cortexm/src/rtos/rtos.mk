

CFLAGS += -Isrc/include \
		-Isrc/rtos/include

CSRC  += src/rtos/kernel/task.c \
		src/rtos/kernel/lib.c \
		src/rtos/kernel/event.c \
		src/rtos/kernel/sem.c \
		src/rtos/kernel/mailbox.c \
		src/rtos/kernel/memblock.c \
		src/rtos/kernel/timer.c \
		src/rtos/kernel/mutex.c \
		src/rtos/kernel/kalloc.c \
		src/rtos/kernel/flag_group.c