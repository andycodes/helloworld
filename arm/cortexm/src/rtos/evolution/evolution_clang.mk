

CFLAGS += -Isrc/include \
		-Isrc/rtos/evolution/include

CSRC  += src/rtos/evolution/kernel/task.c \
		src/rtos/evolution/kernel/lib.c \
		src/rtos/evolution/kernel/event.c \
		src/rtos/evolution/kernel/sem.c \
		src/rtos/evolution/kernel/mailbox.c \
		src/rtos/evolution/kernel/memblock.c \
		src/rtos/evolution/kernel/timer.c \
		src/rtos/evolution/kernel/mutex.c \
		src/rtos/evolution/kernel/flag_group.c