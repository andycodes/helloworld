#! /bin/bash

qemu-system-aarch64 -kernel /project/linux/linux/arch/arm64/boot/Image -nographic \
-append "root=/dev/ram0 console=ttyAMA0 clocksource=pit rw rdinit=/linuxrc" \
-m 2048M -smp 1 -M virt -cpu cortex-a710 -initrd ramdisk.gz
