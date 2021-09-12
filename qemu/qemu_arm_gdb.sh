#! /bin/bash
qemu-system-arm -serial stdio -kernel hello1 -m 256M -machine vexpress-a15 -S -s

