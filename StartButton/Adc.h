/*
 * Adc.h
 *
 * Created: 08.05.2021 15:52:10
 *  Author: mikhail
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void setupADC(void);
uint16_t getADCValue(uint8_t channel);

#endif /* ADC_H_ */