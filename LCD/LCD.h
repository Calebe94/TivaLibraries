#ifndef _LCD_H_
#define  _LCD_H_

#include "TIMERS.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Pins.h"

/*LDC Commands, check Hitachi's HD44780 datasheet to more info*/
#define	LCD_CLEAR			0x01
#define	LCD_HOME			0x02
#define	LCD_ENTRY			0x04
#define	LCD_CTRL			0x08
#define	LCD_CDSHIFT			0x10
#define	LCD_FUNC			0x20
#define	LCD_CGRAM			0x40
#define	LCD_DGRAM			0x80
#define LCD_WAKE_UP 		0x30
#define	LCD_ENTRY_SH		0x01
#define	LCD_ENTRY_ID		0x02
#define	LCD_BLINK_CTRL		0x01
#define	LCD_CURSOR_CTRL		0x02
#define	LCD_DISPLAY_CTRL	0x04
#define	LCD_FUNC_F			0x04
#define	LCD_FUNC_N			0x08
#define	LCD_FUNC_DL			0x10
#define	LCD_CDSHIFT_RL		0x04

static const int rowOffset [4] = { 0x00, 0x40, 0x14, 0x54 };

void LCD_init(void);

void LCD_command(uint8_t command);

void LCD_clear(void);

void LCD_home(void);

void LCD_position(uint8_t x, uint8_t y);

void LCD_write(const unsigned char command);

void LCD_print(char *string);

#endif
