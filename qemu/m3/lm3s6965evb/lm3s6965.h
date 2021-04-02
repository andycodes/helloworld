#ifndef LM3S6965_H

#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr))+6))

enum {
  UART_FR_RXFE = 0x10,
  UART_FR_TXFF = 0x20,
  UART0_ADDR = 0x4000C000,
};

#endif