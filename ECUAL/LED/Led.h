/*
 * Led.h
 *
 * Created: 9/3/2021 3:23:39 PM
 *  Author: 20109
 */ 


#ifndef LED_H_
#define LED_H_

#include "..\..\MCAL\DIO\DIO.h"

typedef enum {
	ACTIVE_LOW,
	ACTIVE_HIGH,
}EN_LEDTYPE_t;

typedef struct led{
	EN_PORTS_t PORT;
	EN_PINS_t PIN;
	EN_LEDTYPE_t CONN;
}ST_LED_CONFIG_t;

void LED_init(ST_LED_CONFIG_t config);
void LED_ON(ST_LED_CONFIG_t config);
void LED_OFF(ST_LED_CONFIG_t config);
void LED_TOGGLE(ST_LED_CONFIG_t config);




#endif /* LED_H_ */