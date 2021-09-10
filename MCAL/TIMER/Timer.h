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
/*available PreScalars for timer0/timer1*/

typedef enum{
	PRESCALAR0_1 = 1,
	PRESCALAR0_8 = 8,
	PRESCALAR0_64 = 64,
	PRESCALAR0_256 = 256,
	PRESCALAR0_1024 = 1024,
	}EN_PRESCALAR0_t;
	#endif

#if TIMER2_CTRL == ENABLED
/*available PreScalars for timer2*/
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
/*available timers*/
typedef enum{
	TIMER0 = 0x53,
	TIMER1 = 0x4F,
	TIMER2 = 0x45,
	}EN_TIMER_t;
	/*available frequencies*/
typedef enum{
	FREQ_1_MHZ=1000000,
	FREQ_2_MHZ=2000000,
	FREQ_4_MHZ=4000000,
	FREQ_8_MHZ=8000000,
	}EN_FREQ_t;
	/*timer modes*/
typedef enum{
	NORMAL_MODE,
	FAST_PWM,
	}EN_MODE_t;
	/*configuration structure*/
typedef struct timer
{
	EN_TIMER_t timer;
	EN_FREQ_t freq;
	EN_MODE_t mode;

	}ST_TIMER_config_t;

	/*
	 *initialization function for timers
	 *PS============ MAKE SURE YOU ENABLE THE DESIRED TIMER IN THE CONFIG FILE ===============
	 *INPUTS ST_TIMER_config_t (see Timers.h for definition)
	 *void return
	 */
void Timer_init(ST_TIMER_config_t);
/*
 *Function to delay for 8-bit registers TIMER0 and TIMER2
 *Conditions on desired delay ::: 255 < FREQ * desired < 216120 otherwise try to use 16bit timer
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */
uint8_t Timer_Delay_8bits(float desired,ST_TIMER_config_t config);
/*
 *Function to delay for 16-bit registers TIMER1
 *Conditions on desired delay ::: 65536 < FREQ * desired < 67,108,864 otherwise try to divide the delay on more than one time
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */
uint8_t Timer_Delay_16bits(float desired,ST_TIMER_config_t config);
/*
 *Function to generate PWM with 8bit resolution
 *INPUTS: uint8_t holds the duty cycle percentage, ST_TIMER_config_t timer config
 *CONDITIONs on input:  ============================== dutyCycle percentage must be between 0 and 100 ======================================
 *return 0 in input error type and 1 in success.
 */
void Timer_generate_PWM(uint8_t dutyCycle,ST_TIMER_config_t config);


#endif /* TIMER_H_ */
