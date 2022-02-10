#ifndef GPIO_H_
#define GPIO_H_

#include "../../LIB/STD_types.h"

/****************************************************************************/
/*                            User Defined Macros                           */
/****************************************************************************/
 
#define PORTA                 (0)
#define PORTB                 (3)
#define PORTC                 (6)
#define PORTD                 (9)

#define OUTPUT                (1)
#define INPUT                 (0)

#define HIGH                  (1)
#define LOW                   (0)

#define PIN0                  (0)
#define PIN1                  (1)
#define PIN2                  (2)
#define PIN3                  (3)
#define PIN4                  (4)
#define PIN5                  (5)
#define PIN6                  (6)
#define PIN7                  (7)

#define LEAST_SIGNIFICANT_BIT (0)
#define MOST_SIGNIFICANT_BIT  (7)

/****************************************************************************/
/*                            Functions Prototypes                          */
/****************************************************************************/

uint8_t GPIO_setHigh(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_setLow(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_toggle(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_dir(uint8_t u8_port, uint8_t u8_bit, uint8_t u8_mode);
uint8_t GPIO_read(uint8_t u8_port, uint8_t u8_bit);


#endif 