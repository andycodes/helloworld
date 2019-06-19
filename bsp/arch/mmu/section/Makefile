objs := head.o init.o leds.o
# $^ 代表所有的依赖文件。 $@--目标文件，$<--第一个依赖文件。 
mmu.bin : $(objs)
	arm-linux-ld -Tmmu.lds -o mmu_linux $^
	arm-linux-objcopy -O binary -S mmu_linux $@         # binary：二进制的 -S：不从源文件复制重定位信息和符号信息到目标文件中去
	arm-linux-objdump -D -m arm mmu_linux > mmu.dis # -D：反汇编所有段 -m arm:指定反汇编文件使用arm架构

%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<            #-Wall：打开警告信息 -O2：2级优化(常用) -c：只编译不连接

%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f mmu.bin mmu_linux mmu.dis *.o