.text
.global _start
.code 32
_start:
	/* ������arm_state -> thumb_state */
	adr r0,thumb_func
	add r0,r0,#1
	bx r0
	
.code 16
thumb_func:	
	bl sdram_init
	//bl sdram_init2 //�õ��г�ʼֵ�����飬����λ���޹���	
	bl copy2sdram	
	bl clean_bss
 
	//bl main 
/*
thumb����arm̬����������ֱ�ӽ���Ÿ�ֵ��pc��
��Ҫͨ���Ĵ���ת��
*/
	ldr r0,=main //������ת������SDRAM
	mov pc,r0
halt:
	b halt