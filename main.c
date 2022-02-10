#include "./HAL/LCD/LCD.h"
#include "./MCAL/TIMERS/Timers.h"
#include "./HAL/KEYPAD/keypad.h"

int main()
{
	LED_en(PORTB,PIN4);
	uint8_t u8_initOK = FALSE;
	static uint8_t u8_buffIndex = INITIAL_VAL;
	uint8_t u8_returnState;
	uint8_t* pu8_buffer = "123456789";
	while(1)
	{
		if(!(u8_initOK) && (LCD_INITIALIZED == LCD_nonBlockingInit()))
		{
			u8_initOK = TRUE;
		}
		else if (u8_initOK)
		{
			u8_returnState = LCD_data(pu8_buffer[u8_buffIndex]);
			if(u8_returnState == TRUE)
			{
				u8_buffIndex++;
			}
			if(8 == u8_buffIndex)
			{
				while(1);
			}
		}
	}
}