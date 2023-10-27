
LDSCRIPT  := src/platform/$(board)/plat.ld
CFLAGS := $(ARCH_FLAGS)
CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g

ifeq ($(board),riscv)
	PREFIX = riscv64-unknown-elf-
else
	toolchain = /project/gcc/arm-gnu-toolchain-1203/bin
	PREFIX = $(toolchain)/arm-none-eabi-
endif

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
SIZE = $(PREFIX)size
NM = $(PREFIX)nm
READELF = readelf