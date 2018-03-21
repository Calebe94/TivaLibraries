#include"SSI.h"

#define F_CPU 16000000u

/*Initialization an Configuration - See pg. 965*/
void SSI0_init(uint8_t clock, uint8_t divider){
	SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0;
	while(SYSCTL_RCGCSSI_R&SYSCTL_RCGCSSI_R0==0);
	SYSCTL_RCGCGPIO_R|= SYSCTL_GPIOHBCTL_PORTA;
	while(SYSCTL_RCGCGPIO_R&SYSCTL_GPIOHBCTL_PORTA==0);
	GPIO_PORTA_DIR_R  |= ();
	GPIO_PORTA_AFSEL_R|= (1<<2)|(1<<3)|(1<<5);
	GPIO_PORTA_DEN_R  |= (1<<2)|(1<<3)|(1<<5)|(1<<6)|(1<<7);
	GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA3_SSI0FSS|GPIO_PCTL_PA2_SSI0CLK|GPIO_PCTL_PA5_SSI0TX;

	SSI0_CR1_R &=~SSI_CR1_SSE;
	SSI0_CR1_R &=~SSI_CR1_MS;

	SSI0_CC_R = (F_CPU/(clock/divider))-1;
	SSI0_CPSR_R &=~SSI_CC_CS_M;
	SSI0_CPSR_R |= 24;

	SSI0_CR0_R&=~(SSI_CR0_SCR_M|SSI_CR0_SPH|SSI_CR0_SPO); // Freescale Format, NOKIA 5110 display only uses Freescale format
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8; // 8 bit
	SSI0_CR1_R|=SSI_CR1_SSE; // Have fun
}

void SSI0_write(uint8_t data){
	while ((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY | (SSI0_SR_R&SSI_SR_TNF)==0);
	SSI0_DR_R = data;
	while ((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY);
}
