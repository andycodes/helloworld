#! /bin/bash

 qemu-system-aarch64 -nographic -smp 2 -machine virt,secure=on -cpu cortex-a710 \
 -d unimp -semihosting-config enable,target=native -m 1057 \
 -bios /project/atf/atf210/build/qemu/debug/bl1.bin