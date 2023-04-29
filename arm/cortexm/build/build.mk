
$(info "!!!!THE CUR BOARD is $(board)")

include src/platform/$(board)/board_config.mk
include build/$(CC)/$(CPU_TYPE).mk
include build/$(CC)/$(CC).mk

PRJ       := felix
OPT_LEVEL := z
C_STD     := c11
DBG_LEVEL := 3

include build/$(ARCH).mk

OUT := bin/$(board)
OBJ := $(addprefix $(OUT)/, $(CSRC:.c=.o))
OBJ += $(addprefix $(OUT)/, $(SSRC:.s=.o))

TARGET:=$(OUT)/$(PRJ).elf
TARGET_LST:=$(OUT)/$(PRJ).lst
TARGET_BIN:=$(OUT)/$(PRJ).bin
TARGET_MAP:=$(OUT)/$(PRJ).map

LDFLAGS := -T $(LDSCRIPT)

ifeq ($(VERBOSE),y)
Q:=
else
Q:=@
endif

.PHONY: all clean list size rebuild qemu

all: $(TARGET_BIN) $(TARGET_LST) 

$(OUT)/%.o: %.c
	@echo CC $^
	@mkdir -p $(dir $@)
	$(Q)$(CC) -o $@ $(CFLAGS) -c $<

$(OUT)/%.o: %.s
	${CC} $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	@echo LD $@
	$(Q)$(LD) -o $@ $(LDFLAGS) $(OBJ)

$(TARGET_LST): $(TARGET)
	@echo LIST on $@
	$(Q)$(DUMP) -x -s -S $< > $@

$(TARGET_BIN): $(TARGET)
	@echo COPY to $@
	$(Q)$(COPY) -O binary $< $@

size: $(TARGET)
	$(Q)$(SIZE) $<

clean:
	@echo CLEAN
	@rm -fR $(OUT)

rebuild: clean all

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