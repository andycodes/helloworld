LDSCRIPT  := build/link.ld
########
PREFIX = /project/clang/bin/
CC = $(PREFIX)clang
LD = $(PREFIX)ld.lld
SIZE = $(PREFIX)llvm-size
# LLVM PR35281
COPY = $(PREFIX)llvm-objcopy
DUMP = $(PREFIX)llvm-objdump

CFLAGS += -ffreestanding
CFLAGS += -O$(OPT_LEVEL)
CFLAGS += -std=$(C_STD)
CFLAGS += -Wall
CFLAGS += -g$(DBG_LEVEL)
CFLAGS += -D__ARMCC_VERSION=6100100

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
