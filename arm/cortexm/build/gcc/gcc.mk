
LDSCRIPT  := src/platform/$(board)/plat.ld
CFLAGS := $(ARCH_FLAGS)


ifeq ($(board),riscv)
	CC = $(PREFIX)gcc
	AS = $(PREFIX)gas
	LD = $(PREFIX)ld
	COPY = $(PREFIX)objcopy
	DUMP = $(PREFIX)objdump
	SIZE = $(PREFIX)size
	NM = $(PREFIX)nm
	READELF = readelf

	CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
	CFLAGS += -MD
	CFLAGS += -mcmodel=medany
#freestanding environment is one in which the standard library may not exist, 
#and program startup may not necessarily be at "main". 
#The option -ffreestanding directs the compiler to not assume 
#that standard functions have their usual definition.
	CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
	CFLAGS += -I.
	CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

	# Disable PIE when possible (for Ubuntu 16.10 toolchain)
	ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
	CFLAGS += -fno-pie -no-pie
	endif
	ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
	CFLAGS += -fno-pie -nopie
	endif

	LDFLAGS = -z max-page-size=4096
	PREFIX = riscv64-unknown-elf-
else
	CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g
	toolchain = /project/gcc/arm-gnu-toolchain-1203/bin
	PREFIX = $(toolchain)/arm-none-eabi-

	CC = $(PREFIX)gcc
	LD = $(PREFIX)ld
	COPY = $(PREFIX)objcopy
	DUMP = $(PREFIX)objdump
	SIZE = $(PREFIX)size
	NM = $(PREFIX)nm
	READELF = readelf
endif

