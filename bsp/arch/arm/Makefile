mmu : head.s  main.c init.c init.h mmu.c mmu.h s3c2410.h serial.h interrupt.c interrupt.h
	arm-linux-gcc  -c -o head.o head.s
	arm-linux-gcc -c -o init.o init.c
	arm-linux-gcc -c -o serial.o serial.c
	arm-linux-gcc -c -o mmu.o mmu.c
	arm-linux-gcc -c -o interrupt.o interrupt.c
	arm-linux-gcc -o main.i -E main.c
	arm-linux-gcc -o main.s -S main.i
	arm-linux-gcc -o main.o -c main.s
	arm-linux-objdump -dx main.o >main.dump
	readelf -r main.o >main.elf
	arm-linux-ld -Tmmu.lds	head.o init.o main.o serial.o  interrupt.o mmu.o -o mmu_tmp.o
	arm-linux-objcopy -O binary -S mmu_tmp.o mmu
	arm-linux-objdump -D -b binary -m arm  mmu >mmu.asm
	arm-linux-objdump -dx mmu_tmp.o >mmu.dump
	arm-linux-nm mmu_tmp.o >mmu.nm
	readelf -r mmu_tmp.o >mmu.elf
clean:
	rm -f  head.o   init.o  main.o mmu.o  tmp.o  serial.o mmu_tmp.o interrupt.o mmu
