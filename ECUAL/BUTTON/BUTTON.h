/*
 * Button.h
 *
 * Created: 1/7/2022 8:05:14 PM
 *  Author: Khaled Ali
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../LIB/Typedef.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER/TIMER0.h"
typedef struct{
	uint8_t PORT;
	uint8_t PIN;
}BTN_t;

typedef enum{
	BTN_ERR,
	BTN_OK
}BTN_ERR_STATE;
BTN_ERR_STATE BTN_u8Init(const BTN_t* btn);

BTN_ERR_STATE BTN_u8State(const BTN_t* btn, uint8_t* pressed);




#endif /* BUTTON_H_ */