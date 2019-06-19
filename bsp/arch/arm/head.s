@******************************************************************************
@ File��head.s
@ ���ܣ�����SDRAM���������Ƶ�SDRAM��Ȼ������SDRAM����ִ��
@******************************************************************************       
	
	   
.extern		main
.text 
.global _start 
_start:
@******************************************************************************       
@�ж�����,��Reset��HandleIRQ�⣬�����쳣��û��ʹ��(������ҷ����ˣ�����������)
@******************************************************************************       
	b	Reset

@ 0x04: Undefined instruction exception
HandleUndef:
	b	HandleUndef 
 
@ 0x08: Software interrupt exception  
HandleSWI:
	b	HandleSWI

@ 0x0c: Prefetch Abort (Instruction Fetch Memory Abort)
HandlePrefetchAbort:
	b	HandlePrefetchAbort

@ 0x10: Data Access Memory Abort
HandleDataAbort:
	b	HandleDataAbort

@ 0x14: Not used
HandleNotUsed:
	b	HandleNotUsed

@ 0x18: IRQ(Interrupt Request) exception
	ldr	pc,HandleIRQAddr

@ 0x1c: FIQ(Fast Interrupt Request) exception
HandleFIQ:
	b	HandleFIQ
	
HandleIRQAddr:	
	.long	HandleIRQ
		

Reset:				@����disable_watch_dog, memsetup, init_nand, nand_read_ll��init.c�ж���
	ldr	sp,	=4096	@���ö�ջ 
	bl	disable_watch_dog	@��WATCH DOG
	bl	memsetup_2		@��ʼ��SDRAM
	bl	init_nand		@��ʼ��NAND Flash

	bl	copy_vectors_from_nand_to_sdram
	bl	copy_process_from_nand_to_sdram

	ldr	sp, =0x30100000	@�������ö�ջ(��Ϊ�����Ҫ����SDRAM��ִ����)
	ldr	pc, =run_on_sdram	@����SDRAM��
run_on_sdram:	
	bl	mmu_tlb_init	@����C����mmu_tlb_init(mmu.c��)������ҳ��
	bl	mmu_init		@����C����mmu_init(mmu.c��)��ʹ��MMU
		
	msr	cpsr_c,	#0xd2	@�����ж�ģʽ
	ldr	sp,	=0x33000000	@�����ж�ģʽ��ջ

	msr	cpsr_c,	#0xdf	@����ϵͳģʽ
	ldr	sp,	=0x30100000	@����ϵͳģʽ��ջ

	bl	init_irq		@�����жϳ�ʼ����������init.c��
	msr	cpsr_c,	#0x5f	@����I-bit=0����IRQ�ж�
	
	ldr	lr,	=halt_loop	@���÷��ص�ַ
	ldr	pc,	=main	@bָ���blָ��ֻ��ǰ����ת32M�ķ�Χ����������ʹ����pc��ֵ�ķ���������ת
halt_loop:
	b	halt_loop

HandleIRQ:
	sub	lr, lr, #4		@���㷵�ص�ַ
	stmdb	sp!, 	{ r0-r12,lr }	@����ʹ�õ��ļĴ���
	
	ldr	lr,	=int_return	@���÷��ص�ַ	
	ldr	pc, 	=EINT_Handle	@�����жϴ���������interrupt.c��
int_return:
	ldmia	sp!, 	{ r0-r12,pc }^	@�жϷ���, ^��ʾ��spsr��ֵ���Ƶ�cpsr
	




