/*
 * StartButton.c
 *
 * Created: 01.11.2020 23:45:58
 *  Author: mikhail
 */ 

#include "Setup.h"
#include "LowLevel.h"
#include "Interrupts.h"

int main(void)
{
	setup();

    while(1)
    {
		if (getADCValue()>= ENGINE_ON_LEVEL) {
			globalData.engineIsRunning = 1;
		} else {
			globalData.engineIsRunning = 0;
		}

		if (globalData.engineIsRunning) {
			globalData.turnOnStarter = 0;
			indicateEngineIsRunning();
		} else {
			indicateEngineIsOff();
		}	
		
		if (globalData.turnOnStarter) {
			starterOn();	
		} else {
			starterOff();
		}					
    }
}
