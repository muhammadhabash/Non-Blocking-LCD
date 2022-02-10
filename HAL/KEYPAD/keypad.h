#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/STD_types.h"

#define HIGH              (1)
#define LOW               (0)
#define ONE               (0x31)
#define FIRST_ROW         (2)
#define FIRST_COLUMN      (5)
#define ROWS              (4)
#define COLUMNS           (7)
#define NO_BUTTON_PRESSED (0)
#define FALSE             (0)
#define TRUE              (1)

typedef enum{
	NOT_PRESSED = 0,
	DEBOUNCING  = 1
	}EN_keypadStatus_t;
	
void KEYPAD_init(void);
EN_keypadStatus_t KEYPAD_scan(uint8_t* u8_pressedKey);
void KEYPAD_nonBlockingScan(uint8_t* u8_pressedKey);



#endif