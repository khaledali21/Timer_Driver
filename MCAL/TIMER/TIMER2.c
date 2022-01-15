/*
 * TIMER0.c
 *
 * Created: 1/12/2022 2:13:41 PM
 *  Author: Khaled Ali
 */ 
#include "TIMER2.h"

// variable used in interrupt to compare with delay
static uint16_t volatile compare;
static uint16_t volatile counter;
static DELAY delay_stat = DELAY_OK;
static void (*delayCallBack)(void);


/*
* brief: This function is used to initialize Timer 2 to use CTC mode and 64 prescaler
* return: (output) the Error state of the function 2 if an error happens and 1 otherwise
*/
uint8_t TIMER2_u8Init(void){
	TCCR2_REG = (1 << WGM21) | (1<<CS22);
	TCNT2_REG = 0;
	return DELAY_OK;
}

/*
* brief: This function is used to initialize an interrupt delay if the Timer isn't busy
* param.: (input) the delay to be set in ms
* param.: (input) a pointer to a function to be called when the delay is over
* return: (output) the Error state of the function 0 if an error happens, 2 if the timer is busy and 1 otherwise
*/
uint8_t TIMER2_u8InterruptDelay(uint16_t delay, void (*fnCallBack)(void)){
	if(delay_stat == DELAY_BUSY){
		return delay_stat;
	}
	delay_stat = DELAY_BUSY;
	compare = delay;
	if(fnCallBack != NULL){
		delayCallBack = fnCallBack;
		OCR2_REG = (F_CPU / PRESCALER);
		SET_BIT(TIMSK_REG, OCIE2);
		SET_BIT(SREG_REG, I_BIT);
		return DELAY_OK;
	}
	else{
		return DELAY_ERR;
	}
}

/*
* brief: This function is used to initialize a polling delay if the Timer isn't busy
* param.: (input) the delay to be set in ms
* return: (output) the Error state of the function 0 if an error happens, 2 if the timer is busy and 1 otherwise
*/
uint8_t TIMER2_u8PollingDelay(uint16_t delay){
	if(delay_stat == DELAY_BUSY){
		return delay_stat;
	}
	delay_stat = DELAY_BUSY;
	counter = 0;						// reset counter to 0
	compare = delay;
	TIMER2_u8Init();					// initialize timer0
	OCR2_REG = (F_CPU / PRESCALER);		// set OCR2_REG value
	SET_BIT(TIMSK_REG, OCIE2);			// enable interrupt
	SET_BIT(SREG_REG, I_BIT);
	while (counter < compare);			// stop if delay not finished
	CLR_BIT(TIMSK_REG, OCIE2);
	delay_stat = DELAY_OK;
	return DELAY_OK;
}
void __vector_4(void){
	counter++;
	if(counter == compare && delayCallBack != NULL){
		counter = 0;
		CLR_BIT(TIMSK_REG, OCIE2);
		delay_stat = DELAY_OK;
		delayCallBack();
	}
}
