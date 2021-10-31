/* 清除BSS段 */
   ldr r1, =bss_start
   ldr r2, =bss_end
   mov r3, #0
clean:
   str r3, [r1]
   add r1, r1, #4
   cmp r1, r2
   ble clean



/* 重定位data段 */
ldr r1, =data_load_addr  /* data段在bin文件中的地址, 加载地址 */
ldr r2, =data_start      /* data段在重定位地址, 运行时的地址 */
ldr r3, =data_end        /* data段结束地址 */

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