#include <tm4c123gh6pm.h>

#define F_CPU_US 16
#define ENABLE GPIO_PORTA_DATA_R^=0x40
#define PWM_FREQ 399

void pwm_init();

void pwm_1(uint8_t estado);

void pwm_2(uint8_t estado);

void pwm_3(uint8_t estado);

void pwm_4(uint8_t estado);
