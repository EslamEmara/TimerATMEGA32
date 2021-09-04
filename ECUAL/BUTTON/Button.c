/*
 * Button.c
 *
 * Created: 9/3/2021 3:23:04 PM
 *  Author: Eslam Emara
 */ 

#include "Button.h"

void Button_init(ST_BUTTON_config_t config)
{
	if(config.CONNECTION == INTERNAL_PULLUP){
		DIO_setPinDir(config.PORT,config.PIN,PULLUP);
	}
	else
		DIO_setPinDir(config.PORT,config.PIN,IN);
}
EN_DATA_t Button_getState(ST_BUTTON_config_t config)
{
	static EN_DATA_t last_button_state = LOW;
	static EN_DATA_t current_state=LOW;
	static EN_DATA_t last_stable=LOW;								//last stable state

	static uint8_t counter = 0;
	
	if (config.CONNECTION == PULLDOWN_RES){
		current_state = DIO_getPin(config.PORT,config.PIN);
	}
	else{
		current_state = !DIO_getPin(config.PORT,config.PIN);
	}

	if (current_state != last_button_state){					//check if debouncing is over
		last_button_state = current_state;	
	}
	else{
		counter++;
	}
		
	if (counter >20)												// if it is same input for 20 loop return current state
	{
		counter = 0;
		last_stable = current_state;
		return current_state;
	}
	else
	return last_stable;										// return last stable state if not stable yet
	
}