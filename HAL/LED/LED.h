#ifndef LED_H_
#define LED_H_

/***************************************************/
/*           Files Inclusions                      */
/***************************************************/

#include "../../LIB/STD_types.h"

/***************************************************/
/*           Prototypes                            */
/***************************************************/
                                                    /******************************************************************************************/
void LED_en(uint8_t u8_port, uint8_t u8_bit);       /* This function enables the given pin in the given u8_port and sets it as output         */
void LED_on(uint8_t u8_port, uint8_t u8_bit);       /* This function sets the given pin in the given u8_port to a logical HIGH                */
void LED_off(uint8_t u8_port, uint8_t u8_bit);      /* This function sets the given pin in the given u8_port to a logical HIGH                */
void LED_toggle (uint8_t u8_port, uint8_t u8_bit);  /* This function toggles the the value of the given in the given port using bit wise XOR  */
                                                    /******************************************************************************************/
/***************************************************/


#endif