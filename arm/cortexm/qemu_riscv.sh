#! /bin/bash
#make qemu board=mps3-an547
#make gdbserver board=mps3-an547
#make gdb board=mps3-an547
#（gdb）target remote :8886

QEMUOPTS='-machine virt -bios none -kernel bin/riscv/felix.elf -m 128M -smp 1 -nographic '
QEMUOPTS+='-global virtio-mmio.force-legacy=false '
echo $QEMUOPTS
qemu-system-riscv64 $QEMUOPTS