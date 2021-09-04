/*
 * Button.h
 *
 * Created: 9/3/2021 3:23:22 PM
 *  Author: 20109
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "..\..\MCAL\DIO\DIO.h"

typedef enum {
	PULLUP_RES,
	PULLDOWN_RES,
	INTERNAL_PULLUP,
}EN_CONN_t;

typedef struct button{
	EN_PORTS_t PORT;
	EN_PINS_t PIN;
	EN_CONN_t CONNECTION;
}ST_BUTTON_config_t;

void Button_init(ST_BUTTON_config_t config);
EN_DATA_t Button_getState(ST_BUTTON_config_t config);




#endif /* BUTTON_H_ */