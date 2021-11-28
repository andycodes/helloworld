
$(info "!!!!THE CUR BOARD is $(board)")

#   make board=mps2-an505
# 	make board=mps2-an505 qemu

CPU_TYPE = cortex-m55
MEM_SIZE = 2048
ifeq ($(board),mps2-an505)
	CPU_TYPE = cortex-m33
	MEM_SIZE = 16
endif

IMAGE := kernel.elf

PWD_TOOLCHAIN = /project/gcc/gcc-arm-none-eabi-10.3-2021.10/bin/
CROSS_COMPILE = $(PWD_TOOLCHAIN)/arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
GDB = $(CROSS_COMPILE)gdb
OBJDUMP = $(CROSS_COMPILE)objdump
READELF = $(CROSS_COMPILE)readelf

CFLAGS = -mcpu=$(CPU_TYPE) -g -nostdlib -nostartfiles -ffreestanding

all: $(IMAGE)

ifeq ($(board),mps2-an505)
OBJS = main.o os_stdio.o cmsdk_uart.o
else
OBJS = main.o os_stdio.o
endif

boot.o: boot.s
	$(CC) -mcpu=$(CPU_TYPE) -g -c boot.s -o boot.o

$(IMAGE): kernel.ld boot.o $(OBJS)
	$(LD) boot.o $(OBJS) -T kernel.ld -o $(IMAGE)
	$(OBJDUMP) -d $(IMAGE) > kernel.list
	$(OBJDUMP) -t $(IMAGE) | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym
	$(READELF) -A $(IMAGE)

dumpvmstate:
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) \
	                    -m 1024 \
			    -nographic -serial mon:stdio \
	                    -kernel $(IMAGE) \
			    -dump-vmstate vmstate.json 

qemu:
	@qemu-system-arm -M ? | grep $(board) >/dev/null || exit
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) \
	                    -m $(MEM_SIZE) \
			    -nographic -serial mon:stdio \
	                    -kernel $(IMAGE) 
			   
gdbserver:
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) -m $(MEM_SIZE) \
			    -nographic -serial mon:stdio \
	                    -kernel $(IMAGE) \
			    -S -s 
gdb: $(IMAGE)
	$(GDB) $^ -ex "target remote:1234"


gdbqemu:
	gdb --args qemu-system-arm -machine $(board) -cpu $(CPU_TYPE)  -m 4096  -nographic -serial mon:stdio -kernel kernel.elf


			    
clean:
	rm -f $(IMAGE) *.o *.list *.sym

.PHONY: all qemu clean
