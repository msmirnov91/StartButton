/*
 * Interrupts.h
 *
 * Created: 04.11.2020 22:53:51
 *  Author: mikhail
 */ 

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

typedef struct GlobalData_impl
{
	int turnOnStarter;
	int engineIsRunning;
	int rpmCountTimerInterrupts;
	int pulsesAmount;
} GlobalData;

extern volatile GlobalData globalData;

void initGlobalData(void);
void setupExternalInterrupts(void);

#endif /* INTERRUPTS_H_ */