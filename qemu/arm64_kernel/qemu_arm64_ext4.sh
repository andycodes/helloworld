#! /bin/bash

qemu-system-aarch64 -m 2048M -cpu cortex-a710,sve=on -M virt,gic-version=3,its=on,iommu=smmuv3 -nographic \
-smp 4 -kernel /project/kernel/kernel/arch/arm64/boot/Image  -append "noinintrd sched_debug root=/dev/vda rootfstype=ext4 rw crashkernel=256M loglevel=8" \
-drive if=none,file=busybox-rootfs_ext4.img,id=hd0 -device virtio-blk-device,drive=hd0 
