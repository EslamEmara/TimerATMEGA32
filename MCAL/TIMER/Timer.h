/*
 * Timer.h
 *
 * Created: 9/4/2021 6:10:47 AM
 *  Author: 20109
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER_RegMap.h"
#include "TypeDefs.h"
#include "BIT_MATH.h"
#include "Timer_config.h"

#if TIMER0_CTRL == ENABLED || TIMER1_CTRL ==ENABLED
typedef enum{
	PRESCALAR0_1 = 1,
	PRESCALAR0_8 = 8,
	PRESCALAR0_64 = 64,
	PRESCALAR0_256 = 256,
	PRESCALAR0_1024 = 1024,
	}EN_PRESCALAR0_t;
	#endif
	
#if TIMER2_CTRL == ENABLED
typedef enum{
	PRESCALAR2_1 = 1,
	PRESCALAR2_8 = 8,
	PRESCALAR2_32 = 32,
	PRESCALAR2_64 = 64,
	PRESCALAR2_128=128,
	PRESCALAR2_256 = 256,
	PRESCALAR2_1024 = 1024,
	}EN_PRESCALAR2_t;
#endif

typedef enum{
	TIMER0 = 0x53,
	TIMER1 = 0x4F,
	TIMER2 = 0x45,
	}EN_TIMER_t;
	
typedef enum{
	FREQ_1_MHZ=1000000,
	FREQ_2_MHZ=2000000,
	FREQ_4_MHZ=4000000,
	FREQ_8_MHZ=8000000,
	}EN_FREQ_t;
	
typedef enum{
	NORMAL_MODE,
	FAST_PWM,
	}EN_MODE_t;
typedef struct timer
{	
	EN_TIMER_t timer;
	EN_FREQ_t freq;
	EN_MODE_t mode;
	
	}ST_TIMER_config_t;


void Timer_init(ST_TIMER_config_t);
uint8_t Timer_Delay_8bits(float desired,ST_TIMER_config_t config);
uint8_t Timer_Delay_16bits(float desired,ST_TIMER_config_t config);
void Timer_generate_PWM(uint8_t dutyCycle,ST_TIMER_config_t config);


#endif /* TIMER_H_ */