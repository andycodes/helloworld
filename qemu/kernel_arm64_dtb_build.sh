#!/bin/bash

cd /project/linux/linux

export ARCH=arm64 
export CROSS_COMPILE=aarch64-linux-gnu-

make ARCH=arm64 mrproper

# stay in the current dir, do not cd to ./build
# 如果需要调整配置选项，则使用 menuconfig 进行配置
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig

#make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image -j4
#make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs -j4
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image dtbs -j4

cp arch/arm64/boot/Image /project/qemu/image/
cp vmlinux /project/qemu/image/


