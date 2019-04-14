	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv3
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
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
	.type	Rand, %function
Rand:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	movw	r3, #:lower16:m_RandSeed
	movt	r3, #:upper16:m_RandSeed
	ldr	r2, [r3]
	movw	r3, #26125
	movt	r3, 25
	mul	r2, r3, r2
	movw	r3, #62303
	movt	r3, 15470
	add	r3, r2, r3
	movw	r2, #:lower16:m_RandSeed
	movt	r2, #:upper16:m_RandSeed
	str	r3, [r2]
	movw	r3, #:lower16:m_RandSeed
	movt	r3, #:upper16:m_RandSeed
	ldr	r3, [r3]
	mov	r3, r3, lsr #5
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	Rand, .-Rand
	.align	2
	.global	wait
	.type	wait, %function
wait:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	b	.L4
.L5:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
.L4:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L5
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	wait, .-wait
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #0
	str	r3, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	bl	Rand
	mov	r3, #16
	movt	r3, 22016
	mov	r2, #1392640
	str	r2, [r3]
	bl	init_uart
.L7:
	movw	r0, #34464
	movt	r0, 1
	bl	wait
	mov	r3, #20
	movt	r3, 22016
	ldr	r2, [fp, #-8]
	add	r1, r2, #1
	str	r1, [fp, #-8]
	mov	r2, r2, asl #7
	mvn	r2, r2
	str	r2, [r3]
	b	.L7
	.size	main, .-main
	.ident	"GCC: (ctng-1.21.0-229g-FA) 4.9.3"
	.section	.note.GNU-stack,"",%progbits
