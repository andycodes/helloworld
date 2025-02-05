#!/bin/bash

# https://developer.arm.com/downloads/-/gnu-a
# gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar
# https://github.com/ARM-software/arm-trusted-firmware
# make CROSS_COMPILE=aarch64-none-elf- PLAT=qemu clean
# make CROSS_COMPILE=aarch64-none-elf- PLAT=qemu DEBUG=1 V=1 BL33=/project/uboot/u-boot-master/u-boot.bin all fip -j4
#

make CROSS_COMPILE=aarch64-none-elf- PLAT=qemu DEBUG=1 V=1 BL33=/project/uboot/uboot/u-boot.bin all fip -j4