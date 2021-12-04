#include <stdint.h>

#define UART0_DR  0x4000C000
#define DEBUG_UART_DR_ADDR UART0_DR

volatile uint32_t * const DEBUG_UART_DR = (uint32_t *)DEBUG_UART_DR_ADDR;
unsigned char UartPutc(unsigned char my_ch)
{
    *DEBUG_UART_DR = my_ch;
    return my_ch;
}