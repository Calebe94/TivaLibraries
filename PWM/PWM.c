#include <stdint.h>
#include <tm4c123gh6pm.h>

#include "PWM.h"

void pwm_init()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF | SYSCTL_RCGC2_GPIOE;
    while( SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOF==0x00 && SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOE==0x00 );
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
    GPIO_PORTF_AFSEL_R |= 0b00110;
    GPIO_PORTF_PCTL_R  |= GPIO_PCTL_PF1_M1PWM5 | GPIO_PCTL_PF2_M1PWM6;
    GPIO_PORTF_DIR_R |= 0b00110;
    GPIO_PORTF_DATA_R = 0;
    GPIO_PORTF_DEN_R |= 0b10111;
    GPIO_PORTF_PUR_R |= 0b10001;

    GPIO_PORTE_DIR_R |= 0b110000;
    GPIO_PORTE_AFSEL_R |= 0b110000;
    GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_M0PWM4 | GPIO_PCTL_PE5_M1PWM3;
    GPIO_PORTE_DATA_R = 0;
    GPIO_PORTE_DEN_R |= 0b110001;
    GPIO_PORTE_PUR_R |= 0b0001;

//  PE4, PE5, PF1, PF2
    int delay = 0;
    for(delay = 0; delay < 20000; delay++);

    /* PWM Port E
     * */
    SYSCTL_RCGCPWM_R |= 0x03;
    while(SYSCTL_RCGCPWM_R&0x03 == 0);

    PWM0_2_GENA_R = 0x00C8;
    PWM1_1_GENB_R = 0x0C08;
    PWM1_2_GENB_R = 0x0C08;
    PWM1_3_GENA_R = 0x00C8;

    PWM0_2_LOAD_R = PWM_FREQ;
    PWM1_1_LOAD_R = PWM_FREQ;
    PWM1_2_LOAD_R = PWM_FREQ;
    PWM1_3_LOAD_R = PWM_FREQ;

    PWM0_2_CTL_R = 0x01;
    PWM1_1_CTL_R = 0x01;
    PWM1_2_CTL_R = 0x01;
    PWM1_3_CTL_R = 0x01;

    PWM0_ENABLE_R = 0x10;
    PWM1_ENABLE_R = 0x68;
}

void pwm_1(uint8_t estado)
{
    PWM0_2_CMPA_R = (uint32_t)(PWM_FREQ*(estado-1))/100;
}

void pwm_2(uint8_t estado)
{
    PWM1_1_CMPB_R = (uint32_t)(PWM_FREQ*(estado-1))/100;
}

void pwm_3(uint8_t estado)
{
    PWM1_2_CMPB_R = (uint32_t)(PWM_FREQ*(estado-1))/100;
}

void pwm_4(uint8_t estado)
{
    PWM1_3_CMPA_R = (uint32_t)(PWM_FREQ*(estado-1))/100;
}
