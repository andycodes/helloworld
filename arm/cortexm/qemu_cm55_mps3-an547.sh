#! /bin/bash
qemu-system-arm -machine mps3-an547 -cpu cortex-m55 \
    -m 2048 -nographic -serial mon:stdio \
    -kernel ./bin/mps3-an547/felix.elf