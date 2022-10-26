#instll clang llvm lld
include build/cortex-m3.mk

########
# Project name
PRJ       := felix
OPT_LEVEL := z
C_STD     := c11
DBG_LEVEL := 3
LDSCRIPT  := build/link.ld
########

CSRC := src/$(ARCH)/cm3.c \
		src/$(ARCH)/main.c \
		src/platform/$(board)/cmsdk_uart.c

SSRC := src/$(ARCH)/cm3_s.s

CFLAGS := $(ARCH_FLAGS)

include src/platform/$(board)/platform_clang.mk
include src/rtos/evolution/evolution_clang.mk
include src/libs/libs_clang.mk
include src/cmsis/cmsis.mk

OUT := bin/$(board)
OBJ := $(addprefix $(OUT)/, $(CSRC:.c=.o))
OBJ += $(addprefix $(OUT)/, $(SSRC:.s=.o))

CC = $(PREFIX)clang
LD = $(PREFIX)ld.lld
SIZE = $(PREFIX)llvm-size
# LLVM PR35281
COPY = $(PREFIX)llvm-objcopy
DUMP = $(PREFIX)llvm-objdump

TARGET:=$(OUT)/$(PRJ).elf
TARGET_LST:=$(OUT)/$(PRJ).lst
TARGET_BIN:=$(OUT)/$(PRJ).bin
TARGET_MAP:=$(OUT)/$(PRJ).map


CFLAGS += -ffreestanding
CFLAGS += -O$(OPT_LEVEL)
CFLAGS += -std=$(C_STD)
CFLAGS += -Wall
CFLAGS += -g$(DBG_LEVEL)

CFLAGS += 	-Isrc/include \
			-Isrc/$(ARCH)\
			-Isrc/libs\
			-Isrc/platform/$(board)

LDFLAGS := --Bstatic
LDFLAGS += --build-id
LDFLAGS += --gc-sections
LDFLAGS += --Map $(TARGET_MAP)
LDFLAGS += --script $(LDSCRIPT)
LDFLAGS += -Llib

ifeq ($(VERBOSE),y)
Q:=
else
Q:=@
endif

all: $(TARGET_BIN) $(TARGET_LST) size

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

.PHONY: all clean list size rebuild
