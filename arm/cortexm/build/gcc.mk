
$(info "!!!!THE CUR BOARD is $(board)")

include src/platform/$(board)/board_config.mk

BIN_PATH = bin/$(board)
OBJ_PATH = obj
OBJECT = felix

$(info "!!!!THE CUR CPU_TYPE is $(CPU_TYPE)")
IMAGE := $(BIN_PATH)/$(OBJECT).elf
LIST_FILE := $(BIN_PATH)/$(OBJECT).list
SYM_FILE := $(BIN_PATH)/$(OBJECT).sym
BIN_FILE := $(BIN_PATH)/$(OBJECT).bin

CROSS_COMPILE = $(PWD_TOOLCHAIN)/arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
GDB = $(CROSS_COMPILE)gdb
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = ${CROSS_COMPILE}objcopy
READELF = $(CROSS_COMPILE)readelf
LDFILE = src/platform/$(board)/plat.ld

CFLAGS =  -fno-builtin -nostdlib -nostartfiles -ffreestanding \
			-Wall -g\
			-mcpu=$(CPU_TYPE)\
			-Isrc/include \
			-Isrc/$(ARCH)\
			-Isrc/libs\
			-Isrc/platform/$(board)

all: $(IMAGE)
include build/gcc_$(ARCH).mk

$(IMAGE): $(LDFILE)  $(OBJS)
	$(LD)  $(OBJS) -T $(LDFILE) -o $(IMAGE)
	$(OBJDUMP) -d $(IMAGE) > $(LIST_FILE)
	$(OBJDUMP) -t $(IMAGE) | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(SYM_FILE)
	$(READELF) -A $(IMAGE)
	$(OBJCOPY) -O binary $(IMAGE) $(BIN_FILE)

%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${CC} $(CFLAGS) -c -o $@ $<

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
	gdb --args qemu-system-arm -machine $(board) -cpu $(CPU_TYPE)  -m 4096  -nographic -serial mon:stdio -$(ARCH) $(IMAGE)

	    
clean:
	rm -rf $(BIN_PATH) $(OBJ_PATH) *.o
.PHONY: all qemu clean
