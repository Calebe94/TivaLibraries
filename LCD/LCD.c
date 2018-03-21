#include"inc/LCD.h"

void LCD_init(void){
	//SysTick_Init();
	SYSCTL_RCGCGPIO_R|= 1<<0|1<<1;// PortA e PortB
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_DR8R_R|=0xFF;
	GPIO_PORTA_DIR_R |= EN|RS;
	GPIO_PORTA_DEN_R |= EN|RS;
	GPIO_PORTA_DR8R_R|=EN|RS;

	LCDCMD&=~(EN|RS);
	delay_us(15000);
	LCD_command(0x30);
	delay_us(15000);
	LCD_command(0x30);
	delay_us(160);
	LCD_command(0x30);
	delay_us(160);
	LCD_command(0x38);
	LCD_command(0x10);
	LCD_command(0x0C);
	LCD_command(0x06);
}

void LCD_command(uint8_t command){
	LCDDATA = command;
	LCDCMD&=~(EN|RS);
	delay_us(6);
	LCDCMD|=EN;
	delay_us(6);
	LCDCMD&=~(EN|RS);
	delay_us(40);
}

void LCD_clear(void){
	LCD_command(0x01);
	delay_us(1600);
	LCD_command(0x02);
	delay_us(1600);
}

void LCD_home(void){
	LCD_command(LCD_HOME);
	delay_us(5000);
}

void LCD_position(uint8_t x, uint8_t y){
	LCD_command((x-1)+(LCD_DGRAM|rowOffset[y-1]));
}

void LCD_write(const unsigned char command){
	LCDDATA = (unsigned char)command&0xFF;
	LCDCMD|= RS;
	delay_us(6);
	LCDCMD|= (EN|RS);
	delay_us(6);
	LCDCMD&=~EN; // EN = 0. RS = 1
	delay_us(40);
}

void LCD_print(char *string){
	while(*string)	LCD_write(*(string++));
}
