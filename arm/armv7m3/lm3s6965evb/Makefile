
BIN_PATH = bin
OBJ_PATH = obj

TOOL_CHAIN = arm-none-eabi-
CC = ${TOOL_CHAIN}gcc
AS = ${TOOL_CHAIN}as
LD = ${TOOL_CHAIN}ld
NM = ${TOOL_CHAIN}nm
OBJCOPY = ${TOOL_CHAIN}objcopy
OBJDUMP = $(TOOL_CHAIN)objdump

CFLAGS		:= -Wall -g -fno-builtin -gdwarf-2 -gstrict-dwarf -mcpu=cortex-m3 -mthumb -nostartfiles  --specs=nosys.specs -std=c11 \
				-O0 -Isrc/include
LDFLAGS		:= -g

objs := src/kernel/int_vector.o \
		src/kernel/cm3.o \
		src/kernel/os_stdio.o \
		src/kernel/cm3_s.o \
		src/kernel/task.o \
		src/kernel/lib.o \
		src/kernel/event.o \
		src/kernel/sem.o \
		src/kernel/mailbox.o \
		src/kernel/memblock.o \
		src/kernel/timer.o \
		src/kernel/mutex.o \
		src/kernel/flag_group.o \
		src/main.o \
		\
		src/testcase/testcase.o

$(BIN_PATH)/rtos.bin: $(objs)
	$(shell mkdir $(BIN_PATH))
	$(shell mkdir $(OBJ_PATH))
	${LD} -T src/fan.ld -o $(BIN_PATH)/rtos.elf $^
	${OBJCOPY} -O binary -S $(BIN_PATH)/rtos.elf $@
	${OBJDUMP} -D -m arm $(BIN_PATH)/rtos.elf > $(BIN_PATH)/rtos.dis
	${NM} $(BIN_PATH)/rtos.elf > $(BIN_PATH)/rtos.nm

run:
	qemu-system-arm -M lm3s6965evb --kernel $(BIN_PATH)/rtos.bin -nographic

debug: $(objs)
	${LD} -T src/fan.ld -o rtos.elf $^
	${OBJCOPY} -O binary -S rtos.elf rtos.bin
	${OBJDUMP} -D -m arm rtos.elf > rtos.dis
	${NM} rtos.elf > rtos.nm
	qemu-system-arm -M lm3s6965evb --kernel rtos.bin -nographic -s -S

%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${CC} $(CFLAGS) -c -o $@ $<

clean:
	rm -rf src/*.o *.elf *.bin *.dis *.nm src/kernel/*.o src/testcase/*.o $(BIN_PATH) $(OBJ_PATH)
