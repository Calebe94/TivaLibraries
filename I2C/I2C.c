#include "I2C.h"

I2C I2C0_master_init(void){
    I2C device;
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;
    while ((SYSCTL_RCGCI2C_R&SYSCTL_RCGCI2C_R0) == 0);
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOB;
    while((SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOB)==0);
    GPIO_PORTB_AFSEL_R|= (I2C0SCL|I2C0SDA);
    GPIO_PORTB_DEN_R  |= (I2C0SCL|I2C0SDA);
    GPIO_PORTB_ODR_R  |= (I2C0SDA);
    I2C0_MCR_R = I2C_MCR_MFE;
    I2C0_MTPR_R = ((F_CPU)/(20* I2C_SCL_CLK))-1;
    device.data = &I2C0_MDR_R;
    device.master_control_status = &I2C0_MCS_R;
    return device;
}

void I2C_setClock(I2C *device, uint32_t clock){
    *device->time_period_register = (uint8_t)((F_CPU)/(20* clock))-1;
}

void I2C_master_beginTransmission(I2C *device, uint8_t slave_address, uint8_t operation){
    *device->address = (slave_address<<1)|operation;
}

void I2C_master_endTransmission(I2C *device){
    *device->master_control_status |= (I2C_MCS_STOP);
}

void I2C0_interrupt_enable(void){
    NVIC_EN0_R  |= ( 1 << ( INT_I2C0 - 16) );
    NVIC_PRI2_R |= NVIC_PRI2_INT8_M;
    I2C0_MIMR_R = I2C_MIMR_IM;
}

void I2C0_interrupt_disable(void){
    I2C0_MIMR_R&=~(I2C_MIMR_IM);
}

void I2C_master_write(I2C *device, uint8_t slave_address, uint8_t *byte){
    while(((*device->master_control_status)&I2C_MCS_BUSY)==1);
    *device->address = ( slave_address << 1 ) | ( I2C_TX );
    *device->data = (uint8_t)*byte;
    *device->master_control_status = ( I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN);
    while(((*device->master_control_status)&I2C_MCS_BUSY)==1);
}

uint8_t I2C_master_read(I2C *device, uint8_t slave_address){
    while(((*device->master_control_status)&I2C_MCS_BUSY)==1);
    (*device->address) = ( ( slave_address << 1 ) | ( I2C_RX ) );
    (*device->master_control_status) = ( I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN);
    while(((*device->master_control_status)&I2C_MCS_BUSY)==1);
    return (uint8_t)( (*device->data)) & 0xFF );
}
