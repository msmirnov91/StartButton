/*
 * Timers.c
 *
 * Created: 08.05.2021 16:07:46
 *  Author: mikhail
 */ 

#include "Timers.h"
#include "Defines.h"
#include <avr/io.h>

void setCTCMode(volatile uint8_t* reg)
{
	if (*reg == TCCR1B)
	{
		*reg |= 1 << WGM12;
		*reg &= ~(1 << WGM13);
	}	
}

void startTimerDiv1024(volatile uint8_t* reg)
{
	if (*reg == TCCR1B)
	{
		*reg |= 1 << CS12;
		*reg &= ~(1 << CS11);
		*reg |= 1 << CS10;
	}
}

void initCutoffTimer(void)
{
	setCTCMode(&TCCR1B);
	resetCutoffTimer();
	
	OCR1A = OCR_4_SEC;
}

void setupTimerInterrupts(void)
{
	initCutoffTimer();
	
	TIMSK1 |= 1 << OCIE1A;  // enable timer interrupts
	TIFR1 |= 1 << OCF1A;  // clear timer interrupts flags
}

void resetCutoffTimer(void)
{
	TCNT1 = TCNT_4_SEC;
	TCCR1B &= STOP_TIMER_MASK;
}

void startCutoffTimer(void)
{
	startTimerDiv1024(&TCCR1B);
}
