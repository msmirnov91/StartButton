/*
 * Interrupts.c
 *
 * Created: 04.11.2020 22:53:28
 *  Author: mikhail
 */ 


#include "Interrupts.h"
#include "LowLevel.h"
#include<avr/interrupt.h>

#define BUTTON_INTERRUPT INT0
#define BUTTON_INTERRUPT_VEC INT0_vect

#define CUTOFF_TIMER_INTERRUPT_VEC TIMER1_COMPA_vect
#define RPM_COUNT_TIMER_INTERRUPT_VEC TIMER2_COMP_vect


volatile GlobalData globalData;


EMPTY_INTERRUPT(BADISR_vect);


#define DEBOUNCE_CHECK_AMOUNT 3
#define DEBOUNCE_DELAY_ITERATIONS 1000

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


ISR(CUTOFF_TIMER_INTERRUPT_VEC)
{
	globalData.turnOnStarter = 0;
}


#define HALF_SECOND_INTERRUPTS_AMOUNT 25
#define PULSE_THRESHOLD 5

ISR(RPM_COUNT_TIMER_INTERRUPT_VEC)
{
	globalData.rpmTimerInterrupts += 1;
	if (globalData.rpmTimerInterrupts > HALF_SECOND_INTERRUPTS_AMOUNT)
	{
		if (globalData.tachPulses > PULSE_THRESHOLD)
		{
			globalData.engineIsRunning = 1;
		}
		else
		{
			globalData.engineIsRunning = 0;
		}

		globalData.rpmTimerInterrupts = 0;
		globalData.tachPulses = 0;
	}
}


void initGlobalData(void)
{
	globalData.tachPulses = 0;
	globalData.rpmTimerInterrupts = 0;
	globalData.turnOnStarter = 0;
	globalData.engineIsRunning = 0;
}


void setupExternalInterrupts(void)
{
	// interrupt by rising edge
	MCUCR |= 1 << ISC01;
	MCUCR |= 1 << ISC00;
	
	// enable external interrupt
	GICR |= 1 << BUTTON_INTERRUPT;
	
	// clear external interrupt flag
	GIFR |= 1 << INTF0;
}


void enableTimerInterrupts(void)
{
	TIMSK |= 1 << OCIE1A;
	TIMSK |= 1 << OCIE2;
}


void clearTimerInterruptsFlags(void)
{
	TIFR |= 1 << OCF1A;
	TIFR |= 1 << OCF2;
}


void setupTimerInterrupts(void)
{
	/* use avrcalc tool to easily
	get timer control register values */
	
	initRPMCountTimer();
	initCutoffTimer();
	
	enableTimerInterrupts();
	clearTimerInterruptsFlags();
}


void setupInterrupts(void)
{
	cli();
	
	initGlobalData();
	setupExternalInterrupts();
	setupTimerInterrupts();
	
	sei();
}
