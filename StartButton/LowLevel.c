/*
 * LowLevel.c
 *
 * Created: 04.11.2020 22:42:13
 *  Author: mikhail
 */ 

#include "LowLevel.h"
#include "Defines.h"

uint16_t getADCValue(uint8_t channel)
{
	ADMUX = (ADMUX & 0xf0) | channel;
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA && (1 << ADIF)));
	ADCSRA |= (1 << ADIF);
 
	return ADC;
}

void turnOnPin(volatile uint8_t* port, uint8_t pin)
{
	*port |= 1 << pin;
}

void turnOffPin(volatile uint8_t* port, uint8_t pin)
{
	*port &= ~(1 << pin);
}

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

void resetCutoffTimer(void)
{
	TCNT1 = TCNT_4_SEC;
	TCCR1B &= STOP_TIMER_MASK;
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

void ignitionOn(void)
{
	turnOnPin(&STARTER_PORT, IGNITION_PIN);
}

void ignitionOff(void)
{
	turnOffPin(&STARTER_PORT, IGNITION_PIN);
}

void starterOn(void)
{
	turnOnPin(&STARTER_PORT, STARTER_PIN);
	turnOnPin(&LED_PORT, STARTER_LED);
	
	startCutoffTimer();
}

void starterOff(void)
{
	turnOffPin(&STARTER_PORT, STARTER_PIN);
	turnOffPin(&LED_PORT, STARTER_LED);

	resetCutoffTimer();
}

void indicateEngineIsRunning(void)
{
	turnOnPin(&LED_PORT, IS_RUNNING_LED);
}

void indicateEngineIsOff(void)
{
	turnOffPin(&LED_PORT, IS_RUNNING_LED);
}

void indicateFatalError(void)
{
	turnOnPin(&LED_PORT, FATAL_ERROR_LED);
}

void turnOffFatalErrorIndicaton(void)
{
	turnOffPin(&LED_PORT, FATAL_ERROR_LED);
}
