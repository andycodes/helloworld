	.arch armv5t
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.local	m_RandSeed
	.comm	m_RandSeed,4,4
	.data
	.align	2
	.type	m_RandSeed1, %object
	.size	m_RandSeed1, 4
m_RandSeed1:
	.word	305419896
	.text
	.align	2
	.global	Rand
	.syntax unified
	.arm
	.fpu softvfp
	.type	Rand, %function
Rand:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L3
	ldr	r3, [r3]
	ldr	r2, .L3+4
	mul	r1, r3, r2
	ldr	r3, .L3+8
	add	r3, r1, r3
	ldr	r2, .L3
	str	r3, [r2]
	ldr	r3, .L3
	ldr	r3, [r3]
	lsr	r3, r3, #5
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L4:
	.align	2
.L3:
	.word	m_RandSeed
	.word	1664525
	.word	1013904223
	.size	Rand, .-Rand
	.align	2
	.global	wait
	.syntax unified
	.arm
	.fpu softvfp
	.type	wait, %function
wait:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	b	.L6
.L7:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
.L6:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L7
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	wait, .-wait
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #0
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-8]
	bl	Rand
	ldr	r3, .L10
	mov	r2, #1392640
	str	r2, [r3]
	bl	init_uart
.L9:
	ldr	r0, .L10+4
	bl	wait
	ldr	r3, [fp, #-12]
	add	r2, r3, #1
	str	r2, [fp, #-12]
	lsl	r3, r3, #7
	ldr	r2, .L10+8
	mvn	r3, r3
	str	r3, [r2]
	b	.L9
.L11:
	.align	2
.L10:
	.word	1442840592
	.word	100000
	.word	1442840596
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",%progbits
