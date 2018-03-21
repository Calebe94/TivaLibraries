#ifndef __UART_H__
#define __UART_H__

#include<stdlib.h>
#include<stdint.h>
#include"tm4c123gh6pm.h"

#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

typedef struct{
    volatile uint32_t *FR;
    volatile uint32_t *DR;
}UART;

UART USB;

void UART_write(UART *uart, char character);

void UART_print(UART *uart, char *string);

UART UART0_begin(uint32_t baudrate);

UART UART1_begin(uint32_t baudrate);

char UART_read(UART *uart);

void UART_readString(UART *uart,char *bufPt, uint16_t max);

#endif
