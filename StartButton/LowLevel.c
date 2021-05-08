/*
 * LowLevel.c
 *
 * Created: 04.11.2020 22:42:13
 *  Author: mikhail
 */ 

#include "LowLevel.h"
#include "Defines.h"
#include "Timers.h"
#include <avr/io.h>

void turnOnPin(volatile uint8_t* port, uint8_t pin)
{
	*port |= 1 << pin;
}

void turnOffPin(volatile uint8_t* port, uint8_t pin)
{
	*port &= ~(1 << pin);
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
