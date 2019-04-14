
mmu：     文件格式 binary


Disassembly of section .data:

00000000 <.data>:
       0:	ea000007 	b	0x24
       4:	eafffffe 	b	0x4
       8:	eafffffe 	b	0x8
       c:	eafffffe 	b	0xc
      10:	eafffffe 	b	0x10
      14:	eafffffe 	b	0x14
      18:	e59ff000 	ldr	pc, [pc]	; 0x20
      1c:	eafffffe 	b	0x1c
      20:	00000070 	andeq	r0, r0, r0, ror r0
      24:	e3a0da01 	mov	sp, #4096	; 0x1000
      28:	eb00001b 	bl	0x9c
      2c:	eb00003c 	bl	0x124
      30:	eb000092 	bl	0x280
      34:	eb00010e 	bl	0x474
      38:	eb000115 	bl	0x494
      3c:	e59fd040 	ldr	sp, [pc, #64]	; 0x84
      40:	e59ff040 	ldr	pc, [pc, #64]	; 0x88
      44:	eb000214 	bl	0x89c
      48:	eb000249 	bl	0x974
      4c:	e321f0d2 	msr	CPSR_c, #210	; 0xd2
      50:	e3a0d433 	mov	sp, #855638016	; 0x33000000
      54:	e321f0df 	msr	CPSR_c, #223	; 0xdf
      58:	e59fd024 	ldr	sp, [pc, #36]	; 0x84
      5c:	eb000114 	bl	0x4b4
      60:	e321f05f 	msr	CPSR_c, #95	; 0x5f
      64:	e59fe020 	ldr	lr, [pc, #32]	; 0x8c
      68:	e59ff020 	ldr	pc, [pc, #32]	; 0x90
      6c:	eafffffe 	b	0x6c
      70:	e24ee004 	sub	lr, lr, #4
      74:	e92d5fff 	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
      78:	e59fe014 	ldr	lr, [pc, #20]	; 0x94
      7c:	e59ff014 	ldr	pc, [pc, #20]	; 0x98
      80:	e8fd9fff 	ldm	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}^
      84:	30100000 	andscc	r0, r0, r0
      88:	00000044 	andeq	r0, r0, r4, asr #32
      8c:	0000006c 	andeq	r0, r0, ip, rrx
      90:	000005e8 	andeq	r0, r0, r8, ror #11
      94:	00000080 	andeq	r0, r0, r0, lsl #1
      98:	000007bc 			; <UNDEFINED> instruction: 0x000007bc
      9c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
      a0:	e28db000 	add	fp, sp, #0
      a4:	e3a03453 	mov	r3, #1392508928	; 0x53000000
      a8:	e3a02000 	mov	r2, #0
      ac:	e5832000 	str	r2, [r3]
      b0:	e24bd000 	sub	sp, fp, #0
      b4:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
      b8:	e12fff1e 	bx	lr
      bc:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
      c0:	e28db000 	add	fp, sp, #0
      c4:	e24dd00c 	sub	sp, sp, #12
      c8:	e3a03000 	mov	r3, #0
      cc:	e50b3008 	str	r3, [fp, #-8]
      d0:	e3a03312 	mov	r3, #1207959552	; 0x48000000
      d4:	e50b300c 	str	r3, [fp, #-12]
      d8:	ea00000b 	b	0x10c
      dc:	e51b3008 	ldr	r3, [fp, #-8]
      e0:	e1a03103 	lsl	r3, r3, #2
      e4:	e51b200c 	ldr	r2, [fp, #-12]
      e8:	e0822003 	add	r2, r2, r3
      ec:	e30039d8 	movw	r3, #2520	; 0x9d8
      f0:	e3403000 	movt	r3, #0
      f4:	e51b1008 	ldr	r1, [fp, #-8]
      f8:	e7933101 	ldr	r3, [r3, r1, lsl #2]
      fc:	e5823000 	str	r3, [r2]
     100:	e51b3008 	ldr	r3, [fp, #-8]
     104:	e2833001 	add	r3, r3, #1
     108:	e50b3008 	str	r3, [fp, #-8]
     10c:	e51b3008 	ldr	r3, [fp, #-8]
     110:	e353000c 	cmp	r3, #12
     114:	dafffff0 	ble	0xdc
     118:	e24bd000 	sub	sp, fp, #0
     11c:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     120:	e12fff1e 	bx	lr
     124:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     128:	e28db000 	add	fp, sp, #0
     12c:	e24dd00c 	sub	sp, sp, #12
     130:	e3a03312 	mov	r3, #1207959552	; 0x48000000
     134:	e50b3008 	str	r3, [fp, #-8]
     138:	e51b2008 	ldr	r2, [fp, #-8]
     13c:	e3013110 	movw	r3, #4368	; 0x1110
     140:	e3423211 	movt	r3, #8721	; 0x2211
     144:	e5823000 	str	r3, [r2]
     148:	e51b3008 	ldr	r3, [fp, #-8]
     14c:	e2833004 	add	r3, r3, #4
     150:	e3a02c07 	mov	r2, #1792	; 0x700
     154:	e5832000 	str	r2, [r3]
     158:	e51b3008 	ldr	r3, [fp, #-8]
     15c:	e2833008 	add	r3, r3, #8
     160:	e3a02c07 	mov	r2, #1792	; 0x700
     164:	e5832000 	str	r2, [r3]
     168:	e51b3008 	ldr	r3, [fp, #-8]
     16c:	e283300c 	add	r3, r3, #12
     170:	e3a02c07 	mov	r2, #1792	; 0x700
     174:	e5832000 	str	r2, [r3]
     178:	e51b3008 	ldr	r3, [fp, #-8]
     17c:	e2833010 	add	r3, r3, #16
     180:	e3a02c07 	mov	r2, #1792	; 0x700
     184:	e5832000 	str	r2, [r3]
     188:	e51b3008 	ldr	r3, [fp, #-8]
     18c:	e2833014 	add	r3, r3, #20
     190:	e3a02c07 	mov	r2, #1792	; 0x700
     194:	e5832000 	str	r2, [r3]
     198:	e51b3008 	ldr	r3, [fp, #-8]
     19c:	e2833018 	add	r3, r3, #24
     1a0:	e3a02c07 	mov	r2, #1792	; 0x700
     1a4:	e5832000 	str	r2, [r3]
     1a8:	e51b3008 	ldr	r3, [fp, #-8]
     1ac:	e283201c 	add	r2, r3, #28
     1b0:	e3083005 	movw	r3, #32773	; 0x8005
     1b4:	e3403001 	movt	r3, #1
     1b8:	e5823000 	str	r3, [r2]
     1bc:	e51b3008 	ldr	r3, [fp, #-8]
     1c0:	e2832020 	add	r2, r3, #32
     1c4:	e3083005 	movw	r3, #32773	; 0x8005
     1c8:	e3403001 	movt	r3, #1
     1cc:	e5823000 	str	r3, [r2]
     1d0:	e51b3008 	ldr	r3, [fp, #-8]
     1d4:	e2832024 	add	r2, r3, #36	; 0x24
     1d8:	e30037a3 	movw	r3, #1955	; 0x7a3
     1dc:	e340308e 	movt	r3, #142	; 0x8e
     1e0:	e5823000 	str	r3, [r2]
     1e4:	e51b3008 	ldr	r3, [fp, #-8]
     1e8:	e2833028 	add	r3, r3, #40	; 0x28
     1ec:	e3a020b2 	mov	r2, #178	; 0xb2
     1f0:	e5832000 	str	r2, [r3]
     1f4:	e51b3008 	ldr	r3, [fp, #-8]
     1f8:	e283302c 	add	r3, r3, #44	; 0x2c
     1fc:	e3a02030 	mov	r2, #48	; 0x30
     200:	e5832000 	str	r2, [r3]
     204:	e51b3008 	ldr	r3, [fp, #-8]
     208:	e2833030 	add	r3, r3, #48	; 0x30
     20c:	e3a02030 	mov	r2, #48	; 0x30
     210:	e5832000 	str	r2, [r3]
     214:	e24bd000 	sub	sp, fp, #0
     218:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     21c:	e12fff1e 	bx	lr
     220:	e92d4800 	push	{fp, lr}
     224:	e28db004 	add	fp, sp, #4
     228:	e24dd008 	sub	sp, sp, #8
     22c:	e3a03000 	mov	r3, #0
     230:	e50b3008 	str	r3, [fp, #-8]
     234:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     238:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     23c:	e5933000 	ldr	r3, [r3]
     240:	e3c33b02 	bic	r3, r3, #2048	; 0x800
     244:	e5823000 	str	r3, [r2]
     248:	ea000002 	b	0x258
     24c:	e51b3008 	ldr	r3, [fp, #-8]
     250:	e2833001 	add	r3, r3, #1
     254:	e50b3008 	str	r3, [fp, #-8]
     258:	e51b3008 	ldr	r3, [fp, #-8]
     25c:	e3530009 	cmp	r3, #9
     260:	dafffff9 	ble	0x24c
     264:	e3a03004 	mov	r3, #4
     268:	e3443e00 	movt	r3, #19968	; 0x4e00
     26c:	e3e02000 	mvn	r2, #0
     270:	e5c32000 	strb	r2, [r3]
     274:	eb000008 	bl	0x29c
     278:	e24bd004 	sub	sp, fp, #4
     27c:	e8bd8800 	pop	{fp, pc}
     280:	e92d4800 	push	{fp, lr}
     284:	e28db004 	add	fp, sp, #4
     288:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     28c:	e30f2830 	movw	r2, #63536	; 0xf830
     290:	e5832000 	str	r2, [r3]
     294:	ebffffe1 	bl	0x220
     298:	e8bd8800 	pop	{fp, pc}
     29c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     2a0:	e28db000 	add	fp, sp, #0
     2a4:	e24dd00c 	sub	sp, sp, #12
     2a8:	ea000008 	b	0x2d0
     2ac:	e3a03000 	mov	r3, #0
     2b0:	e50b3008 	str	r3, [fp, #-8]
     2b4:	ea000002 	b	0x2c4
     2b8:	e51b3008 	ldr	r3, [fp, #-8]
     2bc:	e2833001 	add	r3, r3, #1
     2c0:	e50b3008 	str	r3, [fp, #-8]
     2c4:	e51b3008 	ldr	r3, [fp, #-8]
     2c8:	e3530009 	cmp	r3, #9
     2cc:	dafffff9 	ble	0x2b8
     2d0:	e3a03010 	mov	r3, #16
     2d4:	e3443e00 	movt	r3, #19968	; 0x4e00
     2d8:	e5d33000 	ldrb	r3, [r3]
     2dc:	e6ef3073 	uxtb	r3, r3
     2e0:	e2033001 	and	r3, r3, #1
     2e4:	e3530000 	cmp	r3, #0
     2e8:	0affffef 	beq	0x2ac
     2ec:	e24bd000 	sub	sp, fp, #0
     2f0:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     2f4:	e12fff1e 	bx	lr
     2f8:	e92d4800 	push	{fp, lr}
     2fc:	e28db004 	add	fp, sp, #4
     300:	e24dd018 	sub	sp, sp, #24
     304:	e50b0010 	str	r0, [fp, #-16]
     308:	e50b1014 	str	r1, [fp, #-20]	; 0xffffffec
     30c:	e50b2018 	str	r2, [fp, #-24]	; 0xffffffe8
     310:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     314:	e7e83053 	ubfx	r3, r3, #0, #9
     318:	e3530000 	cmp	r3, #0
     31c:	1a000003 	bne	0x330
     320:	e51b3018 	ldr	r3, [fp, #-24]	; 0xffffffe8
     324:	e7e83053 	ubfx	r3, r3, #0, #9
     328:	e3530000 	cmp	r3, #0
     32c:	0a000000 	beq	0x334
     330:	ea00004d 	b	0x46c
     334:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     338:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     33c:	e5933000 	ldr	r3, [r3]
     340:	e3c33b02 	bic	r3, r3, #2048	; 0x800
     344:	e5823000 	str	r3, [r2]
     348:	e3a03000 	mov	r3, #0
     34c:	e50b3008 	str	r3, [fp, #-8]
     350:	ea000002 	b	0x360
     354:	e51b3008 	ldr	r3, [fp, #-8]
     358:	e2833001 	add	r3, r3, #1
     35c:	e50b3008 	str	r3, [fp, #-8]
     360:	e51b3008 	ldr	r3, [fp, #-8]
     364:	e3530009 	cmp	r3, #9
     368:	dafffff9 	ble	0x354
     36c:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     370:	e50b3008 	str	r3, [fp, #-8]
     374:	ea000030 	b	0x43c
     378:	e3a03004 	mov	r3, #4
     37c:	e3443e00 	movt	r3, #19968	; 0x4e00
     380:	e3a02000 	mov	r2, #0
     384:	e5c32000 	strb	r2, [r3]
     388:	e3a03008 	mov	r3, #8
     38c:	e3443e00 	movt	r3, #19968	; 0x4e00
     390:	e51b2008 	ldr	r2, [fp, #-8]
     394:	e6ef2072 	uxtb	r2, r2
     398:	e5c32000 	strb	r2, [r3]
     39c:	e3a03008 	mov	r3, #8
     3a0:	e3443e00 	movt	r3, #19968	; 0x4e00
     3a4:	e51b2008 	ldr	r2, [fp, #-8]
     3a8:	e1a024c2 	asr	r2, r2, #9
     3ac:	e6ef2072 	uxtb	r2, r2
     3b0:	e5c32000 	strb	r2, [r3]
     3b4:	e3a03008 	mov	r3, #8
     3b8:	e3443e00 	movt	r3, #19968	; 0x4e00
     3bc:	e51b2008 	ldr	r2, [fp, #-8]
     3c0:	e1a028c2 	asr	r2, r2, #17
     3c4:	e6ef2072 	uxtb	r2, r2
     3c8:	e5c32000 	strb	r2, [r3]
     3cc:	e3a03008 	mov	r3, #8
     3d0:	e3443e00 	movt	r3, #19968	; 0x4e00
     3d4:	e51b2008 	ldr	r2, [fp, #-8]
     3d8:	e1a02cc2 	asr	r2, r2, #25
     3dc:	e6ef2072 	uxtb	r2, r2
     3e0:	e5c32000 	strb	r2, [r3]
     3e4:	ebffffac 	bl	0x29c
     3e8:	e3a03000 	mov	r3, #0
     3ec:	e50b300c 	str	r3, [fp, #-12]
     3f0:	ea00000e 	b	0x430
     3f4:	e3a0300c 	mov	r3, #12
     3f8:	e3443e00 	movt	r3, #19968	; 0x4e00
     3fc:	e5d33000 	ldrb	r3, [r3]
     400:	e6ef2073 	uxtb	r2, r3
     404:	e51b3010 	ldr	r3, [fp, #-16]
     408:	e5c32000 	strb	r2, [r3]
     40c:	e51b3010 	ldr	r3, [fp, #-16]
     410:	e2833001 	add	r3, r3, #1
     414:	e50b3010 	str	r3, [fp, #-16]
     418:	e51b300c 	ldr	r3, [fp, #-12]
     41c:	e2833001 	add	r3, r3, #1
     420:	e50b300c 	str	r3, [fp, #-12]
     424:	e51b3008 	ldr	r3, [fp, #-8]
     428:	e2833001 	add	r3, r3, #1
     42c:	e50b3008 	str	r3, [fp, #-8]
     430:	e51b300c 	ldr	r3, [fp, #-12]
     434:	e3530c02 	cmp	r3, #512	; 0x200
     438:	baffffed 	blt	0x3f4
     43c:	e51b2008 	ldr	r2, [fp, #-8]
     440:	e51b1018 	ldr	r1, [fp, #-24]	; 0xffffffe8
     444:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     448:	e0813003 	add	r3, r1, r3
     44c:	e1520003 	cmp	r2, r3
     450:	3affffc8 	bcc	0x378
     454:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     458:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     45c:	e5933000 	ldr	r3, [r3]
     460:	e3833b02 	orr	r3, r3, #2048	; 0x800
     464:	e5823000 	str	r3, [r2]
     468:	e1a00000 	nop			; (mov r0, r0)
     46c:	e24bd004 	sub	sp, fp, #4
     470:	e8bd8800 	pop	{fp, pc}
     474:	e92d4800 	push	{fp, lr}
     478:	e28db004 	add	fp, sp, #4
     47c:	e3a00000 	mov	r0, #0
     480:	e34303ff 	movt	r0, #13311	; 0x33ff
     484:	e3a01000 	mov	r1, #0
     488:	e3a02c02 	mov	r2, #512	; 0x200
     48c:	ebffff99 	bl	0x2f8
     490:	e8bd8800 	pop	{fp, pc}
     494:	e92d4800 	push	{fp, lr}
     498:	e28db004 	add	fp, sp, #4
     49c:	e3a00901 	mov	r0, #16384	; 0x4000
     4a0:	e3430000 	movt	r0, #12288	; 0x3000
     4a4:	e3a01000 	mov	r1, #0
     4a8:	e3a02a01 	mov	r2, #4096	; 0x1000
     4ac:	ebffff91 	bl	0x2f8
     4b0:	e8bd8800 	pop	{fp, pc}
     4b4:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     4b8:	e28db000 	add	fp, sp, #0
     4bc:	e3a02050 	mov	r2, #80	; 0x50
     4c0:	e3452600 	movt	r2, #22016	; 0x5600
     4c4:	e3a03050 	mov	r3, #80	; 0x50
     4c8:	e3453600 	movt	r3, #22016	; 0x5600
     4cc:	e5933000 	ldr	r3, [r3]
     4d0:	e3833902 	orr	r3, r3, #32768	; 0x8000
     4d4:	e38330a8 	orr	r3, r3, #168	; 0xa8
     4d8:	e5823000 	str	r3, [r2]
     4dc:	e3a03058 	mov	r3, #88	; 0x58
     4e0:	e3453600 	movt	r3, #22016	; 0x5600
     4e4:	e3a02058 	mov	r2, #88	; 0x58
     4e8:	e3452600 	movt	r2, #22016	; 0x5600
     4ec:	e5922000 	ldr	r2, [r2]
     4f0:	e382208e 	orr	r2, r2, #142	; 0x8e
     4f4:	e5832000 	str	r2, [r3]
     4f8:	e3a030a4 	mov	r3, #164	; 0xa4
     4fc:	e3453600 	movt	r3, #22016	; 0x5600
     500:	e3a020a4 	mov	r2, #164	; 0xa4
     504:	e3452600 	movt	r2, #22016	; 0x5600
     508:	e5922000 	ldr	r2, [r2]
     50c:	e3c22080 	bic	r2, r2, #128	; 0x80
     510:	e5832000 	str	r2, [r3]
     514:	e3a03008 	mov	r3, #8
     518:	e3443a00 	movt	r3, #18944	; 0x4a00
     51c:	e3a02008 	mov	r2, #8
     520:	e3442a00 	movt	r2, #18944	; 0x4a00
     524:	e5922000 	ldr	r2, [r2]
     528:	e3c2201e 	bic	r2, r2, #30
     52c:	e5832000 	str	r2, [r3]
     530:	e3a0300c 	mov	r3, #12
     534:	e3443a00 	movt	r3, #18944	; 0x4a00
     538:	e3a0200c 	mov	r2, #12
     53c:	e3442a00 	movt	r2, #18944	; 0x4a00
     540:	e5922000 	ldr	r2, [r2]
     544:	e3c22003 	bic	r2, r2, #3
     548:	e5832000 	str	r2, [r3]
     54c:	e24bd000 	sub	sp, fp, #0
     550:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     554:	e12fff1e 	bx	lr
     558:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     55c:	e28db000 	add	fp, sp, #0
     560:	e3033000 	movw	r3, #12288	; 0x3000
     564:	e3403000 	movt	r3, #0
     568:	e5932000 	ldr	r2, [r3]
     56c:	e306360d 	movw	r3, #26125	; 0x660d
     570:	e3403019 	movt	r3, #25
     574:	e0020293 	mul	r2, r3, r2
     578:	e30f335f 	movw	r3, #62303	; 0xf35f
     57c:	e3433c6e 	movt	r3, #15470	; 0x3c6e
     580:	e0823003 	add	r3, r2, r3
     584:	e3032000 	movw	r2, #12288	; 0x3000
     588:	e3402000 	movt	r2, #0
     58c:	e5823000 	str	r3, [r2]
     590:	e3033000 	movw	r3, #12288	; 0x3000
     594:	e3403000 	movt	r3, #0
     598:	e5933000 	ldr	r3, [r3]
     59c:	e1a032a3 	lsr	r3, r3, #5
     5a0:	e1a00003 	mov	r0, r3
     5a4:	e24bd000 	sub	sp, fp, #0
     5a8:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     5ac:	e12fff1e 	bx	lr
     5b0:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     5b4:	e28db000 	add	fp, sp, #0
     5b8:	e24dd00c 	sub	sp, sp, #12
     5bc:	e50b0008 	str	r0, [fp, #-8]
     5c0:	ea000002 	b	0x5d0
     5c4:	e51b3008 	ldr	r3, [fp, #-8]
     5c8:	e2433001 	sub	r3, r3, #1
     5cc:	e50b3008 	str	r3, [fp, #-8]
     5d0:	e51b3008 	ldr	r3, [fp, #-8]
     5d4:	e3530000 	cmp	r3, #0
     5d8:	1afffff9 	bne	0x5c4
     5dc:	e24bd000 	sub	sp, fp, #0
     5e0:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     5e4:	e12fff1e 	bx	lr
     5e8:	e92d4800 	push	{fp, lr}
     5ec:	e28db004 	add	fp, sp, #4
     5f0:	e24dd008 	sub	sp, sp, #8
     5f4:	e3a03000 	mov	r3, #0
     5f8:	e50b3008 	str	r3, [fp, #-8]
     5fc:	e3a03000 	mov	r3, #0
     600:	e50b300c 	str	r3, [fp, #-12]
     604:	ebffffd3 	bl	0x558
     608:	e3a03010 	mov	r3, #16
     60c:	e3453600 	movt	r3, #22016	; 0x5600
     610:	e3a02955 	mov	r2, #1392640	; 0x154000
     614:	e5832000 	str	r2, [r3]
     618:	eb00000b 	bl	0x64c
     61c:	e30806a0 	movw	r0, #34464	; 0x86a0
     620:	e3400001 	movt	r0, #1
     624:	ebffffe1 	bl	0x5b0
     628:	e3a03014 	mov	r3, #20
     62c:	e3453600 	movt	r3, #22016	; 0x5600
     630:	e51b2008 	ldr	r2, [fp, #-8]
     634:	e2821001 	add	r1, r2, #1
     638:	e50b1008 	str	r1, [fp, #-8]
     63c:	e1a02382 	lsl	r2, r2, #7
     640:	e1e02002 	mvn	r2, r2
     644:	e5832000 	str	r2, [r3]
     648:	eafffff3 	b	0x61c
     64c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     650:	e28db000 	add	fp, sp, #0
     654:	e3a03070 	mov	r3, #112	; 0x70
     658:	e3453600 	movt	r3, #22016	; 0x5600
     65c:	e3a02070 	mov	r2, #112	; 0x70
     660:	e3452600 	movt	r2, #22016	; 0x5600
     664:	e5922000 	ldr	r2, [r2]
     668:	e38220a0 	orr	r2, r2, #160	; 0xa0
     66c:	e5832000 	str	r2, [r3]
     670:	e3a03078 	mov	r3, #120	; 0x78
     674:	e3453600 	movt	r3, #22016	; 0x5600
     678:	e3a0200c 	mov	r2, #12
     67c:	e5832000 	str	r2, [r3]
     680:	e3a03205 	mov	r3, #1342177280	; 0x50000000
     684:	e3a02003 	mov	r2, #3
     688:	e5832000 	str	r2, [r3]
     68c:	e3a03245 	mov	r3, #1342177284	; 0x50000004
     690:	e3a02005 	mov	r2, #5
     694:	e5832000 	str	r2, [r3]
     698:	e3a03285 	mov	r3, #1342177288	; 0x50000008
     69c:	e3a02000 	mov	r2, #0
     6a0:	e5832000 	str	r2, [r3]
     6a4:	e3a032c5 	mov	r3, #1342177292	; 0x5000000c
     6a8:	e3a02000 	mov	r2, #0
     6ac:	e5832000 	str	r2, [r3]
     6b0:	e3a03028 	mov	r3, #40	; 0x28
     6b4:	e3453000 	movt	r3, #20480	; 0x5000
     6b8:	e3a0200c 	mov	r2, #12
     6bc:	e5832000 	str	r2, [r3]
     6c0:	e24bd000 	sub	sp, fp, #0
     6c4:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     6c8:	e12fff1e 	bx	lr
     6cc:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     6d0:	e28db000 	add	fp, sp, #0
     6d4:	e24dd00c 	sub	sp, sp, #12
     6d8:	e1a03000 	mov	r3, r0
     6dc:	e54b3005 	strb	r3, [fp, #-5]
     6e0:	e1a00000 	nop			; (mov r0, r0)
     6e4:	e3a03010 	mov	r3, #16
     6e8:	e3453000 	movt	r3, #20480	; 0x5000
     6ec:	e5933000 	ldr	r3, [r3]
     6f0:	e2033004 	and	r3, r3, #4
     6f4:	e3530000 	cmp	r3, #0
     6f8:	0afffff9 	beq	0x6e4
     6fc:	e3a03020 	mov	r3, #32
     700:	e3453000 	movt	r3, #20480	; 0x5000
     704:	e55b2005 	ldrb	r2, [fp, #-5]
     708:	e5c32000 	strb	r2, [r3]
     70c:	e24bd000 	sub	sp, fp, #0
     710:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     714:	e12fff1e 	bx	lr
     718:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     71c:	e28db000 	add	fp, sp, #0
     720:	e1a00000 	nop			; (mov r0, r0)
     724:	e3a03010 	mov	r3, #16
     728:	e3453000 	movt	r3, #20480	; 0x5000
     72c:	e5933000 	ldr	r3, [r3]
     730:	e2033001 	and	r3, r3, #1
     734:	e3530000 	cmp	r3, #0
     738:	0afffff9 	beq	0x724
     73c:	e3a03024 	mov	r3, #36	; 0x24
     740:	e3453000 	movt	r3, #20480	; 0x5000
     744:	e5d33000 	ldrb	r3, [r3]
     748:	e6ef3073 	uxtb	r3, r3
     74c:	e1a00003 	mov	r0, r3
     750:	e24bd000 	sub	sp, fp, #0
     754:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     758:	e12fff1e 	bx	lr
     75c:	e92d4800 	push	{fp, lr}
     760:	e28db004 	add	fp, sp, #4
     764:	e24dd010 	sub	sp, sp, #16
     768:	e50b0010 	str	r0, [fp, #-16]
     76c:	e3a03000 	mov	r3, #0
     770:	e50b3008 	str	r3, [fp, #-8]
     774:	ea000008 	b	0x79c
     778:	e51b3008 	ldr	r3, [fp, #-8]
     77c:	e2832001 	add	r2, r3, #1
     780:	e50b2008 	str	r2, [fp, #-8]
     784:	e1a02003 	mov	r2, r3
     788:	e51b3010 	ldr	r3, [fp, #-16]
     78c:	e0833002 	add	r3, r3, r2
     790:	e5d33000 	ldrb	r3, [r3]
     794:	e1a00003 	mov	r0, r3
     798:	ebffffcb 	bl	0x6cc
     79c:	e51b3008 	ldr	r3, [fp, #-8]
     7a0:	e51b2010 	ldr	r2, [fp, #-16]
     7a4:	e0823003 	add	r3, r2, r3
     7a8:	e5d33000 	ldrb	r3, [r3]
     7ac:	e3530000 	cmp	r3, #0
     7b0:	1afffff0 	bne	0x778
     7b4:	e24bd004 	sub	sp, fp, #4
     7b8:	e8bd8800 	pop	{fp, pc}
     7bc:	e92d4800 	push	{fp, lr}
     7c0:	e28db004 	add	fp, sp, #4
     7c4:	e24dd008 	sub	sp, sp, #8
     7c8:	e3a03014 	mov	r3, #20
     7cc:	e3443a00 	movt	r3, #18944	; 0x4a00
     7d0:	e5933000 	ldr	r3, [r3]
     7d4:	e50b3008 	str	r3, [fp, #-8]
     7d8:	e51b3008 	ldr	r3, [fp, #-8]
     7dc:	e2433001 	sub	r3, r3, #1
     7e0:	e3530003 	cmp	r3, #3
     7e4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     7e8:	ea000013 	b	0x83c
     7ec:	000007fc 	strdeq	r0, [r0], -ip
     7f0:	0000080c 	andeq	r0, r0, ip, lsl #16
     7f4:	0000081c 	andeq	r0, r0, ip, lsl r8
     7f8:	0000082c 	andeq	r0, r0, ip, lsr #16
     7fc:	e3000a0c 	movw	r0, #2572	; 0xa0c
     800:	e3400000 	movt	r0, #0
     804:	ebffffd4 	bl	0x75c
     808:	ea00000f 	b	0x84c
     80c:	e3000a24 	movw	r0, #2596	; 0xa24
     810:	e3400000 	movt	r0, #0
     814:	ebffffd0 	bl	0x75c
     818:	ea00000b 	b	0x84c
     81c:	e3000a3c 	movw	r0, #2620	; 0xa3c
     820:	e3400000 	movt	r0, #0
     824:	ebffffcc 	bl	0x75c
     828:	ea000007 	b	0x84c
     82c:	e3000a54 	movw	r0, #2644	; 0xa54
     830:	e3400000 	movt	r0, #0
     834:	ebffffc8 	bl	0x75c
     838:	ea000003 	b	0x84c
     83c:	e3000a6c 	movw	r0, #2668	; 0xa6c
     840:	e3400000 	movt	r0, #0
     844:	ebffffc4 	bl	0x75c
     848:	e1a00000 	nop			; (mov r0, r0)
     84c:	e51b3008 	ldr	r3, [fp, #-8]
     850:	e3530004 	cmp	r3, #4
     854:	1a000003 	bne	0x868
     858:	e3a030a8 	mov	r3, #168	; 0xa8
     85c:	e3453600 	movt	r3, #22016	; 0x5600
     860:	e3a02080 	mov	r2, #128	; 0x80
     864:	e5832000 	str	r2, [r3]
     868:	e3a0244a 	mov	r2, #1241513984	; 0x4a000000
     86c:	e51b3008 	ldr	r3, [fp, #-8]
     870:	e3a01001 	mov	r1, #1
     874:	e1a03311 	lsl	r3, r1, r3
     878:	e5823000 	str	r3, [r2]
     87c:	e3a03010 	mov	r3, #16
     880:	e3443a00 	movt	r3, #18944	; 0x4a00
     884:	e3a02010 	mov	r2, #16
     888:	e3442a00 	movt	r2, #18944	; 0x4a00
     88c:	e5922000 	ldr	r2, [r2]
     890:	e5832000 	str	r2, [r3]
     894:	e24bd004 	sub	sp, fp, #4
     898:	e8bd8800 	pop	{fp, pc}
     89c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     8a0:	e28db000 	add	fp, sp, #0
     8a4:	e24dd00c 	sub	sp, sp, #12
     8a8:	e3a03203 	mov	r3, #805306368	; 0x30000000
     8ac:	e50b3008 	str	r3, [fp, #-8]
     8b0:	ea00000d 	b	0x8ec
     8b4:	e3043004 	movw	r3, #16388	; 0x4004
     8b8:	e3403000 	movt	r3, #0
     8bc:	e5932000 	ldr	r2, [r3]
     8c0:	e51b3008 	ldr	r3, [fp, #-8]
     8c4:	e1a03a23 	lsr	r3, r3, #20
     8c8:	e1a03103 	lsl	r3, r3, #2
     8cc:	e0822003 	add	r2, r2, r3
     8d0:	e51b3008 	ldr	r3, [fp, #-8]
     8d4:	e3833ec1 	orr	r3, r3, #3088	; 0xc10
     8d8:	e383300a 	orr	r3, r3, #10
     8dc:	e5823000 	str	r3, [r2]
     8e0:	e51b3008 	ldr	r3, [fp, #-8]
     8e4:	e2833601 	add	r3, r3, #1048576	; 0x100000
     8e8:	e50b3008 	str	r3, [fp, #-8]
     8ec:	e51b3008 	ldr	r3, [fp, #-8]
     8f0:	e3730373 	cmn	r3, #-872415231	; 0xcc000001
     8f4:	9affffee 	bls	0x8b4
     8f8:	e3a03312 	mov	r3, #1207959552	; 0x48000000
     8fc:	e50b3008 	str	r3, [fp, #-8]
     900:	ea00000d 	b	0x93c
     904:	e3043004 	movw	r3, #16388	; 0x4004
     908:	e3403000 	movt	r3, #0
     90c:	e5932000 	ldr	r2, [r3]
     910:	e51b3008 	ldr	r3, [fp, #-8]
     914:	e1a03a23 	lsr	r3, r3, #20
     918:	e1a03103 	lsl	r3, r3, #2
     91c:	e0822003 	add	r2, r2, r3
     920:	e51b3008 	ldr	r3, [fp, #-8]
     924:	e3833ec1 	orr	r3, r3, #3088	; 0xc10
     928:	e3833002 	orr	r3, r3, #2
     92c:	e5823000 	str	r3, [r2]
     930:	e51b3008 	ldr	r3, [fp, #-8]
     934:	e2833601 	add	r3, r3, #1048576	; 0x100000
     938:	e50b3008 	str	r3, [fp, #-8]
     93c:	e51b3008 	ldr	r3, [fp, #-8]
     940:	e373021a 	cmn	r3, #-1610612735	; 0xa0000001
     944:	9affffee 	bls	0x904
     948:	e3043004 	movw	r3, #16388	; 0x4004
     94c:	e3403000 	movt	r3, #0
     950:	e5933000 	ldr	r3, [r3]
     954:	e2833dff 	add	r3, r3, #16320	; 0x3fc0
     958:	e283303c 	add	r3, r3, #60	; 0x3c
     95c:	e3002c1a 	movw	r2, #3098	; 0xc1a
     960:	e34323f0 	movt	r2, #13296	; 0x33f0
     964:	e5832000 	str	r2, [r3]
     968:	e24bd000 	sub	sp, fp, #0
     96c:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     970:	e12fff1e 	bx	lr
     974:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     978:	e28db000 	add	fp, sp, #0
     97c:	e24dd00c 	sub	sp, sp, #12
     980:	e3a03203 	mov	r3, #805306368	; 0x30000000
     984:	e50b3008 	str	r3, [fp, #-8]
     988:	e51b3008 	ldr	r3, [fp, #-8]
     98c:	e3a00000 	mov	r0, #0
     990:	ee070f17 	mcr	15, 0, r0, cr7, cr7, {0}
     994:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
     998:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
     99c:	e1a04003 	mov	r4, r3
     9a0:	ee024f10 	mcr	15, 0, r4, cr2, cr0, {0}
     9a4:	e3e00000 	mvn	r0, #0
     9a8:	ee030f10 	mcr	15, 0, r0, cr3, cr0, {0}
     9ac:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
     9b0:	e59f101c 	ldr	r1, [pc, #28]	; 0x9d4
     9b4:	e1c00001 	bic	r0, r0, r1
     9b8:	e3800a02 	orr	r0, r0, #8192	; 0x2000
     9bc:	e3800002 	orr	r0, r0, #2
     9c0:	e3800001 	orr	r0, r0, #1
     9c4:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
     9c8:	e24bd000 	sub	sp, fp, #0
     9cc:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     9d0:	e12fff1e 	bx	lr
     9d4:	00001384 	andeq	r1, r0, r4, lsl #7
     9d8:	22111110 	andscs	r1, r1, #16, 2
     9dc:	00000700 	andeq	r0, r0, r0, lsl #14
     9e0:	00000700 	andeq	r0, r0, r0, lsl #14
     9e4:	00000700 	andeq	r0, r0, r0, lsl #14
     9e8:	00000700 	andeq	r0, r0, r0, lsl #14
     9ec:	00000700 	andeq	r0, r0, r0, lsl #14
     9f0:	00000700 	andeq	r0, r0, r0, lsl #14
     9f4:	00018005 	andeq	r8, r1, r5
     9f8:	00018005 	andeq	r8, r1, r5
     9fc:	008e07a3 	addeq	r0, lr, r3, lsr #15
     a00:	000000b2 	strheq	r0, [r0], -r2
     a04:	00000030 	andeq	r0, r0, r0, lsr r0
     a08:	00000030 	andeq	r0, r0, r0, lsr r0
     a0c:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a10:	4b202c31 	blmi	0x80badc
     a14:	72702031 	rsbsvc	r2, r0, #49	; 0x31
     a18:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a1c:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a20:	00000000 	andeq	r0, r0, r0
     a24:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a28:	4b202c32 	blmi	0x80baf8
     a2c:	72702032 	rsbsvc	r2, r0, #50	; 0x32
     a30:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a34:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a38:	00000000 	andeq	r0, r0, r0
     a3c:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a40:	4b202c33 	blmi	0x80bb14
     a44:	72702033 	rsbsvc	r2, r0, #51	; 0x33
     a48:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a4c:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a50:	00000000 	andeq	r0, r0, r0
     a54:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a58:	4b202c37 	blmi	0x80bb3c
     a5c:	72702034 	rsbsvc	r2, r0, #52	; 0x34
     a60:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a64:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a68:	00000000 	andeq	r0, r0, r0
     a6c:	65746e49 	ldrbvs	r6, [r4, #-3657]!	; 0xfffff1b7
     a70:	70757272 	rsbsvc	r7, r5, r2, ror r2
     a74:	6e752074 	mrcvs	0, 3, r2, cr5, cr4, {3}
     a78:	776f6e6b 	strbvc	r6, [pc, -fp, ror #28]!
     a7c:	0d0a216e 	stfeqs	f2, [sl, #-440]	; 0xfffffe48
	...
    8000:	12345678 	eorsne	r5, r4, #120, 12	; 0x7800000
    8004:	30000000 	andcc	r0, r0, r0
