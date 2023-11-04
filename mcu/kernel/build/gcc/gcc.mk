ifeq ($(board),riscv64)
	CFLAGS := $(ARCH_FLAGS)
	include build/gcc/riscv.mk
else ifeq ($(board),riscv32)
	CFLAGS := $(ARCH_FLAGS)
	include build/gcc/riscv.mk
else
	include build/$(CC)/$(CPU_TYPE).mk
	CFLAGS := $(ARCH_FLAGS)
	include build/$(CC)/cortex.mk
endif