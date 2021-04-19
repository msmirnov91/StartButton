/*
 * StartButton.c
 *
 * Created: 01.11.2020 23:45:58
 *  Author: mikhail
 */ 

#include "Setup.h"
#include "LowLevel.h"
#include "Interrupts.h"

typedef enum TachPinState_impl {LOW = 0, HIGH = 1} TachPinState;

void countPulses(TachPinState*);
int newPulseDetected(TachPinState*);

int main(void)
{
	setup();
	TachPinState prevTachState = LOW;
	startRPMCountTimer();

    while(1)
    {
		countPulses(&prevTachState);
		
		if (globalData.engineIsRunning)
		{
			globalData.turnOnStarter = 0;
			indicateEngineIsRunning();
		}
		else
		{
			indicateEngineIsOff();
		}	
		
		if (globalData.turnOnStarter)
		{
			starterOn();	
		}
		else
		{
			starterOff();
		}					
    }
}

void countPulses(TachPinState* prevState)
{
	if (newPulseDetected(prevState))
	{
		// I know int can store bigger values, but we don't need them
		if (globalData.tachPulses < 255)
			globalData.tachPulses++;
	}
}

int newPulseDetected(TachPinState* prevState)
{
	TachPinState currState = getTachPinState();

	int result = 0;
	if (currState == HIGH && *prevState == LOW)
		result = 1;
	
	*prevState = currState;
	return result;
}
