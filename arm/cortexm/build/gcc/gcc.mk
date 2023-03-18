
LDSCRIPT  := src/platform/$(board)/plat.ld
CFLAGS := $(ARCH_FLAGS)
CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g
toolchain = /project/gcc/cortex-m-gcc/arm/bin
PREFIX = $(toolchain)/arm-none-eabi-

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump