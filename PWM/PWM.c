#include "inc/PWM.h"

#define F_PWM 16000000

#define F_USED 1599

//void PWM_init(uint16_t frequency, uint8_t porcentage){
void PWM_init(uint8_t porcentage){
	//uint16_t f_aux = ((1/frequency)*F_PWM)-1;
	//f_used = f_aux;
	SYSCTL_RCGCPWM_R |= 1<<0;  // Ativa o modulo de PWM 0
	while (SYSCTL_RCGCPWM_R&(1<<0)==0);
	SYSCTL_RCGCGPIO_R |= 1<<2; // Habilita PortC
	while(SYSCTL_RCGCGPIO_R&(1<<2)==0);
	GPIO_PORTC_AFSEL_R|= 1<<4; // Ativa função alternativa do Pino PC4
	GPIO_PORTC_PCTL_R |= 0x40000; // Ativa a função de PWM do PC4 (M0PWM6)
	GPIO_PORTC_DEN_R  |= 1<<4; // PC4 com Função digital

	PWM0_3_CTL_R  	 &= ~(1<<0);
	PWM0_3_GENA_R 	  = 0xC8; //Nivel baixo em LOAD / Nivel alto em CMPA
	//PWM0_3_LOAD_R 	  = f_aux; //Valor que frequencia do PWM
	PWM0_3_LOAD_R 	  = F_USED; //Valor que frequencia do PWM
	//PWM0_3_CMPA_R 	  = (uint16_t)((f_aux*porcentage)/100)-1; //Valor de porcentagem do PWM
	PWM0_3_CMPA_R 	  = (uint16_t)((F_USED*porcentage)/100)-1; //Valor de porcentagem do PWM
	PWM0_3_CTL_R  	 |= 1<<0;
	PWM0_ENABLE_R 	 |= 1<<6;
}

//void PWM_write(uint16_t frequency, uint8_t porcentage){
void PWM_write(uint8_t porcentage){
	//PWM0_3_CMPA_R = ((frequency * porcentage)/100)-1;
	PWM0_3_CMPA_R = ((F_USED * porcentage)/100)-1;
}
