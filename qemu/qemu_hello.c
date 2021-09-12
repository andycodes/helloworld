#include<stdio.h>

int main()
{
        printf("Hello, Qemu!\n");
}

/*
	ARMv7

静态链接库
arm-none-linux-gnueabihf-gcc -ggdb qemu_hello.c -static -o hello
 $ qemu-arm ./hello
 $ file hello
 hello: ELF 32-bit LSB? executable, ARM, EABI5 version 1 (SYSV), \?statically linked, for GNU/Linux 2.6.16, not stripped


动态链接库
不加-static变量的话，运行时则需要使用-L选项链接到
相应的运行库
arm-none-linux-gnueabihf-gcc -ggdb -o hello1 qemu_hello.c
qemu-arm -L /project/gcc/arm-none-linux-gnueabihf/arm-none-linux-gnueabihf/libc ./hello1
Hello, Qemu!
$ file hello_1
hello_1: ELF 32-bit LSB? executable, ARM, EABI5 version 1 (SYSV),\?dynamically linked (uses shared libs), for GNU/Linux 2.6.16, not stripped

动态编译和静态编译生成的文件大小差别：
root@hyy-K42Jc:/project/andy/bsp/qemu# ls -l
total 636
-rwxr-xr-x 1 root   root    635663 Mar 26 16:12 hello
-rwxr-xr-x 1 root   root      6627 Mar 26 16:18 hello_1
-rwxr--r-- 1 nobody nogroup     72 Mar 26 16:08 qemu_hello.c

*/

/*
	ARMv8 AARCH64
aarch64-linux-gnu-gcc -static -ggdb -o hello qemu_hello.c
file hello
qemu-aarch64 hello
*/
