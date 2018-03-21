#include "inc/TIMERS.h"

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

void delay_us(uint32_t delay){
	delay*=F_CPU_US;
	volatile uint32_t elapsedTime;
	uint32_t startTime = NVIC_ST_CURRENT_R;
	do{
		elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
	}while(elapsedTime <= delay);
}
