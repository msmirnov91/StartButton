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

int getTachPinState(void);
unsigned int getADCValue(void);
int isStartButtonPressed(void);

void starterOn(void);
void starterOff(void);

void indicateEngineIsRunning(void);
void indicateEngineIsOff(void);

void initRPMCountTimer(void);
void startRPMCountTimer(void);

void initCutoffTimer(void);

#endif /* LOWLEVEL_H_ */