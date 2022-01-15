/*
 * main.c
 *
 *  Created on: Jan 6, 2022
 *      Author: Khaled Ali
 */

#include "main.h"
LED_t led0 = {PORTB, PIN4};
LED_t led1 = {PORTB, PIN6};
LED_t led_err = {PORTB, PIN7};
volatile uint8_t delay = 0;
int main(void){
	uint8_t status = OK;
	LED_u8Init(&led_err);
	status = LED_u8Init(&led0);
	if(status != OK){
		errorHandler();
	}
	status = LED_u8Init(&led1);
	if(status != OK){
		errorHandler();
	}
	status = TIMER0_u8Init();
	if(status != OK){
		errorHandler();		
	}
	status = TIMER2_u8Init();
	if(status != OK){
		errorHandler();
	}
	status = TIMER0_u8InterruptDelay(500, led0_callBack);
	while(1){
		status = TIMER2_u8PollingDelay(500);
		if(status == ERR){
			errorHandler();
		}
		else if(status == OK){
			LED_u8TOGGLE(&led1);
		}
		else{
			continue;
		}
		status = TIMER2_u8PollingDelay(300);
		if(status == ERR){
			errorHandler();
		}
		else if(status == OK){
			LED_u8TOGGLE(&led1);
		}
		else{
			continue;
		}
	}
}

/*
* brief: This function is a callback function that gets called when a delay event occurs and used to toggle the led and start the delay again
*/
void led0_callBack(void){
	uint8_t status;
	LED_u8TOGGLE(&led0);
	if(delay == 0){
		delay = !delay;
		status = TIMER0_u8InterruptDelay(300, led0_callBack);
		if(status != OK){
			errorHandler();
		}
	}
	else{
		delay = !delay;
		status = TIMER0_u8InterruptDelay(500, led0_callBack);
		if(status != OK){
			errorHandler();
		}
	}
}
/*
* brief: This function is called when an error occurs it turns on a led for indication and then traps the program in an infinite loop
*/
void errorHandler(void){
	LED_u8ON(&led_err);
	while(1); //trap program
}