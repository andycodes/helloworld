	CFLAGS +=  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g
	PREFIX = aarch64-none-elf-
	
	CC = $(PREFIX)gcc
	LD = $(PREFIX)ld
	COPY = $(PREFIX)objcopy
	DUMP = $(PREFIX)objdump
	SIZE = $(PREFIX)size
	NM = $(PREFIX)nm
	READELF = readelf
