#ifndef _EEPROM_H_
#define _EEPROM_H_

#include<stdint.h>
#include"tm4c123gh6pm.h"

#define EEPROM_INIT_OK 0
#define EEPROM_INIT_ERROR 2


uint32_t EEPROM_init(void);

uint32_t EEPROM_read(uint8_t block, uint8_t offset);

void EEPROM_write(uint8_t block, uint8_t offset, uint32_t word);
/*
 I didn't understand how does the EEPROMSIZE works yet. But when I do, I'll change the following functions.
*/
uint8_t EEPROM_getblocks(uint8_t block, uint8_t offset);

uint8_t EEPROM_getwords(uint8_t block, uint8_t offset);

#endif
