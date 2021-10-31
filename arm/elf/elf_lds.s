/* ���BSS�� */
   ldr r1, =bss_start
   ldr r2, =bss_end
   mov r3, #0
clean:
   str r3, [r1]
   add r1, r1, #4
   cmp r1, r2
   ble clean



/* �ض�λdata�� */
ldr r1, =data_load_addr  /* data����bin�ļ��еĵ�ַ, ���ص�ַ */
ldr r2, =data_start      /* data�����ض�λ��ַ, ����ʱ�ĵ�ַ */
ldr r3, =data_end        /* data�ν�����ַ */

cpy:
    ldr r4, [r1]
    str r4, [r2]
    add r1, r1, #4
    add r2, r2, #4
    cmp r2, r3
    ble cpy

bl main


/*
arm-linux-ld -T sdram.lds start.o led.o uart.o init.o main.o -o sdram.elf
arm-linux-objcopy -O binary -- sdram.elf sdram.bin
*/