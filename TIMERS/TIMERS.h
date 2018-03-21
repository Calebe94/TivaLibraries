#ifndef _TIMER_H_
#define _TIMER_H_
#include<stdint.h>
#include "tm4c123gh6pm.h"

#define F_CPU_US 16

void SysTick_Init(void);

void delay_us(uint32_t delay);

#endif
