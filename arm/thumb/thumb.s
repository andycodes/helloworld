.text
.global _start
.code 32
_start:
	/* 怎样从arm_state -> thumb_state */
	adr r0,thumb_func
	add r0,r0,#1
	bx r0
	
.code 16
thumb_func:	
	bl sdram_init
	//bl sdram_init2 //用到有初始值的数组，不是位置无关码	
	bl copy2sdram	
	bl clean_bss
 
	//bl main 
/*
thumb不像arm态那样，不能直接将标号赋值给pc，
需要通过寄存器转化
*/
	ldr r0,=main //绝对跳转，跳到SDRAM
	mov pc,r0
halt:
	b halt