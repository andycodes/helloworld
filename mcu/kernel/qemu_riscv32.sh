#! /bin/bash
qemu-system-riscv32 -nographic -smp 1 -machine virt -bios none -kernel bin/riscv32/felix.elf