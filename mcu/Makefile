IMAGE = mcu

ARCH :=arm

ifeq ($(ARCH),arm) 
CC = arm-linux-gnueabi-gcc
NM = arm-linux-gnueabi-gcc-nm
OBJDUMP = arm-linux-gnueabi-objdump
SRC_DIRS = bsp app
else
CC = gcc
NM = nm
OBJDUMP = objdump
SRC_DIRS = x86 app
endif

LDFLAGS :=
OUTPUT_DIR = ./out
TARGET = $(OUTPUT_DIR)/$(IMAGE).elf
OUT_OBJS_DIR = $(OUTPUT_DIR)/obj
OUT_LIBS_DIR = $(OUTPUT_DIR)/libs
LIBS_DIRS = libs
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
CFLAGS += -O3
endif

##c files 
# foreach表示遍历$(SRC_DIRS)的所有子目录同时把子目录下的.c文件遍历出来
SRC_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
SRC_OBJS = $(patsubst %.c,%.o,$(SRC_FILES))
OUT_OBJS  = $(addprefix $(OUT_OBJS_DIR)/,$(notdir $(patsubst %.c,%.o,$(SRC_FILES))))


##asm files 
# foreach表示遍历$(SRC_DIRS)的所有子目录同时把子目录下的.c文件遍历出来
ASM_SRC_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.s))
ASM_SRC_OBJS = $(patsubst %.s,%.o,$(ASM_SRC_FILES))
ASM_OUT_OBJS  = $(addprefix $(OUT_OBJS_DIR)/,$(notdir $(patsubst %.s,%.o,$(ASM_SRC_FILES))))


##LIBS
LIBS_SRC_FILES = $(foreach dir, $(LIBS_DIRS), $(wildcard $(dir)/*.c))
LIBS_SRC_OBJS = $(patsubst %.c,%.o,$(LIBS_SRC_FILES))
LIBS_OUT_OBJS  = $(addprefix $(OUT_LIBS_DIR)/,$(notdir $(patsubst %.c,%.o,$(LIBS_SRC_FILES)))) 


##Makefile 调试工具
$(info OUT_OBJS：$(OUT_OBJS))


all: $(TARGET)
$(TARGET):$(OUT_OBJS) $(LIBS_OUT_OBJS)
	$(CC) $(OUT_OBJS) $(LDFLAGS) -o $(TARGET)	
	readelf -s $(TARGET) >$(OUTPUT_DIR)/$(IMAGE).sym
	$(NM) $(TARGET) >$(OUTPUT_DIR)/$(IMAGE).nm
	$(OBJDUMP) -j .text -l -C -S $(TARGET) >$(OUTPUT_DIR)/$(IMAGE).asm
$(OUT_OBJS):$(SRC_OBJS) $(ASM_SRC_OBJS)
$(LIBS_OUT_OBJS):$(LIBS_SRC_OBJS)
$(SRC_OBJS):%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c  $<
	mv $@ $(OUT_OBJS_DIR)
$(ASM_SRC_OBJS):%.o : %.s
	$(CC) $(CFLAGS) -o $@ -c  $<
	mv $@ $(OUT_OBJS_DIR)
$(LIBS_SRC_OBJS):%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c  $<
	mv $@ $(LIBS_OUT_OBJS)

#.PHONY是一个伪目标，可以防止在Makefile中定义的只执行命令的目标和工作目录下的实际文件出现名字冲突.
.PHONY:clean
clean:
	rm -rf $(OUTPUT_DIR)
