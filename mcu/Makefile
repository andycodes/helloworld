CC = gcc
CFLAGS = -O2 -Iinclude
TARGET = mcu
OUTPUT = ./debug
DIRS = bsp app .
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
