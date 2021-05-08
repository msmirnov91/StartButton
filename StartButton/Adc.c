/*
 * Adc.c
 *
 * Created: 08.05.2021 15:51:56
 *  Author: mikhail
 */

#include "Adc.h"
#include "Defines.h"

uint16_t getADCValue(uint8_t channel)
{
	ADMUX = (ADMUX & 0xf0) | channel;
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1 << ADIF)));
	ADCSRA |= (1 << ADIF);
 
	return ADC;
}