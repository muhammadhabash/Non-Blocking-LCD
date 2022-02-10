#include "GPIO.h"
#include "../../LIB/ATMEGA32.h"
#include "../../LIB/BIT_manipulation.h"
#include "../../LIB/ERROR_states.h"

uint8_t GPIO_setHigh(uint8_t u8_port, uint8_t u8_bit)
{
	uint8_t* u8_reg;
	if (u8_port >= PORTA && u8_port <= PORTD)
	{
		u8_reg = (uint8_t*)(GPIO_DATA_R - (u8_port - PORTA));
		if ( u8_bit >= LEAST_SIGNIFICANT_BIT && u8_bit <= MOST_SIGNIFICANT_BIT )
		{
			GPIO_SET(u8_reg,u8_bit);
		}
		else 
		{
			return WRONG_PIN;
		}
	}
	else
	{
		return WRONG_PORT;
	}
	return NO_ERRORS;
}

uint8_t GPIO_toggle (uint8_t u8_port, uint8_t u8_bit)
{
	uint8_t* u8_reg;
	if (u8_port >= PORTA && u8_port <= PORTD)
	{
		u8_reg = (uint8_t*)(GPIO_DATA_R - (u8_port - PORTA));
		if ( u8_bit >= LEAST_SIGNIFICANT_BIT && u8_bit <= MOST_SIGNIFICANT_BIT )
		{
			GPIO_TOGGLE(u8_reg,u8_bit);
		}
		else
		{
			return WRONG_PIN;
		}
	}
	else 
	{
		return WRONG_PORT;
	}
	return NO_ERRORS;
}

uint8_t GPIO_dir(uint8_t u8_port, uint8_t u8_bit, uint8_t u8_mode)
{
	uint8_t* u8_reg;
	if (u8_port >= PORTA && u8_port <= PORTD)
	{
		u8_reg = (uint8_t*)(GPIO_DIR_R - (u8_port -PORTA));
		if ( u8_bit >= LEAST_SIGNIFICANT_BIT && u8_bit <= MOST_SIGNIFICANT_BIT )
		{
			if (OUTPUT == u8_mode)
			{
				GPIO_SET(u8_reg,u8_bit);	
			}
			else if (INPUT == u8_mode)
			{
				GPIO_CLEAR(u8_reg,u8_bit);
			}
			else
			{
				return WRONG_MODE;
			}
		}
		else
		{
			return WRONG_PIN;
		}
	}
	else 
	{
		return WRONG_PORT;
	}
	return NO_ERRORS;
}

uint8_t GPIO_setLow(uint8_t u8_port, uint8_t u8_bit)
{
	uint8_t* u8_reg;
	if (u8_port >= PORTA && u8_port <= PORTD)
	{
		u8_reg = (uint8_t*)(GPIO_DATA_R - (u8_port - PORTA));
		if ( u8_bit >= LEAST_SIGNIFICANT_BIT && u8_bit <= MOST_SIGNIFICANT_BIT )
		{
			GPIO_CLEAR(u8_reg, u8_bit);
		}
		else 
		{
			return WRONG_PIN;
		}
	}
	else 
	{
		return WRONG_PORT;
	}
	return NO_ERRORS;
}

uint8_t GPIO_read(uint8_t u8_port, uint8_t u8_bit)
{
	uint8_t* u8_reg;
	if (u8_port >= PORTA && u8_port <= PORTD)
	{
		u8_reg = (uint8_t*)(GPIO_BITS_R - (u8_port - PORTA));
		if (GPIO_IS_SET(u8_reg,u8_bit))
		{
			return HIGH;
		}
		else 
		{
			return LOW;
		}
	}
	else
	{
		return WRONG_PORT;
	}
	return 0;
}