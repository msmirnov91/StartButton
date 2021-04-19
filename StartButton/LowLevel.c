/*
 * LowLevel.c
 *
 * Created: 04.11.2020 22:42:13
 *  Author: mikhail
 */ 


#include "LowLevel.h"

#include "Defines.h"


void calibrateInternalOscillator(void)
{
	OSCCAL = 0xfa;
}


int getPinState(uint8_t pin)
{
	int pinValue = PIND & (1 << pin);
	return pinValue != 0;
}


int getTachPinState(void)
{
	return getPinState(TACH_PIN);
}


unsigned int getADCValue(void)
{
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADCW;
}


int isStartButtonPressed(void)
{
	return getPinState(BUTTON_PIN);
}


void setCTCMode(volatile uint8_t* reg)
{
	if (*reg == TCCR1B)
	{
		*reg |= 1 << WGM12;
		*reg &= ~(1 << WGM13);
	}	

	if (*reg == TCCR2)
	{
		*reg |= 1 << WGM21;
		*reg &= ~(1 << WGM20);
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

	if (*reg == TCCR2)
	{
		*reg |= 1 << CS22;
		*reg |= 1 << CS21;
		*reg |= 1 << CS20;
	}
}


void resetCutoffTimer(void)
{
	TCNT1 = TCNT_4_SEC;
	TCCR1B &= STOP_TIMER_MASK;
}


void resetRPMCountTimer(void)
{ 
	TCNT2 = TCNT_20_MSEC;
	TCCR2 &= STOP_TIMER_MASK;
}


void initCutoffTimer(void)
{
	setCTCMode(&TCCR1B);
	resetCutoffTimer();
	
	OCR1A = OCR_4_SEC;
}


void startCutoffTimer(void)
{
	startTimerDiv1024(&TCCR1B);
}


void initRPMCountTimer(void)
{
	setCTCMode(&TCCR2);
	resetRPMCountTimer();

	OCR2 = OCR_20_MSEC;	
}


void startRPMCountTimer()
{
	startTimerDiv1024(&TCCR2);
}


void starterOn(void)
{
	IO_PORT |= 1 << STARTER_PIN;
	IO_PORT |= 1 << STARTER_LED;
	
	startCutoffTimer();
}


void starterOff(void)
{
	IO_PORT &= ~(1 << STARTER_PIN);
	IO_PORT &= ~(1 << STARTER_LED);

	resetCutoffTimer();
}


void indicateEngineIsRunning(void)
{
	IO_PORT |= 1 << IS_RUNNING_LED;
}


void indicateEngineIsOff(void)
{
	IO_PORT &= ~(1 << IS_RUNNING_LED);
}
