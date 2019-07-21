
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
      2c:	eb00003e 	bl	0x12c
      30:	eb000095 	bl	0x28c
      34:	eb000114 	bl	0x48c
      38:	eb00011c 	bl	0x4b0
      3c:	e59fd040 	ldr	sp, [pc, #64]	; 0x84
      40:	e59ff040 	ldr	pc, [pc, #64]	; 0x88
      44:	eb000219 	bl	0x8b0
      48:	eb00024d 	bl	0x984
      4c:	e321f0d2 	msr	CPSR_c, #210	; 0xd2
      50:	e3a0d433 	mov	sp, #855638016	; 0x33000000
      54:	e321f0df 	msr	CPSR_c, #223	; 0xdf
      58:	e59fd024 	ldr	sp, [pc, #36]	; 0x84
      5c:	eb00011c 	bl	0x4d4
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
      90:	000005f4 	strdeq	r0, [r0], -r4
      94:	00000080 	andeq	r0, r0, r0, lsl #1
      98:	000007d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
      9c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
      a0:	e28db000 	add	fp, sp, #0
      a4:	e3a03453 	mov	r3, #1392508928	; 0x53000000
      a8:	e3a02000 	mov	r2, #0
      ac:	e5832000 	str	r2, [r3]
      b0:	e1a00000 	nop			; (mov r0, r0)
      b4:	e28bd000 	add	sp, fp, #0
      b8:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
      bc:	e12fff1e 	bx	lr
      c0:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
      c4:	e28db000 	add	fp, sp, #0
      c8:	e24dd00c 	sub	sp, sp, #12
      cc:	e3a03000 	mov	r3, #0
      d0:	e50b300c 	str	r3, [fp, #-12]
      d4:	e3a03312 	mov	r3, #1207959552	; 0x48000000
      d8:	e50b3008 	str	r3, [fp, #-8]
      dc:	ea00000a 	b	0x10c
      e0:	e51b300c 	ldr	r3, [fp, #-12]
      e4:	e1a03103 	lsl	r3, r3, #2
      e8:	e51b2008 	ldr	r2, [fp, #-8]
      ec:	e0823003 	add	r3, r2, r3
      f0:	e59f1030 	ldr	r1, [pc, #48]	; 0x128
      f4:	e51b200c 	ldr	r2, [fp, #-12]
      f8:	e7912102 	ldr	r2, [r1, r2, lsl #2]
      fc:	e5832000 	str	r2, [r3]
     100:	e51b300c 	ldr	r3, [fp, #-12]
     104:	e2833001 	add	r3, r3, #1
     108:	e50b300c 	str	r3, [fp, #-12]
     10c:	e51b300c 	ldr	r3, [fp, #-12]
     110:	e353000c 	cmp	r3, #12
     114:	dafffff1 	ble	0xe0
     118:	e1a00000 	nop			; (mov r0, r0)
     11c:	e28bd000 	add	sp, fp, #0
     120:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     124:	e12fff1e 	bx	lr
     128:	000009ec 	andeq	r0, r0, ip, ror #19
     12c:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     130:	e28db000 	add	fp, sp, #0
     134:	e24dd00c 	sub	sp, sp, #12
     138:	e3a03312 	mov	r3, #1207959552	; 0x48000000
     13c:	e50b3008 	str	r3, [fp, #-8]
     140:	e51b3008 	ldr	r3, [fp, #-8]
     144:	e59f20d0 	ldr	r2, [pc, #208]	; 0x21c
     148:	e5832000 	str	r2, [r3]
     14c:	e51b3008 	ldr	r3, [fp, #-8]
     150:	e2833004 	add	r3, r3, #4
     154:	e3a02c07 	mov	r2, #1792	; 0x700
     158:	e5832000 	str	r2, [r3]
     15c:	e51b3008 	ldr	r3, [fp, #-8]
     160:	e2833008 	add	r3, r3, #8
     164:	e3a02c07 	mov	r2, #1792	; 0x700
     168:	e5832000 	str	r2, [r3]
     16c:	e51b3008 	ldr	r3, [fp, #-8]
     170:	e283300c 	add	r3, r3, #12
     174:	e3a02c07 	mov	r2, #1792	; 0x700
     178:	e5832000 	str	r2, [r3]
     17c:	e51b3008 	ldr	r3, [fp, #-8]
     180:	e2833010 	add	r3, r3, #16
     184:	e3a02c07 	mov	r2, #1792	; 0x700
     188:	e5832000 	str	r2, [r3]
     18c:	e51b3008 	ldr	r3, [fp, #-8]
     190:	e2833014 	add	r3, r3, #20
     194:	e3a02c07 	mov	r2, #1792	; 0x700
     198:	e5832000 	str	r2, [r3]
     19c:	e51b3008 	ldr	r3, [fp, #-8]
     1a0:	e2833018 	add	r3, r3, #24
     1a4:	e3a02c07 	mov	r2, #1792	; 0x700
     1a8:	e5832000 	str	r2, [r3]
     1ac:	e51b3008 	ldr	r3, [fp, #-8]
     1b0:	e283301c 	add	r3, r3, #28
     1b4:	e59f2064 	ldr	r2, [pc, #100]	; 0x220
     1b8:	e5832000 	str	r2, [r3]
     1bc:	e51b3008 	ldr	r3, [fp, #-8]
     1c0:	e2833020 	add	r3, r3, #32
     1c4:	e59f2054 	ldr	r2, [pc, #84]	; 0x220
     1c8:	e5832000 	str	r2, [r3]
     1cc:	e51b3008 	ldr	r3, [fp, #-8]
     1d0:	e2833024 	add	r3, r3, #36	; 0x24
     1d4:	e59f2048 	ldr	r2, [pc, #72]	; 0x224
     1d8:	e5832000 	str	r2, [r3]
     1dc:	e51b3008 	ldr	r3, [fp, #-8]
     1e0:	e2833028 	add	r3, r3, #40	; 0x28
     1e4:	e3a020b2 	mov	r2, #178	; 0xb2
     1e8:	e5832000 	str	r2, [r3]
     1ec:	e51b3008 	ldr	r3, [fp, #-8]
     1f0:	e283302c 	add	r3, r3, #44	; 0x2c
     1f4:	e3a02030 	mov	r2, #48	; 0x30
     1f8:	e5832000 	str	r2, [r3]
     1fc:	e51b3008 	ldr	r3, [fp, #-8]
     200:	e2833030 	add	r3, r3, #48	; 0x30
     204:	e3a02030 	mov	r2, #48	; 0x30
     208:	e5832000 	str	r2, [r3]
     20c:	e1a00000 	nop			; (mov r0, r0)
     210:	e28bd000 	add	sp, fp, #0
     214:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     218:	e12fff1e 	bx	lr
     21c:	22111110 	andscs	r1, r1, #16, 2
     220:	00018005 	andeq	r8, r1, r5
     224:	008e07a3 	addeq	r0, lr, r3, lsr #15
     228:	e92d4800 	push	{fp, lr}
     22c:	e28db004 	add	fp, sp, #4
     230:	e24dd008 	sub	sp, sp, #8
     234:	e3a03000 	mov	r3, #0
     238:	e50b3008 	str	r3, [fp, #-8]
     23c:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     240:	e5933000 	ldr	r3, [r3]
     244:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     248:	e3c33b02 	bic	r3, r3, #2048	; 0x800
     24c:	e5823000 	str	r3, [r2]
     250:	ea000002 	b	0x260
     254:	e51b3008 	ldr	r3, [fp, #-8]
     258:	e2833001 	add	r3, r3, #1
     25c:	e50b3008 	str	r3, [fp, #-8]
     260:	e51b3008 	ldr	r3, [fp, #-8]
     264:	e3530009 	cmp	r3, #9
     268:	dafffff9 	ble	0x254
     26c:	e59f3014 	ldr	r3, [pc, #20]	; 0x288
     270:	e3e02000 	mvn	r2, #0
     274:	e5c32000 	strb	r2, [r3]
     278:	eb00000c 	bl	0x2b0
     27c:	e1a00000 	nop			; (mov r0, r0)
     280:	e24bd004 	sub	sp, fp, #4
     284:	e8bd8800 	pop	{fp, pc}
     288:	4e000004 	cdpmi	0, 0, cr0, cr0, cr4, {0}
     28c:	e92d4800 	push	{fp, lr}
     290:	e28db004 	add	fp, sp, #4
     294:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     298:	e59f200c 	ldr	r2, [pc, #12]	; 0x2ac
     29c:	e5832000 	str	r2, [r3]
     2a0:	ebffffe0 	bl	0x228
     2a4:	e1a00000 	nop			; (mov r0, r0)
     2a8:	e8bd8800 	pop	{fp, pc}
     2ac:	0000f830 	andeq	pc, r0, r0, lsr r8	; <UNPREDICTABLE>
     2b0:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     2b4:	e28db000 	add	fp, sp, #0
     2b8:	e24dd00c 	sub	sp, sp, #12
     2bc:	ea000008 	b	0x2e4
     2c0:	e3a03000 	mov	r3, #0
     2c4:	e50b3008 	str	r3, [fp, #-8]
     2c8:	ea000002 	b	0x2d8
     2cc:	e51b3008 	ldr	r3, [fp, #-8]
     2d0:	e2833001 	add	r3, r3, #1
     2d4:	e50b3008 	str	r3, [fp, #-8]
     2d8:	e51b3008 	ldr	r3, [fp, #-8]
     2dc:	e3530009 	cmp	r3, #9
     2e0:	dafffff9 	ble	0x2cc
     2e4:	e59f3020 	ldr	r3, [pc, #32]	; 0x30c
     2e8:	e5d33000 	ldrb	r3, [r3]
     2ec:	e20330ff 	and	r3, r3, #255	; 0xff
     2f0:	e2033001 	and	r3, r3, #1
     2f4:	e3530000 	cmp	r3, #0
     2f8:	0afffff0 	beq	0x2c0
     2fc:	e1a00000 	nop			; (mov r0, r0)
     300:	e28bd000 	add	sp, fp, #0
     304:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     308:	e12fff1e 	bx	lr
     30c:	4e000010 	mcrmi	0, 0, r0, cr0, cr0, {0}
     310:	e92d4800 	push	{fp, lr}
     314:	e28db004 	add	fp, sp, #4
     318:	e24dd018 	sub	sp, sp, #24
     31c:	e50b0010 	str	r0, [fp, #-16]
     320:	e50b1014 	str	r1, [fp, #-20]	; 0xffffffec
     324:	e50b2018 	str	r2, [fp, #-24]	; 0xffffffe8
     328:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     32c:	e1a03b83 	lsl	r3, r3, #23
     330:	e1a03ba3 	lsr	r3, r3, #23
     334:	e3530000 	cmp	r3, #0
     338:	1a00004d 	bne	0x474
     33c:	e51b3018 	ldr	r3, [fp, #-24]	; 0xffffffe8
     340:	e1a03b83 	lsl	r3, r3, #23
     344:	e1a03ba3 	lsr	r3, r3, #23
     348:	e3530000 	cmp	r3, #0
     34c:	1a000048 	bne	0x474
     350:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     354:	e5933000 	ldr	r3, [r3]
     358:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     35c:	e3c33b02 	bic	r3, r3, #2048	; 0x800
     360:	e5823000 	str	r3, [r2]
     364:	e3a03000 	mov	r3, #0
     368:	e50b300c 	str	r3, [fp, #-12]
     36c:	ea000002 	b	0x37c
     370:	e51b300c 	ldr	r3, [fp, #-12]
     374:	e2833001 	add	r3, r3, #1
     378:	e50b300c 	str	r3, [fp, #-12]
     37c:	e51b300c 	ldr	r3, [fp, #-12]
     380:	e3530009 	cmp	r3, #9
     384:	dafffff9 	ble	0x370
     388:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     38c:	e50b300c 	str	r3, [fp, #-12]
     390:	ea00002a 	b	0x440
     394:	e59f30e4 	ldr	r3, [pc, #228]	; 0x480
     398:	e3a02000 	mov	r2, #0
     39c:	e5c32000 	strb	r2, [r3]
     3a0:	e59f20dc 	ldr	r2, [pc, #220]	; 0x484
     3a4:	e51b300c 	ldr	r3, [fp, #-12]
     3a8:	e20330ff 	and	r3, r3, #255	; 0xff
     3ac:	e5c23000 	strb	r3, [r2]
     3b0:	e51b300c 	ldr	r3, [fp, #-12]
     3b4:	e1a034c3 	asr	r3, r3, #9
     3b8:	e59f20c4 	ldr	r2, [pc, #196]	; 0x484
     3bc:	e20330ff 	and	r3, r3, #255	; 0xff
     3c0:	e5c23000 	strb	r3, [r2]
     3c4:	e51b300c 	ldr	r3, [fp, #-12]
     3c8:	e1a038c3 	asr	r3, r3, #17
     3cc:	e59f20b0 	ldr	r2, [pc, #176]	; 0x484
     3d0:	e20330ff 	and	r3, r3, #255	; 0xff
     3d4:	e5c23000 	strb	r3, [r2]
     3d8:	e51b300c 	ldr	r3, [fp, #-12]
     3dc:	e1a03cc3 	asr	r3, r3, #25
     3e0:	e59f209c 	ldr	r2, [pc, #156]	; 0x484
     3e4:	e20330ff 	and	r3, r3, #255	; 0xff
     3e8:	e5c23000 	strb	r3, [r2]
     3ec:	ebffffaf 	bl	0x2b0
     3f0:	e3a03000 	mov	r3, #0
     3f4:	e50b3008 	str	r3, [fp, #-8]
     3f8:	ea00000d 	b	0x434
     3fc:	e59f3084 	ldr	r3, [pc, #132]	; 0x488
     400:	e5d33000 	ldrb	r3, [r3]
     404:	e20320ff 	and	r2, r3, #255	; 0xff
     408:	e51b3010 	ldr	r3, [fp, #-16]
     40c:	e5c32000 	strb	r2, [r3]
     410:	e51b3010 	ldr	r3, [fp, #-16]
     414:	e2833001 	add	r3, r3, #1
     418:	e50b3010 	str	r3, [fp, #-16]
     41c:	e51b3008 	ldr	r3, [fp, #-8]
     420:	e2833001 	add	r3, r3, #1
     424:	e50b3008 	str	r3, [fp, #-8]
     428:	e51b300c 	ldr	r3, [fp, #-12]
     42c:	e2833001 	add	r3, r3, #1
     430:	e50b300c 	str	r3, [fp, #-12]
     434:	e51b3008 	ldr	r3, [fp, #-8]
     438:	e3530c02 	cmp	r3, #512	; 0x200
     43c:	baffffee 	blt	0x3fc
     440:	e51b2018 	ldr	r2, [fp, #-24]	; 0xffffffe8
     444:	e51b3014 	ldr	r3, [fp, #-20]	; 0xffffffec
     448:	e0822003 	add	r2, r2, r3
     44c:	e51b300c 	ldr	r3, [fp, #-12]
     450:	e1520003 	cmp	r2, r3
     454:	8affffce 	bhi	0x394
     458:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
     45c:	e5933000 	ldr	r3, [r3]
     460:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
     464:	e3833b02 	orr	r3, r3, #2048	; 0x800
     468:	e5823000 	str	r3, [r2]
     46c:	e1a00000 	nop			; (mov r0, r0)
     470:	ea000000 	b	0x478
     474:	e1a00000 	nop			; (mov r0, r0)
     478:	e24bd004 	sub	sp, fp, #4
     47c:	e8bd8800 	pop	{fp, pc}
     480:	4e000004 	cdpmi	0, 0, cr0, cr0, cr4, {0}
     484:	4e000008 	cdpmi	0, 0, cr0, cr0, cr8, {0}
     488:	4e00000c 	cdpmi	0, 0, cr0, cr0, cr12, {0}
     48c:	e92d4800 	push	{fp, lr}
     490:	e28db004 	add	fp, sp, #4
     494:	e3a02c02 	mov	r2, #512	; 0x200
     498:	e3a01000 	mov	r1, #0
     49c:	e59f0008 	ldr	r0, [pc, #8]	; 0x4ac
     4a0:	ebffff9a 	bl	0x310
     4a4:	e1a00000 	nop			; (mov r0, r0)
     4a8:	e8bd8800 	pop	{fp, pc}
     4ac:	33ff0000 	mvnscc	r0, #0
     4b0:	e92d4800 	push	{fp, lr}
     4b4:	e28db004 	add	fp, sp, #4
     4b8:	e3a02a01 	mov	r2, #4096	; 0x1000
     4bc:	e3a01000 	mov	r1, #0
     4c0:	e59f0008 	ldr	r0, [pc, #8]	; 0x4d0
     4c4:	ebffff91 	bl	0x310
     4c8:	e1a00000 	nop			; (mov r0, r0)
     4cc:	e8bd8800 	pop	{fp, pc}
     4d0:	30004000 	andcc	r4, r0, r0
     4d4:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     4d8:	e28db000 	add	fp, sp, #0
     4dc:	e59f3070 	ldr	r3, [pc, #112]	; 0x554
     4e0:	e5933000 	ldr	r3, [r3]
     4e4:	e59f2068 	ldr	r2, [pc, #104]	; 0x554
     4e8:	e3833902 	orr	r3, r3, #32768	; 0x8000
     4ec:	e38330a8 	orr	r3, r3, #168	; 0xa8
     4f0:	e5823000 	str	r3, [r2]
     4f4:	e59f305c 	ldr	r3, [pc, #92]	; 0x558
     4f8:	e5933000 	ldr	r3, [r3]
     4fc:	e59f2054 	ldr	r2, [pc, #84]	; 0x558
     500:	e383308e 	orr	r3, r3, #142	; 0x8e
     504:	e5823000 	str	r3, [r2]
     508:	e59f304c 	ldr	r3, [pc, #76]	; 0x55c
     50c:	e5933000 	ldr	r3, [r3]
     510:	e59f2044 	ldr	r2, [pc, #68]	; 0x55c
     514:	e3c33080 	bic	r3, r3, #128	; 0x80
     518:	e5823000 	str	r3, [r2]
     51c:	e59f303c 	ldr	r3, [pc, #60]	; 0x560
     520:	e5933000 	ldr	r3, [r3]
     524:	e59f2034 	ldr	r2, [pc, #52]	; 0x560
     528:	e3c3301e 	bic	r3, r3, #30
     52c:	e5823000 	str	r3, [r2]
     530:	e59f302c 	ldr	r3, [pc, #44]	; 0x564
     534:	e5933000 	ldr	r3, [r3]
     538:	e59f2024 	ldr	r2, [pc, #36]	; 0x564
     53c:	e3c33003 	bic	r3, r3, #3
     540:	e5823000 	str	r3, [r2]
     544:	e1a00000 	nop			; (mov r0, r0)
     548:	e28bd000 	add	sp, fp, #0
     54c:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     550:	e12fff1e 	bx	lr
     554:	56000050 			; <UNDEFINED> instruction: 0x56000050
     558:	56000058 			; <UNDEFINED> instruction: 0x56000058
     55c:	560000a4 	strpl	r0, [r0], -r4, lsr #1
     560:	4a000008 	bmi	0x588
     564:	4a00000c 	bmi	0x59c
     568:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     56c:	e28db000 	add	fp, sp, #0
     570:	e59f3034 	ldr	r3, [pc, #52]	; 0x5ac
     574:	e5933000 	ldr	r3, [r3]
     578:	e59f2030 	ldr	r2, [pc, #48]	; 0x5b0
     57c:	e0010293 	mul	r1, r3, r2
     580:	e59f302c 	ldr	r3, [pc, #44]	; 0x5b4
     584:	e0813003 	add	r3, r1, r3
     588:	e59f201c 	ldr	r2, [pc, #28]	; 0x5ac
     58c:	e5823000 	str	r3, [r2]
     590:	e59f3014 	ldr	r3, [pc, #20]	; 0x5ac
     594:	e5933000 	ldr	r3, [r3]
     598:	e1a032a3 	lsr	r3, r3, #5
     59c:	e1a00003 	mov	r0, r3
     5a0:	e28bd000 	add	sp, fp, #0
     5a4:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     5a8:	e12fff1e 	bx	lr
     5ac:	00003000 	andeq	r3, r0, r0
     5b0:	0019660d 	andseq	r6, r9, sp, lsl #12
     5b4:	3c6ef35f 	stclcc	3, cr15, [lr], #-380	; 0xfffffe84
     5b8:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     5bc:	e28db000 	add	fp, sp, #0
     5c0:	e24dd00c 	sub	sp, sp, #12
     5c4:	e50b0008 	str	r0, [fp, #-8]
     5c8:	ea000002 	b	0x5d8
     5cc:	e51b3008 	ldr	r3, [fp, #-8]
     5d0:	e2433001 	sub	r3, r3, #1
     5d4:	e50b3008 	str	r3, [fp, #-8]
     5d8:	e51b3008 	ldr	r3, [fp, #-8]
     5dc:	e3530000 	cmp	r3, #0
     5e0:	1afffff9 	bne	0x5cc
     5e4:	e1a00000 	nop			; (mov r0, r0)
     5e8:	e28bd000 	add	sp, fp, #0
     5ec:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     5f0:	e12fff1e 	bx	lr
     5f4:	e92d4800 	push	{fp, lr}
     5f8:	e28db004 	add	fp, sp, #4
     5fc:	e24dd008 	sub	sp, sp, #8
     600:	e3a03000 	mov	r3, #0
     604:	e50b300c 	str	r3, [fp, #-12]
     608:	e3a03000 	mov	r3, #0
     60c:	e50b3008 	str	r3, [fp, #-8]
     610:	ebffffd4 	bl	0x568
     614:	e59f3030 	ldr	r3, [pc, #48]	; 0x64c
     618:	e3a02955 	mov	r2, #1392640	; 0x154000
     61c:	e5832000 	str	r2, [r3]
     620:	eb00000c 	bl	0x658
     624:	e59f0024 	ldr	r0, [pc, #36]	; 0x650
     628:	ebffffe2 	bl	0x5b8
     62c:	e51b300c 	ldr	r3, [fp, #-12]
     630:	e2832001 	add	r2, r3, #1
     634:	e50b200c 	str	r2, [fp, #-12]
     638:	e1a03383 	lsl	r3, r3, #7
     63c:	e59f2010 	ldr	r2, [pc, #16]	; 0x654
     640:	e1e03003 	mvn	r3, r3
     644:	e5823000 	str	r3, [r2]
     648:	eafffff5 	b	0x624
     64c:	56000010 			; <UNDEFINED> instruction: 0x56000010
     650:	000186a0 	andeq	r8, r1, r0, lsr #13
     654:	56000014 			; <UNDEFINED> instruction: 0x56000014
     658:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     65c:	e28db000 	add	fp, sp, #0
     660:	e59f3064 	ldr	r3, [pc, #100]	; 0x6cc
     664:	e5933000 	ldr	r3, [r3]
     668:	e59f205c 	ldr	r2, [pc, #92]	; 0x6cc
     66c:	e38330a0 	orr	r3, r3, #160	; 0xa0
     670:	e5823000 	str	r3, [r2]
     674:	e59f3054 	ldr	r3, [pc, #84]	; 0x6d0
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
     6b0:	e59f301c 	ldr	r3, [pc, #28]	; 0x6d4
     6b4:	e3a0200c 	mov	r2, #12
     6b8:	e5832000 	str	r2, [r3]
     6bc:	e1a00000 	nop			; (mov r0, r0)
     6c0:	e28bd000 	add	sp, fp, #0
     6c4:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     6c8:	e12fff1e 	bx	lr
     6cc:	56000070 			; <UNDEFINED> instruction: 0x56000070
     6d0:	56000078 			; <UNDEFINED> instruction: 0x56000078
     6d4:	50000028 	andpl	r0, r0, r8, lsr #32
     6d8:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     6dc:	e28db000 	add	fp, sp, #0
     6e0:	e24dd00c 	sub	sp, sp, #12
     6e4:	e1a03000 	mov	r3, r0
     6e8:	e54b3005 	strb	r3, [fp, #-5]
     6ec:	e1a00000 	nop			; (mov r0, r0)
     6f0:	e59f3028 	ldr	r3, [pc, #40]	; 0x720
     6f4:	e5933000 	ldr	r3, [r3]
     6f8:	e2033004 	and	r3, r3, #4
     6fc:	e3530000 	cmp	r3, #0
     700:	0afffffa 	beq	0x6f0
     704:	e59f2018 	ldr	r2, [pc, #24]	; 0x724
     708:	e55b3005 	ldrb	r3, [fp, #-5]
     70c:	e5c23000 	strb	r3, [r2]
     710:	e1a00000 	nop			; (mov r0, r0)
     714:	e28bd000 	add	sp, fp, #0
     718:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     71c:	e12fff1e 	bx	lr
     720:	50000010 	andpl	r0, r0, r0, lsl r0
     724:	50000020 	andpl	r0, r0, r0, lsr #32
     728:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     72c:	e28db000 	add	fp, sp, #0
     730:	e1a00000 	nop			; (mov r0, r0)
     734:	e59f3028 	ldr	r3, [pc, #40]	; 0x764
     738:	e5933000 	ldr	r3, [r3]
     73c:	e2033001 	and	r3, r3, #1
     740:	e3530000 	cmp	r3, #0
     744:	0afffffa 	beq	0x734
     748:	e59f3018 	ldr	r3, [pc, #24]	; 0x768
     74c:	e5d33000 	ldrb	r3, [r3]
     750:	e20330ff 	and	r3, r3, #255	; 0xff
     754:	e1a00003 	mov	r0, r3
     758:	e28bd000 	add	sp, fp, #0
     75c:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     760:	e12fff1e 	bx	lr
     764:	50000010 	andpl	r0, r0, r0, lsl r0
     768:	50000024 	andpl	r0, r0, r4, lsr #32
     76c:	e92d4800 	push	{fp, lr}
     770:	e28db004 	add	fp, sp, #4
     774:	e24dd010 	sub	sp, sp, #16
     778:	e50b0010 	str	r0, [fp, #-16]
     77c:	e3a03000 	mov	r3, #0
     780:	e50b3008 	str	r3, [fp, #-8]
     784:	ea000008 	b	0x7ac
     788:	e51b3008 	ldr	r3, [fp, #-8]
     78c:	e2832001 	add	r2, r3, #1
     790:	e50b2008 	str	r2, [fp, #-8]
     794:	e1a02003 	mov	r2, r3
     798:	e51b3010 	ldr	r3, [fp, #-16]
     79c:	e0833002 	add	r3, r3, r2
     7a0:	e5d33000 	ldrb	r3, [r3]
     7a4:	e1a00003 	mov	r0, r3
     7a8:	ebffffca 	bl	0x6d8
     7ac:	e51b3008 	ldr	r3, [fp, #-8]
     7b0:	e51b2010 	ldr	r2, [fp, #-16]
     7b4:	e0823003 	add	r3, r2, r3
     7b8:	e5d33000 	ldrb	r3, [r3]
     7bc:	e3530000 	cmp	r3, #0
     7c0:	1afffff0 	bne	0x788
     7c4:	e1a00000 	nop			; (mov r0, r0)
     7c8:	e24bd004 	sub	sp, fp, #4
     7cc:	e8bd8800 	pop	{fp, pc}
     7d0:	e92d4800 	push	{fp, lr}
     7d4:	e28db004 	add	fp, sp, #4
     7d8:	e24dd008 	sub	sp, sp, #8
     7dc:	e59f30ac 	ldr	r3, [pc, #172]	; 0x890
     7e0:	e5933000 	ldr	r3, [r3]
     7e4:	e50b3008 	str	r3, [fp, #-8]
     7e8:	e51b3008 	ldr	r3, [fp, #-8]
     7ec:	e2433001 	sub	r3, r3, #1
     7f0:	e3530003 	cmp	r3, #3
     7f4:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
     7f8:	ea00000f 	b	0x83c
     7fc:	0000080c 	andeq	r0, r0, ip, lsl #16
     800:	00000818 	andeq	r0, r0, r8, lsl r8
     804:	00000824 	andeq	r0, r0, r4, lsr #16
     808:	00000830 	andeq	r0, r0, r0, lsr r8
     80c:	e59f0080 	ldr	r0, [pc, #128]	; 0x894
     810:	ebffffd5 	bl	0x76c
     814:	ea00000b 	b	0x848
     818:	e59f0078 	ldr	r0, [pc, #120]	; 0x898
     81c:	ebffffd2 	bl	0x76c
     820:	ea000008 	b	0x848
     824:	e59f0070 	ldr	r0, [pc, #112]	; 0x89c
     828:	ebffffcf 	bl	0x76c
     82c:	ea000005 	b	0x848
     830:	e59f0068 	ldr	r0, [pc, #104]	; 0x8a0
     834:	ebffffcc 	bl	0x76c
     838:	ea000002 	b	0x848
     83c:	e59f0060 	ldr	r0, [pc, #96]	; 0x8a4
     840:	ebffffc9 	bl	0x76c
     844:	e1a00000 	nop			; (mov r0, r0)
     848:	e51b3008 	ldr	r3, [fp, #-8]
     84c:	e3530004 	cmp	r3, #4
     850:	1a000002 	bne	0x860
     854:	e59f304c 	ldr	r3, [pc, #76]	; 0x8a8
     858:	e3a02080 	mov	r2, #128	; 0x80
     85c:	e5832000 	str	r2, [r3]
     860:	e3a02001 	mov	r2, #1
     864:	e51b3008 	ldr	r3, [fp, #-8]
     868:	e1a02312 	lsl	r2, r2, r3
     86c:	e3a0344a 	mov	r3, #1241513984	; 0x4a000000
     870:	e5832000 	str	r2, [r3]
     874:	e59f3030 	ldr	r3, [pc, #48]	; 0x8ac
     878:	e59f202c 	ldr	r2, [pc, #44]	; 0x8ac
     87c:	e5933000 	ldr	r3, [r3]
     880:	e5823000 	str	r3, [r2]
     884:	e1a00000 	nop			; (mov r0, r0)
     888:	e24bd004 	sub	sp, fp, #4
     88c:	e8bd8800 	pop	{fp, pc}
     890:	4a000014 	bmi	0x8e8
     894:	00000a20 	andeq	r0, r0, r0, lsr #20
     898:	00000a38 	andeq	r0, r0, r8, lsr sl
     89c:	00000a50 	andeq	r0, r0, r0, asr sl
     8a0:	00000a68 	andeq	r0, r0, r8, ror #20
     8a4:	00000a80 	andeq	r0, r0, r0, lsl #21
     8a8:	560000a8 	strpl	r0, [r0], -r8, lsr #1
     8ac:	4a000010 	bmi	0x8f4
     8b0:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     8b4:	e28db000 	add	fp, sp, #0
     8b8:	e24dd00c 	sub	sp, sp, #12
     8bc:	e3a03203 	mov	r3, #805306368	; 0x30000000
     8c0:	e50b3008 	str	r3, [fp, #-8]
     8c4:	ea00000c 	b	0x8fc
     8c8:	e59f30ac 	ldr	r3, [pc, #172]	; 0x97c
     8cc:	e5932000 	ldr	r2, [r3]
     8d0:	e51b3008 	ldr	r3, [fp, #-8]
     8d4:	e1a03a23 	lsr	r3, r3, #20
     8d8:	e1a03103 	lsl	r3, r3, #2
     8dc:	e0822003 	add	r2, r2, r3
     8e0:	e51b3008 	ldr	r3, [fp, #-8]
     8e4:	e3833ec1 	orr	r3, r3, #3088	; 0xc10
     8e8:	e383300a 	orr	r3, r3, #10
     8ec:	e5823000 	str	r3, [r2]
     8f0:	e51b3008 	ldr	r3, [fp, #-8]
     8f4:	e2833601 	add	r3, r3, #1048576	; 0x100000
     8f8:	e50b3008 	str	r3, [fp, #-8]
     8fc:	e51b3008 	ldr	r3, [fp, #-8]
     900:	e3730373 	cmn	r3, #-872415231	; 0xcc000001
     904:	9affffef 	bls	0x8c8
     908:	e3a03312 	mov	r3, #1207959552	; 0x48000000
     90c:	e50b3008 	str	r3, [fp, #-8]
     910:	ea00000c 	b	0x948
     914:	e59f3060 	ldr	r3, [pc, #96]	; 0x97c
     918:	e5932000 	ldr	r2, [r3]
     91c:	e51b3008 	ldr	r3, [fp, #-8]
     920:	e1a03a23 	lsr	r3, r3, #20
     924:	e1a03103 	lsl	r3, r3, #2
     928:	e0822003 	add	r2, r2, r3
     92c:	e51b3008 	ldr	r3, [fp, #-8]
     930:	e3833ec1 	orr	r3, r3, #3088	; 0xc10
     934:	e3833002 	orr	r3, r3, #2
     938:	e5823000 	str	r3, [r2]
     93c:	e51b3008 	ldr	r3, [fp, #-8]
     940:	e2833601 	add	r3, r3, #1048576	; 0x100000
     944:	e50b3008 	str	r3, [fp, #-8]
     948:	e51b3008 	ldr	r3, [fp, #-8]
     94c:	e373021a 	cmn	r3, #-1610612735	; 0xa0000001
     950:	9affffef 	bls	0x914
     954:	e59f3020 	ldr	r3, [pc, #32]	; 0x97c
     958:	e5933000 	ldr	r3, [r3]
     95c:	e2833dff 	add	r3, r3, #16320	; 0x3fc0
     960:	e283303c 	add	r3, r3, #60	; 0x3c
     964:	e59f2014 	ldr	r2, [pc, #20]	; 0x980
     968:	e5832000 	str	r2, [r3]
     96c:	e1a00000 	nop			; (mov r0, r0)
     970:	e28bd000 	add	sp, fp, #0
     974:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     978:	e12fff1e 	bx	lr
     97c:	00004004 	andeq	r4, r0, r4
     980:	33f00c1a 	mvnscc	r0, #6656	; 0x1a00
     984:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
     988:	e28db000 	add	fp, sp, #0
     98c:	e24dd00c 	sub	sp, sp, #12
     990:	e3a03203 	mov	r3, #805306368	; 0x30000000
     994:	e50b3008 	str	r3, [fp, #-8]
     998:	e51b3008 	ldr	r3, [fp, #-8]
     99c:	e3a00000 	mov	r0, #0
     9a0:	ee070f17 	mcr	15, 0, r0, cr7, cr7, {0}
     9a4:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
     9a8:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
     9ac:	e1a04003 	mov	r4, r3
     9b0:	ee024f10 	mcr	15, 0, r4, cr2, cr0, {0}
     9b4:	e3e00000 	mvn	r0, #0
     9b8:	ee030f10 	mcr	15, 0, r0, cr3, cr0, {0}
     9bc:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
     9c0:	e59f1020 	ldr	r1, [pc, #32]	; 0x9e8
     9c4:	e1c00001 	bic	r0, r0, r1
     9c8:	e3800a02 	orr	r0, r0, #8192	; 0x2000
     9cc:	e3800002 	orr	r0, r0, #2
     9d0:	e3800001 	orr	r0, r0, #1
     9d4:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
     9d8:	e1a00000 	nop			; (mov r0, r0)
     9dc:	e28bd000 	add	sp, fp, #0
     9e0:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
     9e4:	e12fff1e 	bx	lr
     9e8:	00001384 	andeq	r1, r0, r4, lsl #7
     9ec:	22111110 	andscs	r1, r1, #16, 2
     9f0:	00000700 	andeq	r0, r0, r0, lsl #14
     9f4:	00000700 	andeq	r0, r0, r0, lsl #14
     9f8:	00000700 	andeq	r0, r0, r0, lsl #14
     9fc:	00000700 	andeq	r0, r0, r0, lsl #14
     a00:	00000700 	andeq	r0, r0, r0, lsl #14
     a04:	00000700 	andeq	r0, r0, r0, lsl #14
     a08:	00018005 	andeq	r8, r1, r5
     a0c:	00018005 	andeq	r8, r1, r5
     a10:	008e07a3 	addeq	r0, lr, r3, lsr #15
     a14:	000000b2 	strheq	r0, [r0], -r2
     a18:	00000030 	andeq	r0, r0, r0, lsr r0
     a1c:	00000030 	andeq	r0, r0, r0, lsr r0
     a20:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a24:	4b202c31 	blmi	0x80baf0
     a28:	72702031 	rsbsvc	r2, r0, #49	; 0x31
     a2c:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a30:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a34:	00000000 	andeq	r0, r0, r0
     a38:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a3c:	4b202c32 	blmi	0x80bb0c
     a40:	72702032 	rsbsvc	r2, r0, #50	; 0x32
     a44:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a48:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a4c:	00000000 	andeq	r0, r0, r0
     a50:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a54:	4b202c33 	blmi	0x80bb28
     a58:	72702033 	rsbsvc	r2, r0, #51	; 0x33
     a5c:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a60:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a64:	00000000 	andeq	r0, r0, r0
     a68:	544e4945 	strbpl	r4, [lr], #-2373	; 0xfffff6bb
     a6c:	4b202c37 	blmi	0x80bb50
     a70:	72702034 	rsbsvc	r2, r0, #52	; 0x34
     a74:	65737365 	ldrbvs	r7, [r3, #-869]!	; 0xfffffc9b
     a78:	0d0a2164 	stfeqs	f2, [sl, #-400]	; 0xfffffe70
     a7c:	00000000 	andeq	r0, r0, r0
     a80:	65746e49 	ldrbvs	r6, [r4, #-3657]!	; 0xfffff1b7
     a84:	70757272 	rsbsvc	r7, r5, r2, ror r2
     a88:	6e752074 	mrcvs	0, 3, r2, cr5, cr4, {3}
     a8c:	776f6e6b 	strbvc	r6, [pc, -fp, ror #28]!
     a90:	0d0a216e 	stfeqs	f2, [sl, #-440]	; 0xfffffe48
	...
    8000:	12345678 	eorsne	r5, r4, #120, 12	; 0x7800000
    8004:	30000000 	andcc	r0, r0, r0
