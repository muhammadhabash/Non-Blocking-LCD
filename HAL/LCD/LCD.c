#include "LCD.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/TIMERS/TIMERS.h"

#include <math.h>

uint8_t LCD_nonBlockingInit(void){
	
	static EN_LCDinitStates_t EN_LCDinitStates = POWER_UP_STATE;
	static uint8_t LCD_initStatus = LCD_NOT_INITIALIZED;
	static uint8_t u8_cmdSent = FALSE;
	 
	switch(EN_LCDinitStates)
	{
		case POWER_UP_STATE:
		if(TIMER0_DELAY_FINISHED == TIMER0_msdelay(100))
		{
			EN_LCDinitStates = CFGR_OUTPUT_PINS_STATE;
		}
		break;
		
		case CFGR_OUTPUT_PINS_STATE:
		GPIO_dir(PORTA,RS,OUTPUT);
		GPIO_dir(PORTA,RW,OUTPUT);
		GPIO_dir(PORTA,EN,OUTPUT);
		GPIO_dir(PORTA,D4,OUTPUT);
		GPIO_dir(PORTA,D5,OUTPUT);
		GPIO_dir(PORTA,D6,OUTPUT);
		GPIO_dir(PORTA,D7,OUTPUT);
		if(TIMER0_DELAY_FINISHED == TIMER0_msdelay(100))
		{
			EN_LCDinitStates = FISRT_FORCE_RESET_STATE;
		}
		break;
		
		case FISRT_FORCE_RESET_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(FORCE_RESET)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = SECOND_FORCE_RESET_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case SECOND_FORCE_RESET_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(FORCE_RESET)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = THIRD_FORCE_RESET_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case THIRD_FORCE_RESET_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(FORCE_RESET)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = CFGR_FOUR_BITS_MODE_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case CFGR_FOUR_BITS_MODE_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(FOUR_BITS_MODE)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = TURN_DISPLAY_OFF_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case TURN_DISPLAY_OFF_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(DISPLAY_OFF)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = DISPLAY_CLEAR_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case DISPLAY_CLEAR_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(DISPLAY_CLEAR)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = CFGR_ENTRY_MODE_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case CFGR_ENTRY_MODE_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(ENTRY_MODE)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_LCDinitStates = CFGR_DISPLAY_CURSOR_STATE;
			u8_cmdSent = FALSE;
		}
		break;
		
		case CFGR_DISPLAY_CURSOR_STATE:
		if(!(u8_cmdSent) && (LCD_CMD_READY == LCD_nonBlockingSendCMD(DISPLAY_ON_CURSOR_OFF)))
		{
			u8_cmdSent = TRUE;
		}
		else if((u8_cmdSent) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			LCD_initStatus = LCD_INITIALIZED;
			u8_cmdSent = FALSE;
		}
		break;
	}
	return LCD_initStatus;
}

uint8_t LCD_nonBlockingSendCMD(uint8_t u8_command)
{
	static EN_LCDsendCMDstates_t EN_CMDstates = LOADING_HIGHER_NIPPLE_CMD_STATE;
	static uint8_t u8_firstDelayFinished = FALSE;
	static uint8_t u8_cmdLoaded = FALSE;
	static uint8_t u8_LCDcmdState;
	
	switch(EN_CMDstates)
	{
		case LOADING_HIGHER_NIPPLE_CMD_STATE:
		
		u8_LCDcmdState = LCD_CMD_NOT_READY;
		if(!(u8_cmdLoaded))
		{
			DATA_REGISTER  = (DATA_REGISTER & (0x0F)) |  (u8_command & (0xF0));
			u8_cmdLoaded = TRUE;
		}
		GPIO_setLow(PORTA,RS);
		GPIO_setHigh(PORTA,EN);
		if(!(u8_firstDelayFinished) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			u8_firstDelayFinished = TRUE;
			GPIO_setLow(PORTA,EN);
		}
		else if((u8_firstDelayFinished) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_CMDstates = LOADING_LOWER_NIPPLE_CMD_STATE;
			u8_firstDelayFinished = FALSE;
			u8_cmdLoaded = FALSE;
		}
		else
		{
			
		}
		break;
		
		case LOADING_LOWER_NIPPLE_CMD_STATE:
		
		if(!(u8_cmdLoaded))
		{
		    DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_command << 4);
			u8_cmdLoaded = TRUE;
		}
		GPIO_setHigh(PORTA,EN);
		if(!(u8_firstDelayFinished) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			u8_firstDelayFinished = TRUE;
			GPIO_setLow(PORTA,EN);
		}
		else if((u8_firstDelayFinished) && (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10)))
		{
			EN_CMDstates = LOADING_HIGHER_NIPPLE_DATA_STATE;
			u8_firstDelayFinished = FALSE;
			u8_cmdLoaded = FALSE;
			u8_LCDcmdState = LCD_CMD_READY;
		}
		else
		{
			
		}
		break;
	}
	return u8_LCDcmdState;
}

uint8_t LCD_data(uint8_t u8_data){
	
	static uint8_t u8_higherNippleSent = FALSE;
	static uint8_t u8_dataLoaded       = FALSE;
	static uint8_t u8_dataSent         = FALSE;
	
	/*************************/
	/* Sending higher nipple */
	/*************************/
	if(u8_higherNippleSent != TRUE)
	{
		u8_dataSent = FALSE;
		
		if(u8_dataLoaded != TRUE)
		{
			DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data & (0xF0));
			u8_dataLoaded = TRUE;
		}
		GPIO_setHigh(PORTA,RS);
		GPIO_setHigh(PORTA,EN);
		if (TIMER0_DELAY_FINISHED == TIMER0_msdelay(10))
		{
			GPIO_setLow(PORTA,EN);
			u8_higherNippleSent = TRUE;
			u8_dataLoaded = FALSE;
		}
	}
	
	/************************/
	/* Sending lower nipple */
	/************************/
	else if (u8_higherNippleSent == TRUE)
	{
		if(u8_dataLoaded != TRUE)
		{
			DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data << 4);
			u8_dataLoaded = TRUE;
		}
		GPIO_setHigh(PORTA,EN);
		if(TIMER0_DELAY_FINISHED == TIMER0_msdelay(10))
		{
			GPIO_setLow(PORTA,EN);
			u8_higherNippleSent = FALSE;
			u8_dataLoaded       = FALSE;
			u8_dataSent         = TRUE;
		}
	} 
	return u8_dataSent;
}