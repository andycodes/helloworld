
./out/mcu.elf：     文件格式 elf32-littlearm


Disassembly of section .text:

00010330 <main>:
main():
   10330:	e92d4010 	push	{r4, lr}
   10334:	e3a01955 	mov	r1, #1392640	; 0x154000
   10338:	e3a04456 	mov	r4, #1442840576	; 0x56000000
   1033c:	e59f202c 	ldr	r2, [pc, #44]	; 10370 <main+0x40>
   10340:	e59fc02c 	ldr	ip, [pc, #44]	; 10374 <main+0x44>
   10344:	e592e000 	ldr	lr, [r2]
   10348:	e59f0028 	ldr	r0, [pc, #40]	; 10378 <main+0x48>
   1034c:	e0230e9c 	mla	r3, ip, lr, r0
   10350:	e5823000 	str	r3, [r2]
   10354:	e5841010 	str	r1, [r4, #16]
   10358:	eb000176 	bl	10938 <init_uart>
   1035c:	e1a02004 	mov	r2, r4
   10360:	e3e03000 	mvn	r3, #0
   10364:	e5823014 	str	r3, [r2, #20]
   10368:	e2433080 	sub	r3, r3, #128	; 0x80
   1036c:	eafffffc 	b	10364 <main+0x34>
   10370:	00021028 	.word	0x00021028
   10374:	0019660d 	.word	0x0019660d
   10378:	3c6ef35f 	.word	0x3c6ef35f

0001037c <_start>:
_start():
   1037c:	e3a0b000 	mov	fp, #0
   10380:	e3a0e000 	mov	lr, #0
   10384:	e49d1004 	pop	{r1}		; (ldr r1, [sp], #4)
   10388:	e1a0200d 	mov	r2, sp
   1038c:	e52d2004 	push	{r2}		; (str r2, [sp, #-4]!)
   10390:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
   10394:	e59fc010 	ldr	ip, [pc, #16]	; 103ac <_start+0x30>
   10398:	e52dc004 	push	{ip}		; (str ip, [sp, #-4]!)
   1039c:	e59f000c 	ldr	r0, [pc, #12]	; 103b0 <_start+0x34>
   103a0:	e59f300c 	ldr	r3, [pc, #12]	; 103b4 <_start+0x38>
   103a4:	ebffffd8 	bl	1030c <__libc_start_main@plt>
   103a8:	ebffffdd 	bl	10324 <abort@plt>
   103ac:	00010a44 	.word	0x00010a44
   103b0:	00010330 	.word	0x00010330
   103b4:	000109e4 	.word	0x000109e4

000103b8 <call_weak_fn>:
call_weak_fn():
   103b8:	e59f3014 	ldr	r3, [pc, #20]	; 103d4 <call_weak_fn+0x1c>
   103bc:	e59f2014 	ldr	r2, [pc, #20]	; 103d8 <call_weak_fn+0x20>
   103c0:	e08f3003 	add	r3, pc, r3
   103c4:	e7932002 	ldr	r2, [r3, r2]
   103c8:	e3520000 	cmp	r2, #0
   103cc:	012fff1e 	bxeq	lr
   103d0:	eaffffd0 	b	10318 <__gmon_start__@plt>
   103d4:	00010c38 	.word	0x00010c38
   103d8:	00000018 	.word	0x00000018

000103dc <deregister_tm_clones>:
deregister_tm_clones():
   103dc:	e59f0018 	ldr	r0, [pc, #24]	; 103fc <deregister_tm_clones+0x20>
   103e0:	e59f3018 	ldr	r3, [pc, #24]	; 10400 <deregister_tm_clones+0x24>
   103e4:	e1530000 	cmp	r3, r0
   103e8:	012fff1e 	bxeq	lr
   103ec:	e59f3010 	ldr	r3, [pc, #16]	; 10404 <deregister_tm_clones+0x28>
   103f0:	e3530000 	cmp	r3, #0
   103f4:	012fff1e 	bxeq	lr
   103f8:	e12fff13 	bx	r3
   103fc:	00021024 	.word	0x00021024
   10400:	00021024 	.word	0x00021024
   10404:	00000000 	.word	0x00000000

00010408 <register_tm_clones>:
register_tm_clones():
   10408:	e59f0024 	ldr	r0, [pc, #36]	; 10434 <register_tm_clones+0x2c>
   1040c:	e59f1024 	ldr	r1, [pc, #36]	; 10438 <register_tm_clones+0x30>
   10410:	e0411000 	sub	r1, r1, r0
   10414:	e1a01141 	asr	r1, r1, #2
   10418:	e0811fa1 	add	r1, r1, r1, lsr #31
   1041c:	e1b010c1 	asrs	r1, r1, #1
   10420:	012fff1e 	bxeq	lr
   10424:	e59f3010 	ldr	r3, [pc, #16]	; 1043c <register_tm_clones+0x34>
   10428:	e3530000 	cmp	r3, #0
   1042c:	012fff1e 	bxeq	lr
   10430:	e12fff13 	bx	r3
   10434:	00021024 	.word	0x00021024
   10438:	00021024 	.word	0x00021024
   1043c:	00000000 	.word	0x00000000

00010440 <__do_global_dtors_aux>:
__do_global_dtors_aux():
   10440:	e92d4010 	push	{r4, lr}
   10444:	e59f4018 	ldr	r4, [pc, #24]	; 10464 <__do_global_dtors_aux+0x24>
   10448:	e5d43000 	ldrb	r3, [r4]
   1044c:	e3530000 	cmp	r3, #0
   10450:	18bd8010 	popne	{r4, pc}
   10454:	ebffffe0 	bl	103dc <deregister_tm_clones>
   10458:	e3a03001 	mov	r3, #1
   1045c:	e5c43000 	strb	r3, [r4]
   10460:	e8bd8010 	pop	{r4, pc}
   10464:	00021024 	.word	0x00021024

00010468 <frame_dummy>:
frame_dummy():
   10468:	eaffffe6 	b	10408 <register_tm_clones>

0001046c <mmu_tlb_init>:
mmu_tlb_init():
   1046c:	e3a02203 	mov	r2, #805306368	; 0x30000000
   10470:	e59f0054 	ldr	r0, [pc, #84]	; 104cc <mmu_tlb_init+0x60>
   10474:	e1a03a22 	lsr	r3, r2, #20
   10478:	e1821000 	orr	r1, r2, r0
   1047c:	e1a03103 	lsl	r3, r3, #2
   10480:	e2822601 	add	r2, r2, #1048576	; 0x100000
   10484:	e2833203 	add	r3, r3, #805306368	; 0x30000000
   10488:	e352030d 	cmp	r2, #872415232	; 0x34000000
   1048c:	e5831000 	str	r1, [r3]
   10490:	1afffff7 	bne	10474 <mmu_tlb_init+0x8>
   10494:	e3a02312 	mov	r2, #1207959552	; 0x48000000
   10498:	e59f0030 	ldr	r0, [pc, #48]	; 104d0 <mmu_tlb_init+0x64>
   1049c:	e1a03a22 	lsr	r3, r2, #20
   104a0:	e1821000 	orr	r1, r2, r0
   104a4:	e1a03103 	lsl	r3, r3, #2
   104a8:	e2822601 	add	r2, r2, #1048576	; 0x100000
   104ac:	e2833203 	add	r3, r3, #805306368	; 0x30000000
   104b0:	e3520206 	cmp	r2, #1610612736	; 0x60000000
   104b4:	e5831000 	str	r1, [r3]
   104b8:	1afffff7 	bne	1049c <mmu_tlb_init+0x30>
   104bc:	e59f3010 	ldr	r3, [pc, #16]	; 104d4 <mmu_tlb_init+0x68>
   104c0:	e59f2010 	ldr	r2, [pc, #16]	; 104d8 <mmu_tlb_init+0x6c>
   104c4:	e5832ffc 	str	r2, [r3, #4092]	; 0xffc
   104c8:	e12fff1e 	bx	lr
   104cc:	00000c1a 	.word	0x00000c1a
   104d0:	00000c12 	.word	0x00000c12
   104d4:	30003000 	.word	0x30003000
   104d8:	33f00c1a 	.word	0x33f00c1a

000104dc <mmu_init>:
mmu_init():
   104dc:	e3a03203 	mov	r3, #805306368	; 0x30000000
   104e0:	e3a00000 	mov	r0, #0
   104e4:	ee070f17 	mcr	15, 0, r0, cr7, cr7, {0}
   104e8:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
   104ec:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
   104f0:	e1a04003 	mov	r4, r3
   104f4:	ee024f10 	mcr	15, 0, r4, cr2, cr0, {0}
   104f8:	e3e00000 	mvn	r0, #0
   104fc:	ee030f10 	mcr	15, 0, r0, cr3, cr0, {0}
   10500:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
   10504:	e59f1014 	ldr	r1, [pc, #20]	; 10520 <mmu_init+0x44>
   10508:	e1c00001 	bic	r0, r0, r1
   1050c:	e3800a02 	orr	r0, r0, #8192	; 0x2000
   10510:	e3800002 	orr	r0, r0, #2
   10514:	e3800001 	orr	r0, r0, #1
   10518:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
   1051c:	e12fff1e 	bx	lr
   10520:	00001384 	.word	0x00001384

00010524 <disable_watch_dog>:
disable_watch_dog():
   10524:	e3a03453 	mov	r3, #1392508928	; 0x53000000
   10528:	e3a02000 	mov	r2, #0
   1052c:	e5832000 	str	r2, [r3]
   10530:	e12fff1e 	bx	lr

00010534 <memsetup>:
memsetup():
   10534:	e3a03312 	mov	r3, #1207959552	; 0x48000000
   10538:	e3a02c07 	mov	r2, #1792	; 0x700
   1053c:	e3a01030 	mov	r1, #48	; 0x30
   10540:	e3a0c0b2 	mov	ip, #178	; 0xb2
   10544:	e59f0040 	ldr	r0, [pc, #64]	; 1058c <memsetup+0x58>
   10548:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
   1054c:	e59fe03c 	ldr	lr, [pc, #60]	; 10590 <memsetup+0x5c>
   10550:	e5830000 	str	r0, [r3]
   10554:	e59f0038 	ldr	r0, [pc, #56]	; 10594 <memsetup+0x60>
   10558:	e583e024 	str	lr, [r3, #36]	; 0x24
   1055c:	e583c028 	str	ip, [r3, #40]	; 0x28
   10560:	e5832004 	str	r2, [r3, #4]
   10564:	e5832008 	str	r2, [r3, #8]
   10568:	e583200c 	str	r2, [r3, #12]
   1056c:	e5832010 	str	r2, [r3, #16]
   10570:	e5832014 	str	r2, [r3, #20]
   10574:	e5832018 	str	r2, [r3, #24]
   10578:	e583001c 	str	r0, [r3, #28]
   1057c:	e5830020 	str	r0, [r3, #32]
   10580:	e583102c 	str	r1, [r3, #44]	; 0x2c
   10584:	e5831030 	str	r1, [r3, #48]	; 0x30
   10588:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
   1058c:	22111110 	.word	0x22111110
   10590:	008e07a3 	.word	0x008e07a3
   10594:	00018005 	.word	0x00018005

00010598 <memsetup_2>:
memsetup_2():
   10598:	e3a03312 	mov	r3, #1207959552	; 0x48000000
   1059c:	e3a02c07 	mov	r2, #1792	; 0x700
   105a0:	e3a01030 	mov	r1, #48	; 0x30
   105a4:	e3a0c0b2 	mov	ip, #178	; 0xb2
   105a8:	e59f0040 	ldr	r0, [pc, #64]	; 105f0 <memsetup_2+0x58>
   105ac:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
   105b0:	e59fe03c 	ldr	lr, [pc, #60]	; 105f4 <memsetup_2+0x5c>
   105b4:	e5830000 	str	r0, [r3]
   105b8:	e59f0038 	ldr	r0, [pc, #56]	; 105f8 <memsetup_2+0x60>
   105bc:	e583e024 	str	lr, [r3, #36]	; 0x24
   105c0:	e583c028 	str	ip, [r3, #40]	; 0x28
   105c4:	e5832004 	str	r2, [r3, #4]
   105c8:	e5832008 	str	r2, [r3, #8]
   105cc:	e583200c 	str	r2, [r3, #12]
   105d0:	e5832010 	str	r2, [r3, #16]
   105d4:	e5832014 	str	r2, [r3, #20]
   105d8:	e5832018 	str	r2, [r3, #24]
   105dc:	e583001c 	str	r0, [r3, #28]
   105e0:	e5830020 	str	r0, [r3, #32]
   105e4:	e583102c 	str	r1, [r3, #44]	; 0x2c
   105e8:	e5831030 	str	r1, [r3, #48]	; 0x30
   105ec:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
   105f0:	22111110 	.word	0x22111110
   105f4:	008e07a3 	.word	0x008e07a3
   105f8:	00018005 	.word	0x00018005

000105fc <reset_nand>:
reset_nand():
   105fc:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
   10600:	e3e00000 	mvn	r0, #0
   10604:	e1a02003 	mov	r2, r3
   10608:	e5931000 	ldr	r1, [r3]
   1060c:	e3c11b02 	bic	r1, r1, #2048	; 0x800
   10610:	e5831000 	str	r1, [r3]
   10614:	e5c30004 	strb	r0, [r3, #4]
   10618:	e5d23010 	ldrb	r3, [r2, #16]
   1061c:	e3130001 	tst	r3, #1
   10620:	0afffffc 	beq	10618 <reset_nand+0x1c>
   10624:	e12fff1e 	bx	lr

00010628 <init_nand>:
init_nand():
   10628:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
   1062c:	e3e00000 	mvn	r0, #0
   10630:	e1a02003 	mov	r2, r3
   10634:	e59f1020 	ldr	r1, [pc, #32]	; 1065c <init_nand+0x34>
   10638:	e5831000 	str	r1, [r3]
   1063c:	e5931000 	ldr	r1, [r3]
   10640:	e3c11b02 	bic	r1, r1, #2048	; 0x800
   10644:	e5831000 	str	r1, [r3]
   10648:	e5c30004 	strb	r0, [r3, #4]
   1064c:	e5d23010 	ldrb	r3, [r2, #16]
   10650:	e3130001 	tst	r3, #1
   10654:	0afffffc 	beq	1064c <init_nand+0x24>
   10658:	e12fff1e 	bx	lr
   1065c:	0000f830 	.word	0x0000f830

00010660 <wait_idle>:
wait_idle():
   10660:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
   10664:	e5d23010 	ldrb	r3, [r2, #16]
   10668:	e3130001 	tst	r3, #1
   1066c:	0afffffc 	beq	10664 <wait_idle+0x4>
   10670:	e12fff1e 	bx	lr

00010674 <nand_read_ll>:
nand_read_ll():
   10674:	e92d40f0 	push	{r4, r5, r6, r7, lr}
   10678:	e1814002 	orr	r4, r1, r2
   1067c:	e1a04b84 	lsl	r4, r4, #23
   10680:	e1a04ba4 	lsr	r4, r4, #23
   10684:	e3540000 	cmp	r4, #0
   10688:	18bd80f0 	popne	{r4, r5, r6, r7, pc}
   1068c:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
   10690:	e1a0c001 	mov	ip, r1
   10694:	e5931000 	ldr	r1, [r3]
   10698:	e082500c 	add	r5, r2, ip
   1069c:	e3c11b02 	bic	r1, r1, #2048	; 0x800
   106a0:	e15c0005 	cmp	ip, r5
   106a4:	e5831000 	str	r1, [r3]
   106a8:	2a000019 	bcs	10714 <nand_read_ll+0xa0>
   106ac:	e1a01003 	mov	r1, r3
   106b0:	e2800c02 	add	r0, r0, #512	; 0x200
   106b4:	e1a064cc 	asr	r6, ip, #9
   106b8:	e1a0e8cc 	asr	lr, ip, #17
   106bc:	e1a02ccc 	asr	r2, ip, #25
   106c0:	e20660ff 	and	r6, r6, #255	; 0xff
   106c4:	e20c70ff 	and	r7, ip, #255	; 0xff
   106c8:	e20ee0ff 	and	lr, lr, #255	; 0xff
   106cc:	e20220ff 	and	r2, r2, #255	; 0xff
   106d0:	e5c14004 	strb	r4, [r1, #4]
   106d4:	e2403c02 	sub	r3, r0, #512	; 0x200
   106d8:	e5c17008 	strb	r7, [r1, #8]
   106dc:	e5c16008 	strb	r6, [r1, #8]
   106e0:	e5c1e008 	strb	lr, [r1, #8]
   106e4:	e5c12008 	strb	r2, [r1, #8]
   106e8:	e5d12010 	ldrb	r2, [r1, #16]
   106ec:	e3120001 	tst	r2, #1
   106f0:	0afffffc 	beq	106e8 <nand_read_ll+0x74>
   106f4:	e5d1200c 	ldrb	r2, [r1, #12]
   106f8:	e4c32001 	strb	r2, [r3], #1
   106fc:	e1530000 	cmp	r3, r0
   10700:	1afffffb 	bne	106f4 <nand_read_ll+0x80>
   10704:	e28ccc02 	add	ip, ip, #512	; 0x200
   10708:	e15c0005 	cmp	ip, r5
   1070c:	e2800c02 	add	r0, r0, #512	; 0x200
   10710:	3affffe7 	bcc	106b4 <nand_read_ll+0x40>
   10714:	e3a0244e 	mov	r2, #1308622848	; 0x4e000000
   10718:	e5923000 	ldr	r3, [r2]
   1071c:	e3833b02 	orr	r3, r3, #2048	; 0x800
   10720:	e5823000 	str	r3, [r2]
   10724:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}

00010728 <copy_vectors_from_nand_to_sdram>:
copy_vectors_from_nand_to_sdram():
   10728:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
   1072c:	e3a02000 	mov	r2, #0
   10730:	e1a00003 	mov	r0, r3
   10734:	e5931000 	ldr	r1, [r3]
   10738:	e3c11b02 	bic	r1, r1, #2048	; 0x800
   1073c:	e5831000 	str	r1, [r3]
   10740:	e5c32004 	strb	r2, [r3, #4]
   10744:	e5c32008 	strb	r2, [r3, #8]
   10748:	e5c32008 	strb	r2, [r3, #8]
   1074c:	e5c32008 	strb	r2, [r3, #8]
   10750:	e5c32008 	strb	r2, [r3, #8]
   10754:	e5d03010 	ldrb	r3, [r0, #16]
   10758:	e3130001 	tst	r3, #1
   1075c:	0afffffc 	beq	10754 <copy_vectors_from_nand_to_sdram+0x2c>
   10760:	e3a0344e 	mov	r3, #1308622848	; 0x4e000000
   10764:	e59f2020 	ldr	r2, [pc, #32]	; 1078c <copy_vectors_from_nand_to_sdram+0x64>
   10768:	e59f1020 	ldr	r1, [pc, #32]	; 10790 <copy_vectors_from_nand_to_sdram+0x68>
   1076c:	e5d3000c 	ldrb	r0, [r3, #12]
   10770:	e4c20001 	strb	r0, [r2], #1
   10774:	e1520001 	cmp	r2, r1
   10778:	1afffffb 	bne	1076c <copy_vectors_from_nand_to_sdram+0x44>
   1077c:	e5932000 	ldr	r2, [r3]
   10780:	e3822b02 	orr	r2, r2, #2048	; 0x800
   10784:	e5832000 	str	r2, [r3]
   10788:	e12fff1e 	bx	lr
   1078c:	33ff0000 	.word	0x33ff0000
   10790:	33ff0200 	.word	0x33ff0200

00010794 <copy_process_from_nand_to_sdram>:
copy_process_from_nand_to_sdram():
   10794:	e3a0144e 	mov	r1, #1308622848	; 0x4e000000
   10798:	e3a02000 	mov	r2, #0
   1079c:	e1a03001 	mov	r3, r1
   107a0:	e1a0c002 	mov	ip, r2
   107a4:	e5910000 	ldr	r0, [r1]
   107a8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
   107ac:	e3c00b02 	bic	r0, r0, #2048	; 0x800
   107b0:	e5810000 	str	r0, [r1]
   107b4:	e1a004c2 	asr	r0, r2, #9
   107b8:	e20000ff 	and	r0, r0, #255	; 0xff
   107bc:	e202e0ff 	and	lr, r2, #255	; 0xff
   107c0:	e2821203 	add	r1, r2, #805306368	; 0x30000000
   107c4:	e5c3c004 	strb	ip, [r3, #4]
   107c8:	e2811901 	add	r1, r1, #16384	; 0x4000
   107cc:	e5c3e008 	strb	lr, [r3, #8]
   107d0:	e5c30008 	strb	r0, [r3, #8]
   107d4:	e5c3c008 	strb	ip, [r3, #8]
   107d8:	e5c3c008 	strb	ip, [r3, #8]
   107dc:	e5d30010 	ldrb	r0, [r3, #16]
   107e0:	e3100001 	tst	r0, #1
   107e4:	0afffffc 	beq	107dc <copy_process_from_nand_to_sdram+0x48>
   107e8:	e2820203 	add	r0, r2, #805306368	; 0x30000000
   107ec:	e2800c42 	add	r0, r0, #16896	; 0x4200
   107f0:	e5d3e00c 	ldrb	lr, [r3, #12]
   107f4:	e4c1e001 	strb	lr, [r1], #1
   107f8:	e1510000 	cmp	r1, r0
   107fc:	1afffffb 	bne	107f0 <copy_process_from_nand_to_sdram+0x5c>
   10800:	e2822c02 	add	r2, r2, #512	; 0x200
   10804:	e3520a01 	cmp	r2, #4096	; 0x1000
   10808:	1affffe9 	bne	107b4 <copy_process_from_nand_to_sdram+0x20>
   1080c:	e5932000 	ldr	r2, [r3]
   10810:	e3822b02 	orr	r2, r2, #2048	; 0x800
   10814:	e5832000 	str	r2, [r3]
   10818:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

0001081c <init_irq>:
init_irq():
   1081c:	e3a03456 	mov	r3, #1442840576	; 0x56000000
   10820:	e3a0144a 	mov	r1, #1241513984	; 0x4a000000
   10824:	e5932050 	ldr	r2, [r3, #80]	; 0x50
   10828:	e3822902 	orr	r2, r2, #32768	; 0x8000
   1082c:	e38220a8 	orr	r2, r2, #168	; 0xa8
   10830:	e5832050 	str	r2, [r3, #80]	; 0x50
   10834:	e5932058 	ldr	r2, [r3, #88]	; 0x58
   10838:	e382208e 	orr	r2, r2, #142	; 0x8e
   1083c:	e5832058 	str	r2, [r3, #88]	; 0x58
   10840:	e59320a4 	ldr	r2, [r3, #164]	; 0xa4
   10844:	e3c22080 	bic	r2, r2, #128	; 0x80
   10848:	e58320a4 	str	r2, [r3, #164]	; 0xa4
   1084c:	e5913008 	ldr	r3, [r1, #8]
   10850:	e3c3301e 	bic	r3, r3, #30
   10854:	e5813008 	str	r3, [r1, #8]
   10858:	e591300c 	ldr	r3, [r1, #12]
   1085c:	e3c33003 	bic	r3, r3, #3
   10860:	e581300c 	str	r3, [r1, #12]
   10864:	e12fff1e 	bx	lr

00010868 <EINT_Handle>:
EINT_Handle():
   10868:	e3a0344a 	mov	r3, #1241513984	; 0x4a000000
   1086c:	e92d4010 	push	{r4, lr}
   10870:	e5934014 	ldr	r4, [r3, #20]
   10874:	e2443001 	sub	r3, r4, #1
   10878:	e3530003 	cmp	r3, #3
   1087c:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
   10880:	ea000018 	b	108e8 <EINT_Handle+0x80>
   10884:	000108dc 	.word	0x000108dc
   10888:	000108d0 	.word	0x000108d0
   1088c:	000108c4 	.word	0x000108c4
   10890:	00010894 	.word	0x00010894
   10894:	e59f0058 	ldr	r0, [pc, #88]	; 108f4 <EINT_Handle+0x8c>
   10898:	eb000043 	bl	109ac <printk>
   1089c:	e3a03456 	mov	r3, #1442840576	; 0x56000000
   108a0:	e3a02080 	mov	r2, #128	; 0x80
   108a4:	e58320a8 	str	r2, [r3, #168]	; 0xa8
   108a8:	e3a02001 	mov	r2, #1
   108ac:	e3a0344a 	mov	r3, #1241513984	; 0x4a000000
   108b0:	e1a02412 	lsl	r2, r2, r4
   108b4:	e5832000 	str	r2, [r3]
   108b8:	e5932010 	ldr	r2, [r3, #16]
   108bc:	e5832010 	str	r2, [r3, #16]
   108c0:	e8bd8010 	pop	{r4, pc}
   108c4:	e59f002c 	ldr	r0, [pc, #44]	; 108f8 <EINT_Handle+0x90>
   108c8:	eb000037 	bl	109ac <printk>
   108cc:	eafffff5 	b	108a8 <EINT_Handle+0x40>
   108d0:	e59f0024 	ldr	r0, [pc, #36]	; 108fc <EINT_Handle+0x94>
   108d4:	eb000034 	bl	109ac <printk>
   108d8:	eafffff2 	b	108a8 <EINT_Handle+0x40>
   108dc:	e59f001c 	ldr	r0, [pc, #28]	; 10900 <EINT_Handle+0x98>
   108e0:	eb000031 	bl	109ac <printk>
   108e4:	eaffffef 	b	108a8 <EINT_Handle+0x40>
   108e8:	e59f0014 	ldr	r0, [pc, #20]	; 10904 <EINT_Handle+0x9c>
   108ec:	eb00002e 	bl	109ac <printk>
   108f0:	eaffffec 	b	108a8 <EINT_Handle+0x40>
   108f4:	00010ad0 	.word	0x00010ad0
   108f8:	00010ab8 	.word	0x00010ab8
   108fc:	00010aa0 	.word	0x00010aa0
   10900:	00010a88 	.word	0x00010a88
   10904:	00010ae8 	.word	0x00010ae8

00010908 <Rand>:
Rand():
   10908:	e59f3018 	ldr	r3, [pc, #24]	; 10928 <Rand+0x20>
   1090c:	e59f1018 	ldr	r1, [pc, #24]	; 1092c <Rand+0x24>
   10910:	e5930000 	ldr	r0, [r3]
   10914:	e59f2014 	ldr	r2, [pc, #20]	; 10930 <Rand+0x28>
   10918:	e02c2091 	mla	ip, r1, r0, r2
   1091c:	e583c000 	str	ip, [r3]
   10920:	e1a002ac 	lsr	r0, ip, #5
   10924:	e12fff1e 	bx	lr
   10928:	00021028 	.word	0x00021028
   1092c:	0019660d 	.word	0x0019660d
   10930:	3c6ef35f 	.word	0x3c6ef35f

00010934 <wait>:
wait():
   10934:	e12fff1e 	bx	lr

00010938 <init_uart>:
init_uart():
   10938:	e3a02456 	mov	r2, #1442840576	; 0x56000000
   1093c:	e92d4010 	push	{r4, lr}
   10940:	e3a03205 	mov	r3, #1342177280	; 0x50000000
   10944:	e3a0000c 	mov	r0, #12
   10948:	e3a0c000 	mov	ip, #0
   1094c:	e3a04003 	mov	r4, #3
   10950:	e3a0e005 	mov	lr, #5
   10954:	e5921070 	ldr	r1, [r2, #112]	; 0x70
   10958:	e38110a0 	orr	r1, r1, #160	; 0xa0
   1095c:	e5821070 	str	r1, [r2, #112]	; 0x70
   10960:	e5820078 	str	r0, [r2, #120]	; 0x78
   10964:	e5834000 	str	r4, [r3]
   10968:	e583e004 	str	lr, [r3, #4]
   1096c:	e583c008 	str	ip, [r3, #8]
   10970:	e583c00c 	str	ip, [r3, #12]
   10974:	e5830028 	str	r0, [r3, #40]	; 0x28
   10978:	e8bd8010 	pop	{r4, pc}

0001097c <putc>:
putc():
   1097c:	e3a02205 	mov	r2, #1342177280	; 0x50000000
   10980:	e5923010 	ldr	r3, [r2, #16]
   10984:	e3130004 	tst	r3, #4
   10988:	0afffffc 	beq	10980 <putc+0x4>
   1098c:	e5c20020 	strb	r0, [r2, #32]
   10990:	e12fff1e 	bx	lr

00010994 <getc>:
getc():
   10994:	e3a02205 	mov	r2, #1342177280	; 0x50000000
   10998:	e5923010 	ldr	r3, [r2, #16]
   1099c:	e3130001 	tst	r3, #1
   109a0:	0afffffc 	beq	10998 <getc+0x4>
   109a4:	e5d20024 	ldrb	r0, [r2, #36]	; 0x24
   109a8:	e12fff1e 	bx	lr

000109ac <printk>:
printk():
   109ac:	e5d01000 	ldrb	r1, [r0]
   109b0:	e3510000 	cmp	r1, #0
   109b4:	012fff1e 	bxeq	lr
   109b8:	e3a02205 	mov	r2, #1342177280	; 0x50000000
   109bc:	e5923010 	ldr	r3, [r2, #16]
   109c0:	e3130004 	tst	r3, #4
   109c4:	0afffffc 	beq	109bc <printk+0x10>
   109c8:	e5c21020 	strb	r1, [r2, #32]
   109cc:	e5f01001 	ldrb	r1, [r0, #1]!
   109d0:	e3510000 	cmp	r1, #0
   109d4:	1afffff8 	bne	109bc <printk+0x10>
   109d8:	e12fff1e 	bx	lr

000109dc <sub_int>:
sub_int():
   109dc:	e0400001 	sub	r0, r0, r1
   109e0:	e12fff1e 	bx	lr

000109e4 <__libc_csu_init>:
__libc_csu_init():
   109e4:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}
   109e8:	e59f604c 	ldr	r6, [pc, #76]	; 10a3c <__libc_csu_init+0x58>
   109ec:	e59f504c 	ldr	r5, [pc, #76]	; 10a40 <__libc_csu_init+0x5c>
   109f0:	e08f6006 	add	r6, pc, r6
   109f4:	e08f5005 	add	r5, pc, r5
   109f8:	e0466005 	sub	r6, r6, r5
   109fc:	e1a07000 	mov	r7, r0
   10a00:	e1a08001 	mov	r8, r1
   10a04:	e1a09002 	mov	r9, r2
   10a08:	ebfffe37 	bl	102ec <_init>
   10a0c:	e1b06146 	asrs	r6, r6, #2
   10a10:	08bd87f0 	popeq	{r4, r5, r6, r7, r8, r9, sl, pc}
   10a14:	e3a04000 	mov	r4, #0
   10a18:	e2844001 	add	r4, r4, #1
   10a1c:	e4953004 	ldr	r3, [r5], #4
   10a20:	e1a02009 	mov	r2, r9
   10a24:	e1a01008 	mov	r1, r8
   10a28:	e1a00007 	mov	r0, r7
   10a2c:	e12fff33 	blx	r3
   10a30:	e1560004 	cmp	r6, r4
   10a34:	1afffff7 	bne	10a18 <__libc_csu_init+0x34>
   10a38:	e8bd87f0 	pop	{r4, r5, r6, r7, r8, r9, sl, pc}
   10a3c:	0001051c 	.word	0x0001051c
   10a40:	00010514 	.word	0x00010514

00010a44 <__libc_csu_fini>:
__libc_csu_fini():
   10a44:	e12fff1e 	bx	lr
