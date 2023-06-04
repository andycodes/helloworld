
LDSCRIPT  := src/platform/$(board)/plat.ld
CFLAGS := $(ARCH_FLAGS)
CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g -Wl,--no-warn-rwx-segments
toolchain = /project/gcc/armgcc1202mpacbti_rel1/bin
PREFIX = $(toolchain)/arm-none-eabi-

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
READELF = readelf