all:
	arm-none-eabi-gcc -g -c -o start.o start.S
	arm-none-eabi-ld -Tmap.lds -o test.elf start.o



run: all
	qemu-system-arm -machine vexpress-a9 -m 256M -serial stdio -kernel test.elf -S -s &
	sleep 3
	arm-none-eabi-gdb test.elf

clean:
	rm -rf *.o test.elf