CC = gcc
CFLAGS = -O2 -Iinclude
TARGET = out/mcu
DIRS = bsp app .
# foreach表示遍历$(D_SRC)的所有子目录同时把子目录下的.c文件遍历出来
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(info OBJS：$(OBJS))
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
