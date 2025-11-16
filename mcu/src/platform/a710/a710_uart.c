
#include <stdint.h>

#define DEBUG_UART_DR_ADDR (0x09000000)

volatile uint32_t * const DEBUG_UART_DR = (uint32_t *)DEBUG_UART_DR_ADDR;
unsigned char UartPutc(unsigned char my_ch)
{
    *DEBUG_UART_DR = my_ch;
    return my_ch;
}