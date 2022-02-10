#include "KEYPAD.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/TIMERS/TIMERS.h"
#include "../../HAL/LED/LED.h"


void KEYPAD_init(void)
{
	//Setting rows as outputs
	GPIO_dir(PORTC,2,OUTPUT);
	GPIO_dir(PORTC,3,OUTPUT);
	GPIO_dir(PORTC,4,OUTPUT);
	//Setting rows initial values to high
	GPIO_setHigh(PORTC,2);
	GPIO_setHigh(PORTC,3);
	GPIO_setHigh(PORTC,4);
	//Setting columns as inputs
	GPIO_dir(PORTC,5,INPUT);
	GPIO_dir(PORTC,6,INPUT);
	GPIO_dir(PORTC,7,INPUT);
	//Setting columns initial values to high
	GPIO_setHigh(PORTC,5);
	GPIO_setHigh(PORTC,6);
	GPIO_setHigh(PORTC,7);
}

EN_keypadStatus_t KEYPAD_scan(uint8_t* pressedKey)
{
	uint8_t u8_button = ONE, u8_row = FIRST_ROW, u8_column = FIRST_COLUMN;
	EN_keypadStatus_t EN_keypadStatus;
	
	for ( u8_row = FIRST_ROW ; u8_row <= ROWS ; u8_row++)
	{
		GPIO_setLow(PORTC,u8_row);
		for (u8_column = FIRST_COLUMN ; u8_column <= COLUMNS ; u8_column++)
		{
			if(LOW == GPIO_read(PORTC,u8_column))
			{
				*(pressedKey)   = u8_button;
				EN_keypadStatus = DEBOUNCING;
				break;
			}
			else
			{
				//*(pressedKey) = 0;
				EN_keypadStatus = NOT_PRESSED;
				u8_button++;
			}
		}
		GPIO_setHigh(PORTC,u8_row);
		if(DEBOUNCING == EN_keypadStatus)
		{
			break;
		}
		else
		{
			
		}
	}
	return EN_keypadStatus;
}

void KEYPAD_nonBlockingScan(uint8_t* u8_pressedKey)
{
	static EN_keypadStatus_t EN_keypadStatus = NOT_PRESSED;
	switch(EN_keypadStatus)
	{
		case NOT_PRESSED:
		
		EN_keypadStatus = KEYPAD_scan(u8_pressedKey);
		
		break;
		
		case DEBOUNCING:
		
		if((TIMER2_DELAY_FINISHED == TIMER2_msdelay(20)))
		{
			EN_keypadStatus = KEYPAD_scan(u8_pressedKey);
		}
		
		break;
	}
}