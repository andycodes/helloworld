
.syntax unified
.arch armv8-m.main

.section .isr_vector
.align   2
.globl __Vectors
__Vectors:	
    .long    __StackTop         /* Initial Top of Stack */
    .long    Reset_Handler      /* Reset Handler */
   

.text
.global Reset_Handler
Reset_Handler:  
    ldr     R0, = main
    bx      R0
         
