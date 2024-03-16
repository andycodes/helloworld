CFLAGS ?= -D_FORTIFY_SOURCE=2 -O2
#-fstack-protector-all
#-fno-stack-protector

ifeq ($(board),riscv64)
	CFLAGS += $(ARCH_FLAGS)
	include build/gcc/$(board).mk
else ifeq ($(board),riscv32)
	CFLAGS += $(ARCH_FLAGS)
	include build/gcc/$(board).mk
else
	include build/$(CC)/$(CPU_TYPE).mk
	CFLAGS += $(ARCH_FLAGS)
	include build/$(CC)/cortex.mk
endif