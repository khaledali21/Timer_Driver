/*
 * main.h
 *
 * Created: 1/12/2022 3:50:31 PM
 *  Author: Khaled Ali
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "../LIB/Typedef.h"
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/BUTTON/BUTTON.h"
#include "../MCAL/TIMER/TIMER0.h"
#include "../MCAL/TIMER/TIMER2.h"
typedef enum{
	INTERRUPT_MODE,
	POLLING_MODE	
}MODE;

void btn0_callBack(void);
void led0_callBack(void);
void errorHandler(void);

#endif /* MAIN_H_ */