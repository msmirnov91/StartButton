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

void setupADC(void)
{
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX = (1 << REFS0);
}

void setup(void)
{
	calibrateInternalOscillator();
	setupInterrupts();
	setupPins();
	setupADC();	

	starterOff();
}
