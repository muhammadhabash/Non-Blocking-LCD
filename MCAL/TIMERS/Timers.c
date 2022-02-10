#include "TIMERS.h"
#include "../../LIB/BIT_manipulation.h"
#include "../../MCAL/GPIO/GPIO.h"
#include <math.h>

volatile uint32_t gu32_OVcounts0 = INITIAL_VAL;
volatile uint32_t gu32_OVcounts2 = INITIAL_VAL;

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	gu32_OVcounts0++;
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	gu32_OVcounts2++;
}
void OVI0_init(void)
{
	BIT_SET(TIMSK_R,PIN0);
	BIT_SET(STATUS_R,PIN7); 
}

void OCI0_init(void)
{
	BIT_SET(TIMSK_R,PIN1);
	BIT_SET(STATUS_R,PIN7);
}

void OVI2_init(void)
{
	BIT_SET(TIMSK_R,PIN6);
	BIT_SET(STATUS_R,PIN7);
}

void OCI2_init(void)
{
	BIT_SET(TIMSK_R,PIN7);
	BIT_SET(STATUS_R,PIN7);
}

EN_timer0DelayStatus_t TIMER0_msdelay(uint16_t mseconds)
{	
	static volatile uint32_t u32_ticks;
	EN_timer0DelayStatus_t EN_delayStatus;
	static EN_timer0DelayStatus_t EN_timer0Status = TIMER0_DELAY_NSTARTED;
	
	if(TIMER0_DELAY_NSTARTED == EN_timer0Status)
	{
		u32_ticks = round(( ( mseconds / PERIODIC_TIME_IN_MS ) / COUNTS_PER_OVF ));
		OVI0_init();                                         //Enabling system interrupt and flag for overflow for timer 0
		TIMER0_start(PRESCALE_8);                            //Prescaler of one that yields 8MHz frequency
		EN_timer0Status  = TIMER0_DELAY_STARTED;
	}
	else if(gu32_OVcounts0 == u32_ticks)
	{
		TIMER0_stop();
		EN_timer0Status  = TIMER0_DELAY_NSTARTED;
		EN_delayStatus   = TIMER0_DELAY_FINISHED;
		gu32_OVcounts0   = INITIAL_VAL;
	}
	else
	    EN_delayStatus   = TIMER0_DELAY_NFINISHED;
		
	return EN_delayStatus;
}

void TIMER0_start(uint16_t u16_prescale)
{
	if (PRESCALE_1 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS00);
	}
	else if (PRESCALE_8 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS01);	
	}
	else if (PRESCALE_32 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS01) | (1<<CS00);
	}
	else if (PRESCALE_64 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS02);
	}
	else if (PRESCALE_128 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS02) | (1<<CS00);
	}
	else if (PRESCALE_256 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS02) | (1<<CS01);
	}
	else if (PRESCALE_1028 == u16_prescale)
	{
		TIMER0_CTL_R |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	}
}

void TIMER0_stop(void)
{
	TIMER0_CTL_R = INITIAL_VAL;
}

EN_timer2DelayStatus_t TIMER2_msdelay(uint16_t mseconds)
{
	static volatile uint32_t u32_ticks;
	EN_timer2DelayStatus_t EN_delayStatus;
	static EN_timer2DelayStatus_t EN_timer2Status = TIMER2_DELAY_NSTARTED;
	
	if(TIMER0_DELAY_NSTARTED == EN_timer2Status)
	{
		u32_ticks = round(( ( mseconds / PERIODIC_TIME_IN_MS ) / COUNTS_PER_OVF ));
		OVI2_init();                                         //Enabling system interrupt and flag for overflow for timer 0
		TIMER2_start(PRESCALE_8);                            //Prescaler of one that yields 8MHz frequency
		EN_timer2Status  = TIMER0_DELAY_STARTED;
	}
	else if(gu32_OVcounts2 == u32_ticks)
	{
		TIMER2_stop();
		EN_timer2Status  = TIMER2_DELAY_NSTARTED;
		EN_delayStatus   = TIMER2_DELAY_FINISHED;
		gu32_OVcounts2   = INITIAL_VAL;
	}
	else
	EN_delayStatus   = TIMER2_DELAY_NFINISHED;
	
	return EN_delayStatus;
}

void TIMER2_start(uint16_t u16_prescale)
{
	if (PRESCALE_1 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS00);
	}
	else if (PRESCALE_8 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS01);
	}
	else if (PRESCALE_32 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS01) | (1<<CS00);
	}
	else if (PRESCALE_64 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS02);
	}
	else if (PRESCALE_128 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS02) | (1<<CS00);
	}
	else if (PRESCALE_256 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS02) | (1<<CS01);
	}
	else if (PRESCALE_1028 == u16_prescale)
	{
		TIMER2_CTL_R |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	}
}

void TIMER2_stop(void)
{
	TIMER2_CTL_R = INITIAL_VAL;
}