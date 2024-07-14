PREFIX ?= aarch64-linux-gnu-

asm-objs = boot.o el0_entry.o

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
DUMP = $(PREFIX)objdump
READELF = readelf

OBJECT?=felix
TARGET:=$(OBJECT).elf
TARGET_OBJDUMP:=$(OBJECT).dump
TARGET_READELF:=$(OBJECT).readelf
TARGET_MAP ?= $(OBJECT).map

.PHONY: all

all: $(TARGET) $(TARGET_OBJDUMP) $(TARGET_READELF)


$(asm-objs): %.o: %.S
	${CC} -nostdlib -nostartfiles -g -c $< -o $@

$(TARGET): $(asm-objs)
	$(LD) -T linker.ld -g -static $(asm-objs) -o $(TARGET) --entry=start64  --cref -M=$(TARGET_MAP)

$(TARGET_OBJDUMP): $(TARGET)
	@echo LIST on $@
	$(Q)$(DUMP) -x -s -S $< > $@

$(TARGET_READELF): $(TARGET)
	$(Q)$(READELF) -a $< > $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(TARGET_OBJDUMP) $(TARGET_READELF) $(TARGET_MAP)