#include"inc/UART.h"
#include<string.h>

UART UART0_begin(uint32_t baudrate){
    UART aux;

    uint32_t integer = (16000000/(16*baudrate/100));
    uint32_t fraction = (integer)-((16000000/(16*baudrate))*100);

    SYSCTL_RCGCUART_R |= (1<<0);
    while(SYSCTL_RCGCUART_R&(1<<0) == 0);
    SYSCTL_RCGCGPIO_R |= (1<<0);
    while(SYSCTL_RCGCGPIO_R&(1<<0) == 0);
    GPIO_PORTA_AFSEL_R = (1<<0)|(1<<1);
    GPIO_PORTA_PCTL_R  = (1<<0)|(1<<4);
    GPIO_PORTA_DEN_R   = (1<<0)|(1<<1);

    UART0_CTL_R &=~(1<<0);//UART Control. Check pg. 918
    //Interrupt
    UART0_IM_R = UART_IM_RXIM;
    UART0_IFLS_R = UART_IFLS_RX7_8 | UART_IFLS_TX1_8;

    UART0_IBRD_R = (uint32_t)integer/100;//Check pg. 914
    UART0_FBRD_R = (uint32_t)fraction;//Check pg. 915
    UART0_LCRH_R = 0x3<<5;//UART Line Control. Check pg. 916
    UART0_CC_R = 0x0;// UART Clock Configuration. Check pg. 939
    UART0_CTL_R = (1<<0)|(1<<8)|(1<<9);// UART Control. Check pg. 918
    aux.FR =&UART0_FR_R;  // UART Flag. Check pg. 911
    aux.DR =&UART0_DR_R;  //UART Data. Check pg. 906
    /*Just a little delay. I don't know why. But without it the UART crashes*/
    uint32_t delay=0;
    for(delay=0;delay<3000;delay++);

    NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFF00FF)|0x00004000;
    NVIC_EN0_R |= 0x00000020;

    for(delay=0;delay<3000;delay++);
    return aux;
}

UART UART1_begin(uint32_t baudrate){
    UART aux;

    uint32_t integer = (16000000/(16*baudrate/100));
    uint32_t fraction = (integer)-((16000000/(16*baudrate))*100);

    SYSCTL_RCGCUART_R |= (1<<1);
    while(SYSCTL_RCGCUART_R&(1<<1) == 0);
    SYSCTL_RCGCGPIO_R |= (1<<1);
    while(SYSCTL_RCGCGPIO_R&(1<<1) == 0);
    GPIO_PORTB_AFSEL_R |= (1<<0)|(1<<1);
    GPIO_PORTB_PCTL_R  |= (1<<0)|(1<<4); // GPIO Port Control is used in conjuction with the AFSEL. Check pg. 688
    GPIO_PORTB_DEN_R   |= (1<<0)|(1<<1);

    UART1_CTL_R &=~(1<<0);//Check pg 918
    UART1_IBRD_R = (uint32_t)integer/100;//Check pg 914
    UART1_FBRD_R = (uint32_t)fraction;//Check pg 915
    UART1_LCRH_R = 0x3<<5;//Check pg 916
    UART1_CC_R = 0x0;//Check pg 939
    UART1_CTL_R = (1<<0)|(1<<8)|(1<<9);//Check pg 918
    aux.FR =&UART1_FR_R;  //Check pg 911
    aux.DR =&UART1_DR_R;  //Check pg 906
    /*Just a little delay. I don't know why. But without it the UART crashes*/
    uint32_t delay=0;
    for(delay=0;delay<3000;delay++);

    return aux;
}

void UART_print(UART *uart, char *string){
    while(*string){
        UART_write(uart,*(string++));
    }
}
void UART_write(UART *uart, char character){
    while((*uart->FR&(1<<5))!=0){}
    *uart->DR = character;
}

char UART_read(UART *uart){
  while((*uart->FR&UART_FR_RXFE) != 0);
  return((char)(*uart->DR&0xFF));
}

void UART_readString(UART *uart, char *string, uint16_t max) {
	int length=0;
	char character;
	character = UART_read(uart);
	while(character != CR){
		if(length < max){
			*(string++) = character;
			length++;
		}
		character = UART_read(uart);
	}
	//*string = 0;
	//return length;
}
