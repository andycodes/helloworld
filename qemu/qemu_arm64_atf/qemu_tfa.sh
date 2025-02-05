#!/bin/bash

cd /project/atf/atf210/build/qemu/debug
dd if=bl1.bin of=flash.bin bs=4096 conv=notrunc
# 下面需要设置seek=64的原因是在qemu平台中定义了fip文件的起始地址从0x40000开始，
#具体详见下面的宏定义（位于plat/qemu/qemu/include/platform_def.h）
# #define PLAT_QEMU_FIP_BASE		0x00040000
dd if=fip.bin of=flash.bin bs=4096 seek=64 conv=notrunc
# 再创建另一个flash文件用于保存u-boot环境变量参数以及接下来存放linux内核镜像。
dd if=/dev/zero of=flash2.bin bs=4096 count=16384
# 通过QEMU加载flash.bin启动。之后会进入u-boot的命令行界面
qemu-system-aarch64 -M virt,secure=on -cpu cortex-a710 -smp 2 -m 1024 \
-nographic -bios flash.bin -drive if=pflash,format=raw,index=1,file=flash2.bin
# 在u-boot的命令行中输入bdinfo，我们可以看到单板状态信息
