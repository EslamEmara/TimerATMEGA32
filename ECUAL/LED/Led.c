/*
 * Led.c
 *
 * Created: 9/3/2021 3:23:54 PM
 *  Author: 20109
 */ 

#include "Led.h"
void LED_init(ST_LED_CONFIG_t config)
{
	DIO_setPinDir(config.PORT,config.PIN,OUT);
}
void LED_ON(ST_LED_CONFIG_t config)
{
	if (config.CONN == ACTIVE_HIGH)
		DIO_setPin(config.PORT,config.PIN);
	else if (config.CONN == ACTIVE_LOW)
		DIO_clearPin(config.PORT,config.PIN);
}
void LED_OFF(ST_LED_CONFIG_t config)
{
	if (config.CONN == ACTIVE_HIGH)
		DIO_clearPin(config.PORT,config.PIN);
	else if (config.CONN == ACTIVE_LOW)
		DIO_setPin(config.PORT,config.PIN);
}
void LED_TOGGLE(ST_LED_CONFIG_t config)
{
	DIO_toggle(config.PORT,config.PIN);
}