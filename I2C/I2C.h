#ifndef _I2C_H_
#define  _I2C_H_

#define F_CPU 		16000000

#define I2C0SCL 	(1<<2) // PB2
#define I2C0SDA 	(1<<3) // PB3

#define I2C1SCL		(1<<6) // PA6
#define I2C1SDA		(1<<7) // PA7

#define I2C2SCL		(1<<4) // PE4
#define I2C2SDA		(1<<5) // PE5

#define I2C3SCL		(1<<0) // PD0
#define I2C3SDA		(1<<1) // PD1

#define I2C_SCL_CLK 100000

#define I2C_RX       (1)
#define I2C_TX       (0)

typedef struct{
	uint8_t  time_period;
	uint32_t *data;
	uint32_t *master_control_status;
	uint32_t *time_period_register;
	uint32_t *address;
}I2C;

#endif
