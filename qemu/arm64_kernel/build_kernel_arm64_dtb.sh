#!/bin/bash

# 判断参数个数是否为2
if [ $# -ne 1 ]; then
    echo "错误：脚本需要 exactly 1 个参数，但传递了 $# 个参数。"
    exit 1
fi

# 获取第二个参数（注意：脚本只允许1个参数，这里只是为了演示）
if [ -n "$1" ]; then
    echo "第二个参数的值是: $1"
    linux_path=$1
else
    echo "警告：没有传递第1个参数。"
    exit 1
fi

cd $linux_path

export ARCH=arm64 
export CROSS_COMPILE=aarch64-linux-gnu-

make ARCH=arm64 mrproper

# stay in the current dir, do not cd to ./build
# 如果需要调整配置选项，则使用 menuconfig 进行配置
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
#make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig

#make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image -j4
#make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs -j4
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image dtbs -j4

#cp arch/arm64/boot/Image /project/qemu/image/ 
#cp vmlinux /project/qemu/image/ 

