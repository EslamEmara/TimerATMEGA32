/*
 * main.c
 *
 * Created: 9/4/2021 6:15:39 AM
 *  Author: 20109
 */ 

#include ".\MCAL\TIMER\Timer.h"
#include ".\ECUAL\LED\Led.h"

int main(void)
{
	ST_TIMER_config_t TIMERconfig = {TIMER1,FREQ_8_MHZ,NORMAL_MODE};
	ST_LED_CONFIG_t LEDconfig = {PORTA,PIN0,ACTIVE_HIGH};
		
	Timer_init(TIMERconfig);
	LED_init(LEDconfig);

	
	while(1)  
	{
		if(Timer_Delay_16bits(0.3,TIMERconfig))				// Toggle if delay is successful.
			LED_TOGGLE(LEDconfig);
	}
}
