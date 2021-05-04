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
	STARTER_DDR |= 1 << STARTER_PIN;
	STARTER_DDR |= 1 << IGNITION_PIN;

	LED_DDR |= 1 << FATAL_ERROR_LED;
	LED_DDR |= 1 << STARTER_LED;
	LED_DDR |= 1 << IS_RUNNING_LED;
	
	INPUT_DDR &= ~(1 << BUTTON_PIN);
	INPUT_PORT &= ~(1 << BUTTON_PIN);
}

void setupADC(void)
{
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << REFS0);  // AVCC reference with capacitor at AREF
}

void setup(void)
{
	setupInterrupts();
	setupPins();
	setupADC();	

	starterOff();
}
