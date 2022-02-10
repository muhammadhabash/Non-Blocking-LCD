#include "LED.h"
#include "../../MCAL/GPIO/GPIO.h"

void LED_en(uint8_t u8_port, uint8_t u8_bit)
{
	GPIO_dir(u8_port,u8_bit,OUTPUT);
}

void LED_on(uint8_t u8_port, uint8_t u8_bit)
{
	GPIO_setHigh(u8_port,u8_bit);
}

void LED_off(uint8_t u8_port, uint8_t u8_bit)
{
	GPIO_setLow(u8_port,u8_bit);
}

void LED_toggle (uint8_t u8_port, uint8_t u8_bit)
{
	GPIO_toggle(u8_port,u8_bit);
}