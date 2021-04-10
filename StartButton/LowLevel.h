/*
 * LowLevel.h
 *
 * Created: 04.11.2020 22:41:55
 *  Author: mikhail
 */ 


#ifndef LOWLEVEL_H_
#define LOWLEVEL_H_


#define IO_DDR DDRD
#define IO_PORT PORTD

#define STARTER_PIN PD0
#define BUTTON_PIN PD2
#define TACH_PIN PD3

#define STARTER_LED PD6
#define IS_RUNNING_LED PD7


#include <avr/io.h>


void calibrateInternalOscillator(void);
int getTachPinState(void);
int isStartButtonPressed(void);

void starterOn(void);
void starterOff(void);

void indicateEngineIsRunning(void);
void indicateEngineIsOff(void);

void initRPMCountTimer(void);
void startRPMCountTimer(void);

void initCutoffTimer(void);


#endif /* LOWLEVEL_H_ */