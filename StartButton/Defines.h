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
#define ENGINE_ON_LEVEL 6
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
#define TACH_PIN PD3

#define LED_DDR DDRB
#define LED_PORT PORTB
#define FATAL_ERROR_LED PB0
#define STARTER_LED PB1
#define IS_RUNNING_LED PB2


/*  ======= INTERRUPTS =======  */ 
#define BUTTON_INTERRUPT INT0
#define BUTTON_INTERRUPT_VEC INT0_vect

#define TACH_INTERRUPT INT1
#define TACH_INTERRUPT_VEC INT1_vect

#define CUTOFF_TIMER_INTERRUPT_VEC TIMER1_COMPA_vect
#define RPM_COUNT_TIMER_INTERRUPT_VEC TIMER0_COMPA_vect

#define DEBOUNCE_CHECK_AMOUNT 3
#define DEBOUNCE_DELAY_ITERATIONS 1000


/*  ======= TIMERS =======  */ 
#define STOP_TIMER_MASK 0b11111000

/* use avrcalc tool to easily get timer control register values */

// 16 bit
#define OCR_4_SEC 0xF424
#define TCNT_4_SEC 0x0BDC

// 8 bit
#define OCR_10_MSEC 0x9C
#define INTERRUPTS_PER_1SEC 0x64


/*  ======= ADC =======  */ 
#define VOLTAGE_CHANNEL 2


#endif /* DEFINES_H_ */