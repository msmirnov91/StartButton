/*
 * LowLevel.h
 *
 * Created: 04.11.2020 22:41:55
 *  Author: mikhail
 */ 

#ifndef LOWLEVEL_H_
#define LOWLEVEL_H_

#include "Defines.h"
#include <avr/io.h>

uint16_t getADCValue(uint8_t channel);

void ignitionOn(void);
void ignitionOff(void);

void starterOn(void);
void starterOff(void);

void indicateEngineIsRunning(void);
void indicateEngineIsOff(void);

void indicateFatalError(void);
void turnOffFatalErrorIndicaton(void);

void initCutoffTimer(void);

#endif /* LOWLEVEL_H_ */