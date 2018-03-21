#ifndef __ADC_H__
#define __ADC_H__

#include<stdint.h>
#include"tm4c123gh6pm.h"
#include"Pins.h"

void ADC_Init();

unsigned long ADC_Read(unsigned int AINx);

#endif
