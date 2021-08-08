/*
 * Interrupts.c
 *
 * Created: 04.11.2020 22:53:28
 *  Author: mikhail
 */ 

#include "Interrupts.h"
#include "Defines.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

volatile GlobalData globalData;

EMPTY_INTERRUPT(BADISR_vect);

ISR(BUTTON_INTERRUPT_VEC)
{
	/* 
	    cannot call functions from interrupt handler => 
	    have to check if the button is still pressed and
		make delay in such a freaky way 
	*/
	int isStillPressed = (PIND & (1 << BUTTON_PIN)) != 0;
	for (int i = 0; i < DEBOUNCE_CHECK_AMOUNT; i++)
	{
		for (int i = 0; i < DEBOUNCE_DELAY_ITERATIONS; i++);
		int currentIsStillPressed = (PIND & (1 << BUTTON_PIN)) != 0;
		isStillPressed = isStillPressed & currentIsStillPressed;
	}

	if (isStillPressed && !globalData.engineIsRunning)
	{
		globalData.turnOnStarter = 1;
	}
}

ISR(TACH_INTERRUPT_VEC)
{
	globalData.pulsesAmount += 1;
}

ISR(CUTOFF_TIMER_INTERRUPT_VEC)
{
	globalData.turnOnStarter = 0;
}

ISR(RPM_COUNT_TIMER_INTERRUPT_VEC)
{
	globalData.rpmCountTimerInterrupts += 1;
	if (globalData.rpmCountTimerInterrupts == INTERRUPTS_PER_1SEC) {
		if (globalData.pulsesAmount > ENGINE_ON_LEVEL) {
			globalData.engineIsRunning = 1;
		}
		else {
			globalData.engineIsRunning = 0;
		}

		globalData.rpmCountTimerInterrupts = 0;
		globalData.pulsesAmount = 0;	
	}
}

void initGlobalData(void)
{
	globalData.turnOnStarter = 0;
	globalData.engineIsRunning = 0;
	globalData.rpmCountTimerInterrupts = 0;
	globalData.pulsesAmount = 0;
}

void setupExternalInterrupts(void)
{
	// interrupt by rising edge
	EICRA |= 1 << ISC01;
	EICRA |= 1 << ISC00;
	
	EICRA |= 1 << ISC11;
	EICRA |= 1 << ISC10;
	
	// enable external interrupt
	EIMSK |= 1 << BUTTON_INTERRUPT;
	EIMSK |= 1 << TACH_INTERRUPT;
	
	// clear external interrupt flag
	EIFR |= 1 << INTF0;
	EIFR |= 1 << INTF1;
}
