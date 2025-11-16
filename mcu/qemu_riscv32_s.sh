#! /bin/bash
#make qemu board=mps3-an547
#make gdbserver board=mps3-an547
#make gdb board=mps3-an547
#（gdb）target remote :8886


#! /bin/bash
qemu-system-riscv32 -nographic -smp 1 -machine \
virt -bios none -kernel bin/riscv32/felix.elf \
-S -gdb tcp::8888