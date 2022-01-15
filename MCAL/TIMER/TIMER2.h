/*
 * TIMER2.h
 *
 * Created: 1/14/2022 8:57:18 PM
 *  Author: Khaled Ali
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_


#include "../../LIB/Atmega32.h"
#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "TIMER0.h"
uint8_t TIMER2_u8Init(void);
uint8_t TIMER2_u8InterruptDelay(uint16_t delay, void (*fnCallBack)(void));
uint8_t TIMER2_u8PollingDelay(uint16_t delay);
//TIMER0 COMP
void __vector_4(void) __attribute__ ((signal, used));



#endif /* TIMER2_H_ */