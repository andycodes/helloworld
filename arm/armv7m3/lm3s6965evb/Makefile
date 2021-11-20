
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
				-O0 -Iinclude
LDFLAGS		:= -g

objs := kernel/int_vector.o main.o kernel/cm3.o kernel/os_stdio.o kernel/cm3_s.o kernel/task.o kernel/lib.o kernel/event.o kernel/sem.o kernel/mailbox.o kernel/memblock.o kernel/timer.o kernel/mutex.o kernel/flag_group.o testcase/testcase.o

$(BIN_PATH)/rtos.bin: $(objs)
	$(shell mkdir $(BIN_PATH))
	$(shell mkdir $(OBJ_PATH))
	${LD} -T fan.ld -o $(BIN_PATH)/rtos.elf $^
	${OBJCOPY} -O binary -S $(BIN_PATH)/rtos.elf $@
	${OBJDUMP} -D -m arm $(BIN_PATH)/rtos.elf > $(BIN_PATH)/rtos.dis
	${NM} $(BIN_PATH)/rtos.elf > $(BIN_PATH)/rtos.nm

run: $(objs)
	${LD} -T fan.ld -o $(BIN_PATH)/rtos.elf $^
	${OBJCOPY} -O binary -S $(BIN_PATH)/rtos.elf $(BIN_PATH)/rtos.bin
	${OBJDUMP} -D -m arm $(BIN_PATH)/rtos.elf > $(BIN_PATH)/rtos.dis
	qemu-system-arm -M lm3s6965evb --kernel $(BIN_PATH)/rtos.bin -nographic

debug: $(objs)
	${LD} -T fan.ld -o rtos.elf $^
	${OBJCOPY} -O binary -S rtos.elf rtos.bin
	${OBJDUMP} -D -m arm rtos.elf > rtos.dis
	${NM} rtos.elf > rtos.nm
	qemu-system-arm -M lm3s6965evb --kernel rtos.bin -nographic -s -S

%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${CC} $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o *.elf *.bin *.dis *.nm kernel/*.o testcase/*.o $(BIN_PATH) $(OBJ_PATH)
