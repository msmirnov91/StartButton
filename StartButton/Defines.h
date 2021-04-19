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


/*  ======= THRESHOLDS =======  */
#define ENGINE_ON_LEVEL 512


/*  ======= IO =======  */
#define IO_DDR DDRD
#define IO_PORT PORTD

#define STARTER_PIN PD0
#define BUTTON_PIN PD2
#define TACH_PIN PD3

#define STARTER_LED PD6
#define IS_RUNNING_LED PD7


/*  ======= TIMERS =======  */ 
#define STOP_TIMER_MASK 0b11111000

// 16 bit
#define OCR_4_SEC 0xF424
#define TCNT_4_SEC 0x0BDC


#endif /* DEFINES_H_ */