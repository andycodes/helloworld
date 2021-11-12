#ifdef __cplusplus
extern "C" {
#endif


#include "lm3s6965.h"
#include <sys/types.h>

static char *heap_end = 0;
extern unsigned long _heap_bottom;
extern unsigned long _heap_top;
extern unsigned long g_ulBase;

int _close(int file){
    return -1;
}

int _fstat(int file){
    return 0;
}

int _isatty(int file){
    return 1;
}

int _lseek(int file, int ptr, int dir){
    return 0;
}

int _open(const char *name, int flags, int mode){
    return -1;
}

int _read(int file, char *ptr, int len){
//	int todo;
//	char ch;
//	for (todo = 0; todo < len; todo++, ptr++){
//		while(UART_FR(UART0_ADDR) & UART_FR_RXFE)
//		;
//		*ptr = UART_DR(UART0_ADDR); //获取字符
//		UART_DR(UART0_ADDR) = *ptr; //回显
//		if(UART_FR(UART0_ADDR) & UART_FR_RXFE){
// 			break;
//		}
//	}
 	return len;
}

int _write(int file, char *ptr, int len){
	int todo;
 
	for (todo = 0; todo < len; todo++){
		UART_DR(UART0_ADDR) = *ptr++;
	}
	return len;
}

caddr_t _sbrk(unsigned int incr){
    char *prev_heap_end;

    if (heap_end == 0){
        heap_end = (caddr_t)&_heap_bottom;
    }

    prev_heap_end = heap_end;

    if (heap_end + incr > (caddr_t)&_heap_top){
        return (caddr_t)0;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

#ifdef __cplusplus
}
#endif