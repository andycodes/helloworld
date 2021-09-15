.text
.global _start
_start:
ldr r0, stacktop
mov sp, r0

stop:
nop
b stop

stacktop: .word stack + 4 * 4096
.data
stack: .space 4 * 4096