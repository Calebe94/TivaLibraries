#include"inc/ADC.h"

void ADC_Init(){
    SYSCTL_RCGCADC_R |= 0b01;
    while(SYSCTL_RCGCADC_R&0b01==0);

    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGC2_GPIOE;
    while(SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOE==0);
    GPIO_PORTE_DIR_R  |= (MOTOR_SIGNAL | LDR_SIGNAL);
    GPIO_PORTE_AFSEL_R|= (~MOTOR_SIGNAL | ~LDR_SIGNAL);
    GPIO_PORTE_DEN_R  &= (MOTOR_SIGNAL | LDR_SIGNAL);
    GPIO_PORTE_AMSEL_R|= (~MOTOR_SIGNAL | ~LDR_SIGNAL);

    ADC0_ACTSS_R&=0b0000; // ADC Active Sample Sequencer. Check pg 821
    ADC0_EMUX_R&=~0x0F00; // ADC Event Multiplexer Select. Check pg. 833
    ADC0_SSCTL2_R=0b01100110; // ADC Sample Sequence Control 2. Check pg. 868
    ADC0_ACTSS_R|=0b0100;
}

unsigned long ADC_Read(unsigned int AINx){
    unsigned long result=0;
    ADC0_SSMUX2_R = AINx; // ADC Sample Sequence Input Multiplexer Select 2 pg. 867
    ADC0_PSSI_R=0b0100; // ADC Processor Sample Sequence Initiate. Check pg.845
    while(ADC0_RIS_R&0b0100==0); // ADC Raw Interrupt Status. Check pg. 823
    result = ADC0_SSFIFO2_R&0b111111111111; // ADC Sample Sequence Result FIFO 2. Check pg. 860
    ADC0_ISC_R = 0b0100; // ADC Interrupt Status and Clear. Check pg. 828
    return result;
}
