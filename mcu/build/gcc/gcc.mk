CFLAGS ?= -D_FORTIFY_SOURCE=2 -O2
#CFLAGS += -fstack-protector-strong
CFLAGS += -fno-stack-protector
CFLAGS += -Wstack-usage=2048  -Wframe-larger-than=512

ifeq ($(board),riscv64)
	CFLAGS += $(ARCH_FLAGS)
	include build/gcc/$(board).mk
else ifeq ($(board),riscv32)
	CFLAGS += $(ARCH_FLAGS)
	include build/gcc/$(board).mk
else ifeq ($(board),a710)
	CFLAGS += $(ARCH_FLAGS)
	include build/$(CC)/cortex-a710.mk
else
	include build/$(CC)/$(CPU_TYPE).mk
	CFLAGS += $(ARCH_FLAGS)
	include build/$(CC)/cortex_m.mk
endif