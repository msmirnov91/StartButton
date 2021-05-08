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

void setupPins(void)
{
	STARTER_DDR |= 1 << STARTER_PIN;
	STARTER_DDR |= 1 << IGNITION_PIN;

	LED_DDR |= 1 << FATAL_ERROR_LED;
	LED_DDR |= 1 << STARTER_LED;
	LED_DDR |= 1 << IS_RUNNING_LED;
	
	INPUT_DDR &= ~(1 << BUTTON_PIN);
	INPUT_PORT &= ~(1 << BUTTON_PIN);
}

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
