/*
 * defines.h
 *
 * Created: 19.04.2021 23:30:20
 *  Author: mikhail
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#define F_CPU 8000000L


#define IO_DDR DDRD
#define IO_PORT PORTD

#define STARTER_PIN PD0
#define BUTTON_PIN PD2
#define TACH_PIN PD3

#define STARTER_LED PD6
#define IS_RUNNING_LED PD7


#define STOP_TIMER_MASK 0b11111000

// 16 bit
#define OCR_4_SEC 0x7A11
#define TCNT_4_SEC 0x85EE
// 8 bit
#define OCR_20_MSEC 0x9B
#define TCNT_20_MSEC 0x64

#endif /* DEFINES_H_ */