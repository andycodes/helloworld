CC = gcc
OUTPUT = ./out
TARGET = $(OUTPUT)/mcu.elf
OUT_OBJS_DIR = $(OUTPUT)/obj
SRC_DIRS = bsp app .
## used headers  file path
INCLUDE_PATH = include
## used include librarys file path
LIBRARY_PATH := /lib
## need libs, add at here
LIBS :=
##
CFLAGS :=


## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## debug mode
ifeq (1, ${DBG_ENABLE}) 
CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
else
CFLAGS += -O2
endif

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))



# foreach表示遍历$(SRC_DIRS)的所有子目录同时把子目录下的.c文件遍历出来
SRC_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

SRC_OBJS = $(patsubst %.c,%.o,$(SRC_FILES))

OUT_OBJS  = $(addprefix $(OUT_OBJS_DIR)/,$(notdir $(patsubst %.c,%.o,$(SRC_FILES)))) 
$(info OUT_OBJS：$(OUT_OBJS))

all: $(TARGET)
$(TARGET):$(OUT_OBJS)
	$(CC) $(OUT_OBJS) -o $(TARGET)
$(OUT_OBJS):$(SRC_OBJS)
$(SRC_OBJS):%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c  $<
	mv $@ $(OUT_OBJS_DIR)


clean:
	-$(RM) $(TARGET)
	-$(RM) $(OUT_OBJS)
