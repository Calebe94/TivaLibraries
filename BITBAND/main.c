/*
 * main.c
 *
 * GPIO_PORTF_DIR_R = 0x40025400;
 * 0x25400 OFF_SET_R * 0x20(BASE) + (0x2(BIT QUE QUERO ACIONAR)*0x04(BASE BIT ESPECÍFICO)) = 0x4A808(VALOR DE OFSET);
 *
 * Valor da BitBand = 0x42000000(Base)+0x4A808(OFFSET) = 424A8008;
 *
 *GPIO_PORTF_DATA_R = 0x400253FC;
 *0x253FC * 0x20 +(0x2*0x04) = 4A7F88
 * Valor da BitBand = 0x42000000+4A7F88 = 424A7F88
 *
 * GPIO_PORTF_DEN_R = 0x4002551C;
 * 0x2551C * 0x20 + (0x2*0x04) = 4AA388
 * Valor da BitBand = 0x42000000 + 0x4AA388 = 424AA388
 */
#include<stdint.h>

#define GPIO_PORTF_DIR_BIT2  (*((volatile uint32_t*)0x424A8008))
#define GPIO_PORTF_DATA_BIT2 (*((volatile uint32_t*)0x424A7F88))
#define GPIO_PORTF_DEN_BIT2  (*((volatile uint32_t*)0x424AA388))

#include"tm4c123gh6pm.h"

void setup(){

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
    while(SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOF==0){}

    GPIO_PORTF_DIR_BIT2 = 1;
    GPIO_PORTF_DATA_BIT2 = 0;
    GPIO_PORTF_DEN_BIT2 = 1;
    GPIO_PORTF_DATA_BIT2 = 1;
}

int main(void) {

    setup();

	while(1){
	    //GPIO_PORTF_DATA_R = 1<<2;
	    __asm("WFI");
	}
}
