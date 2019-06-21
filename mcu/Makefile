CC = gcc
TARGET = mcu
OUTPUT = ./debug
DIRS = bsp app .
## used headers  file path
INCLUDE_PATH = include
## used include librarys file path
LIBRARY_PATH := /lib
## need libs, add at here
LIBS :=

CFLAGS = -O2

## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE}) 
CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))



# foreach表示遍历$(D_SRC)的所有子目录同时把子目录下的.c文件遍历出来
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
#OBJS = $(patsubst %.c, %.o, $(FILES))
DIR_OBJS        = $(patsubst %.c,%.o,$(FILES))
OBJS          = $(addprefix $(OUTPUT)/,$(notdir $(patsubst %.c,%.o,$(FILES)))) 
$(info OBJS：$(OBJS))
all: $(TARGET)
$(TARGET):$(OUTPUT) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)
$(OBJS):$(DIR_OBJS)
$(DIR_OBJS):%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c  $<
	mv $@ ./debug/ 


clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
