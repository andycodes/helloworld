
LDSCRIPT  := src/platform/$(board)/plat.ld
CFLAGS := $(ARCH_FLAGS)
CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g
toolchain = /project/gcc/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/bin
PREFIX = $(toolchain)/arm-none-eabi-

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump