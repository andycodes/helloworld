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