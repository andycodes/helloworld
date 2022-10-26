
$(info "!!!!THE CUR BOARD is $(board)")

include src/platform/$(board)/board_config.mk

OUT = bin/$(board)
OBJ_PATH = obj
PRJ = felix

$(info "!!!!THE CUR CPU_TYPE is $(CPU_TYPE)")
TARGET := $(OUT)/$(PRJ).elf
TARGET_LST := $(OUT)/$(PRJ).list
TARGET_SYM := $(OUT)/$(PRJ).sym
TARGET_BIN := $(OUT)/$(PRJ).bin

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

all: $(TARGET)
include build/gcc_$(ARCH).mk

%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${CC} $(CFLAGS) -c -o $@ $<

$(TARGET): $(LDFILE)  $(OBJS)
	$(LD)  $(OBJS) -T $(LDFILE) -o $(TARGET)
	$(OBJDUMP) -d $(TARGET) > $(TARGET_LST)
	$(OBJDUMP) -t $(TARGET) | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(TARGET_SYM)
	$(READELF) -A $(TARGET)
	$(OBJCOPY) -O binary $(TARGET) $(TARGET_BIN)

dumpvmstate:
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) \
	                    -m 1024 \
			    -nographic -serial mon:stdio \
	                    -kernel $(TARGET) \
			    -dump-vmstate vmstate.json 

qemu:
	@qemu-system-arm -M ? | grep $(board) >/dev/null || exit
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) \
	                    -m $(MEM_SIZE) \
			    -nographic -serial mon:stdio \
	                    -kernel $(TARGET) 
			   
gdbserver:
	qemu-system-arm -machine $(board) -cpu $(CPU_TYPE) -m $(MEM_SIZE) \
			    -nographic -serial mon:stdio \
	                    -kernel $(TARGET) \
			    -S -s 
gdb: $(TARGET)
	$(GDB) $^ -ex "target remote:1234"


gdbqemu:
	gdb --args qemu-system-arm -machine $(board) -cpu $(CPU_TYPE)  -m 4096  -nographic -serial mon:stdio -$(ARCH) $(TARGET)

	    
clean:
	rm -rf $(OUT) $(OBJ_PATH) *.o
.PHONY: all qemu clean
