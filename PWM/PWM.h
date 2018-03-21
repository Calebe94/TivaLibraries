#ifndef  _PWM_H_
#define _PWM_H_

#include<stdint.h>
#include"tm4c123gh6pm.h"
//#include "Pins.h"

//void PWM_init(uint16_t frequency, uint8_t porcentage);
void PWM_init(uint8_t porcentage);

//void PWM_write(uint16_t frequency, uint8_t porcentage);
void PWM_write(uint8_t porcentage);

#endif
