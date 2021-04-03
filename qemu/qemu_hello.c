#include<stdio.h>

int main()
{
	printf("Hello, Qemu!\n");
}

/*
��̬���ӿ�
arm-none-linux-gnueabi-gcc -ggdb  qemu_hello.c -static -o hello
 $ qemu-arm ./hello
 $ file hello
 hello: ELF 32-bit LSB? executable, ARM, EABI5 version 1 (SYSV), \?statically linked, for GNU/Linux 2.6.16, not stripped


��̬���ӿ�
����-static�����Ļ�������ʱ����Ҫʹ��-Lѡ�����ӵ���Ӧ�����п�
arm-none-linux-gnueabi-gcc -o hello_1 qemu_hello.c
qemu-arm -L /usr/local/arm-2014.05/arm-none-linux-gnueabi/libc/ ./hello_1
Hello, Qemu!
$ file hello_1
hello_1: ELF 32-bit LSB? executable, ARM, EABI5 version 1 (SYSV),\?dynamically linked (uses shared libs), for GNU/Linux 2.6.16, not stripped

��̬����;�̬�������ɵ��ļ���С���
root@hyy-K42Jc:/project/andy/bsp/qemu# ls -l
total 636
-rwxr-xr-x 1 root   root    635663 Mar 26 16:12 hello
-rwxr-xr-x 1 root   root      6627 Mar 26 16:18 hello_1
-rwxr--r-- 1 nobody nogroup     72 Mar 26 16:08 qemu_hello.c

*/
