/*
 * StartButton.c
 *
 * Created: 01.11.2020 23:45:58
 *  Author: mikhail
 */ 

#include "Defines.h"
#include "Setup.h"
#include "LowLevel.h"
#include "Interrupts.h"
#include "Adc.h"
#include <util/delay.h>

void mainLoop(void);
void testPCBLoop(void);

int main(void)
{
	setup();

    while(1)
    {
		#ifdef PCB_TEST_MODE
			testPCBLoop();
		#else
			mainLoop();
		#endif
    }
}

void mainLoop(void)
{
	uint16_t voltageLevel = getADCValue(VOLTAGE_CHANNEL);
	if (voltageLevel <= LOW_VLOTAGE_LEVEL ||
	    voltageLevel >= HIGH_VOLTAGE_LEVEL) {
		indicateFatalError();
	} else {
		turnOffFatalErrorIndicaton();
	}

	if (getADCValue(TACH_CHANNEL) >= ENGINE_ON_LEVEL) {
		globalData.turnOnStarter = 0;
		globalData.engineIsRunning = 1;
		indicateEngineIsRunning();
	} else {
		globalData.engineIsRunning = 0;
		indicateEngineIsOff();
	}
		
	if (globalData.turnOnStarter) {
		starterOn();	
	} else {
		starterOff();
	}
}

void testPCBLoop(void)
{
	ignitionOn();
	_delay_ms(1000);
	ignitionOff();
	_delay_ms(1000);
	starterOn();
	_delay_ms(1000);
	starterOff();
	_delay_ms(1000);
	indicateFatalError();
	_delay_ms(1000);
	turnOffFatalErrorIndicaton();
	_delay_ms(1000);
	
	unsigned int adcValue = getADCValue(TACH_CHANNEL);
	if (adcValue >= ENGINE_ON_LEVEL) {
		indicateEngineIsRunning();
	} else {
		indicateEngineIsOff();
	}
}
