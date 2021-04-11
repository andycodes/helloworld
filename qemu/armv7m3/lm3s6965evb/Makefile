CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
ARM = qemu-system-arm

#-specs=nosys.specs£ºfix undefined reference to `_exit¡®
main.bin:main.c syscalls.c startup.c
	$(CC) -specs=nosys.specs -std=c11 -g -mcpu=cortex-m3 -mthumb -nostartfiles -T lm3s6965.ld syscalls.c startup.c main.c -static -o main
	$(OBJCOPY) -O binary -S -R .note -R .comment main main.bin
	$(OBJDUMP) -S main > main.list

QEMU: main.bin
	$(ARM) -M lm3s6965evb --kernel main.bin --serial stdio #-nographic
DEBUG: main.bin
	$(ARM) -M lm3s6965evb -nographic -monitor null -serial null -semihosting  -kernel main.bin  -S  -gdb tcp::123456

clean: main.bin
	rm main.bin main main.list