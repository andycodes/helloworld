#include <stdint.h>
#include <stdbool.h>

#define CMSDK_UART_CTRL_TXEN_Msk         (0x01UL) /* CMSDK_UART CTRL: TXEN Mask */


/* typedef's */
typedef struct {
    uint32_t  DATA;                     /* Offset: 0x000 (R/W) Data Register */
    uint32_t  STATE;                    /* Offset: 0x004 (R/W) Status state */
    uint32_t  CTRL;                     /* Offset: 0x008 (R/W) Control Register */
    union {
        uint32_t INTSTATUS;             /* Offset: 0x00C (R/ ) Interrupt Status Register */
        uint32_t INTCLEAR;              /* Offset: 0x00C ( /W) Interrupt Clear Register */
    };
    uint32_t  BAUDDIV;                  /* Offset: 0x010 (R/W) Baud rate divider */
} uart_t;

volatile uint32_t g_uart;
/**
    @brief    - This function initializes the UART
**/
void pal_uart_cmsdk_init(uint32_t uart_base_addr)
{
    g_uart = uart_base_addr;

    /* Disable RX and TX interrupts, disable overrun interrupts, enable TX,
    * disable RX */
    ((uart_t *) g_uart)->CTRL = CMSDK_UART_CTRL_TXEN_Msk;
    /* However, the UART resets to a BAUDDIV of 0, which is invalid. Set it to
    * the minimum valid number. */
    ((uart_t *) g_uart)->BAUDDIV = 16;

}

void main(void)
{
    pal_uart_cmsdk_init(0x50200000);
    volatile unsigned int * const DEBUG_UART_DR = (unsigned int  *)0x50200000;
    int i = 65;

    while (1){
        *DEBUG_UART_DR = i++;
    };
}
