#! /bin/bash

aarch64-linux-gnu-gcc -static -ggdb -o hello qemu_hello.c
qemu-aarch64 hello


