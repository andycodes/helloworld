#! /bin/bash
#make qemu board=mps3-an547
#make gdbserver board=mps3-an547
#make gdb board=mps3-an547
#（gdb）target remote :8886

gdb-multiarch bin/riscv32/felix.elf
#（gdb）target remote :8886