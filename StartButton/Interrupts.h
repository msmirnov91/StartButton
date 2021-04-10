/*
 * Interrupts.h
 *
 * Created: 04.11.2020 22:53:51
 *  Author: mikhail
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


#define F_CPU 8000000L
#include <util/delay.h>


typedef struct GlobalData_impl
{
	int tachPulses;
	int rpmTimerInterrupts;
	int turnOnStarter;
	int engineIsRunning;
} GlobalData;

extern volatile GlobalData globalData;

void setupInterrupts(void);


#endif /* INTERRUPTS_H_ */