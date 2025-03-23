#! /bin/bash

qemu-system-aarch64\
 -kernel /project/kernel/kernel/arch/arm64/boot/Image\
 -nographic \
-append "root=/dev/vda console=ttyAMA0 rootfstype=ext4 init=/linuxrc rw" \
-m 2048M -smp 1 -M virt -cpu cortex-a710 -initrd initramfs.cpio.gz