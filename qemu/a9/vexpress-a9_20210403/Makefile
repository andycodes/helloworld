all:
	arm-none-eabi-gcc -g -c -o start.o start.S
	arm-none-eabi-ld -Ttext 0x0 -o kernel.elf start.o
	
run: all
	qemu-system-arm -machine vexpress-a9 -m 256M -serial stdio -kernel kernel.elf -S -s

clean:
	rm -rf *.o kernel.elf