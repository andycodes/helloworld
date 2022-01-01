#include <stdint.h>

#define USART1_BASE_ADDR 0x40011000
#define USART_DR   0x04
#define DEBUG_UART_DR_ADDR (USART1_BASE_ADDR + USART_DR)

volatile uint32_t * const DEBUG_UART_DR = (uint32_t *)DEBUG_UART_DR_ADDR;
unsigned char UartPutc(unsigned char my_ch)
{
    *DEBUG_UART_DR = my_ch;
    return my_ch;
}
