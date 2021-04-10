/*
 * Setup.c
 *
 * Created: 04.11.2020 22:40:51
 *  Author: mikhail
 */ 


#include "Setup.h"
#include "LowLevel.h"
#include "Interrupts.h"


void setupPins(void)
{
	IO_DDR |= 1 << STARTER_PIN;
	IO_DDR |= 1 << STARTER_LED;
	IO_DDR |= 1 << IS_RUNNING_LED;
	
	IO_DDR &= ~(1 << BUTTON_PIN);
	IO_DDR &= ~(1 << TACH_PIN);
	
	IO_PORT &= ~(1 << BUTTON_PIN);
	IO_PORT &= ~(1 << TACH_PIN);
}


void setup(void)
{
	calibrateInternalOscillator();
	setupInterrupts();
	setupPins();

	starterOff();
}