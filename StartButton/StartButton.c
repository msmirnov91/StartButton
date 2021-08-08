/*
 * StartButton.c
 *
 * Created: 01.11.2020 23:45:58
 *  Author: mikhail
 */ 

#include "Defines.h"
#include "LowLevel.h"
#include "Interrupts.h"
#include "Adc.h"
#include "Timers.h"

#include <util/delay.h>
#include <avr/interrupt.h>

void mainLoop(void);
void testPCBLoop(void);

int main(void)
{
	setupPins();
	setupADC();	

	cli();

	initGlobalData();
	setupExternalInterrupts();
	setupTimerInterrupts();

	sei();
	
	starterOff();

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

	if (globalData.engineIsRunning) {
		indicateEngineIsRunning();
	} else {
		indicateEngineIsOff();
	}
		
	if (globalData.turnOnStarter && !globalData.engineIsRunning) {
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
	
	if (globalData.engineIsRunning) {
		indicateEngineIsRunning();
	} else {
		indicateEngineIsOff();
	}
}
