/*
 * defines.h
 *
 * Created: 19.04.2021 23:30:20
 *  Author: mikhail
 */ 

#ifndef DEFINES_H_
#define DEFINES_H_


/*  ======= COMMON =======  */
#define F_CPU 16000000L
// #define PCB_TEST_MODE // uncomment this to compile in PCB test mode


/*  ======= THRESHOLDS =======  */
#define ENGINE_ON_LEVEL 100
#define LOW_VLOTAGE_LEVEL 615
#define HIGH_VOLTAGE_LEVEL 935


/*  ======= IO =======  */
#define STARTER_DDR DDRC
#define STARTER_PORT PORTC
#define STARTER_PIN PC4
#define IGNITION_PIN PC3

#define INPUT_DDR DDRD
#define INPUT_PORT PORTD
#define BUTTON_PIN PD2

#define LED_DDR DDRB
#define LED_PORT PORTB
#define FATAL_ERROR_LED PB0
#define STARTER_LED PB1
#define IS_RUNNING_LED PB2


/*  ======= TIMERS =======  */ 
#define STOP_TIMER_MASK 0b11111000

// 16 bit
#define OCR_4_SEC 0xF424
#define TCNT_4_SEC 0x0BDC


/*  ======= ADC =======  */ 
#define TACH_CHANNEL 0
#define VOLTAGE_CHANNEL 2


#endif /* DEFINES_H_ */