#! /bin/bash
qemu-system-arm -machine mps3-an547 -cpu cortex-m55 \
    -m 2G -nographic -serial mon:stdio \
    -kernel ./bin/cm85/felix.elf 