CC = gcc
CFLAGS = -O2 -Iinclude
TARGET = out/mcu
DIRS = bsp app .
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
