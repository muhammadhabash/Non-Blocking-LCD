#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/STD_types.h"
#include "../../MCAL/GPIO/GPIO.h"

#define RS (PIN1)
#define RW (PIN2)
#define EN (PIN3)
#define D4 (PIN4)
#define D5 (PIN5)
#define D6 (PIN6)
#define D7 (PIN7)

#define FORCE_RESET           (0x03)
#define FOUR_BITS_MODE        (0x02)
#define SINGLE_LINE           (0x20)
#define DISPLAY_CLEAR         (0x01)
#define DISPLAY_CURSOR_ON     (0x0E)
#define DISPLAY_OFF           (0x08)
#define ENTRY_MODE            (0x06)
#define DISPLAY_ON_CURSOR_OFF (0x0C)
#define LEFT                  (0x10)
#define RIGHT                 (0x14)
#define DATA_REGISTER         (*((volatile uint8_t*) GPIO_DATA_R))
#define LCD_INITIALIZED       (1)
#define LCD_NOT_INITIALIZED   (0) 
#define TRUE                  (1)
#define FALSE                 (0)
#define LCD_CMD_READY         (1)
#define LCD_CMD_NOT_READY     (0)
#define LCD_DATA_NOT_SENT     (0)
#define LCD_DATA_SENT         (1)
 
 typedef enum{
	 
	 POWER_UP_STATE            = 0,
	 CFGR_OUTPUT_PINS_STATE    = 1,
	 FISRT_FORCE_RESET_STATE   = 2,
	 SECOND_FORCE_RESET_STATE  = 3,
	 THIRD_FORCE_RESET_STATE   = 4,
	 CFGR_FOUR_BITS_MODE_STATE = 5,	
	 TURN_DISPLAY_OFF_STATE    = 6,
	 DISPLAY_CLEAR_STATE       = 7,
	 CFGR_ENTRY_MODE_STATE     = 8,
	 CFGR_DISPLAY_CURSOR_STATE = 9
	 }EN_LCDinitStates_t;

typedef enum{
	
	LOADING_HIGHER_NIPPLE_CMD_STATE = 0,
	LOADING_LOWER_NIPPLE_CMD_STATE  = 1
	}EN_LCDsendCMDstates_t;
	
typedef enum{
	
	LOADING_HIGHER_NIPPLE_DATA_STATE = 0,
	LOADING_LOWER_NIPPLE_DATA_STATE  = 1
	}EN_LCDsendDataStates_t;
	
	
	 
void LCD_init();
uint8_t LCD_data(uint8_t u8_data);
uint8_t LCD_nonBlockingInit(void);
uint8_t LCD_nonBlockingSendCMD(uint8_t u8_command);




#endif