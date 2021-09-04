/*
 * Timer.c
 *
 * Created: 9/4/2021 6:11:00 AM
 *  Author: 20109
 */ 

#include "Timer.h"

#if TIMER0_CTRL == ENABLED

	static void adjustPrescalarT0(EN_PRESCALAR0_t prescalar){					/*ADJUSTIN PRESCALAR BITS FOR TIMER0 */
		if(prescalar == PRESCALAR0_1){
			SETBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_8){
			CLRBIT(TCCR0,0);
			SETBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_64){
			SETBIT(TCCR0,0);
			SETBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_256){
			CLRBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			SETBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_1024){
		
			SETBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			SETBIT(TCCR0,2);
		}

	}
#endif
#if TIMER2_CTRL == ENABLED
	static void adjustPrescalarT2(EN_PRESCALAR2_t prescalar){				/*ADJUSTIN PRESCALAR BITS FOR TIMER2 */
		if(prescalar == PRESCALAR2_1){
			SETBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_8){
			CLRBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
	
		else if(prescalar == PRESCALAR2_32){
			SETBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_64){
			CLRBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_128){
			SETBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_256){
			CLRBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_1024){
		
			SETBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}

	}
#endif

#if TIMER1_CTRL == ENABLED
	static void adjustPrescalarT1(EN_PRESCALAR0_t prescalar){						/*ADJUSTIN PRESCALAR BITS FOR TIMER1 */
		if(prescalar == PRESCALAR0_1){
			SETBIT(TCCR1B,0);
			CLRBIT(TCCR1B,1);
			CLRBIT(TCCR1B,2);
		}
		else if(prescalar == PRESCALAR0_8){
			CLRBIT(TCCR1B,0);
			SETBIT(TCCR1B,1);
			CLRBIT(TCCR1B,2);
		}
		else if(prescalar == PRESCALAR0_64){
			SETBIT(TCCR1B,0);
			SETBIT(TCCR1B,1);
			CLRBIT(TCCR1B,2);
		}
		else if(prescalar == PRESCALAR0_256){
			CLRBIT(TCCR1B,0);
			CLRBIT(TCCR1B,1);
			SETBIT(TCCR1B,2);
		}
		else if(prescalar == PRESCALAR0_1024){
		
			SETBIT(TCCR1B,0);
			CLRBIT(TCCR1B,1);
			SETBIT(TCCR1B,2);
		}

	}
#endif

/*
 *initialization function for timers
 *PS============ MAKE SURE YOU ENABLE THE DESIRED TIMER IN THE CONFIG FILE ===============
 *INPUTS ST_TIMER_config_t (see Timers.h for definition)
 *void return
 */
void Timer_init(ST_TIMER_config_t config)
{
	if (config.mode == NORMAL_MODE)
		REG(config.timer) = 0x00;				//Normal Mode
		
	else if (config.mode == FAST_PWM){
		if (config.timer == TIMER0)
			SETBIT(PORTB_DIR,3);
		if (config.timer == TIMER2)
			SETBIT(PORTD_DIR,7);
		REG(config.timer) =0b01101001;			// FAST PWM with no prescalar and non inverting mode
												// for inverting mode 0b01111001
	}
}
/*
 *Function to delay for 8-bit registers TIMER0 and TIMER2
 *Conditions on desired delay ::: 255 < FREQ * desired < 216120 otherwise try to use 16bit timer
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */
uint8_t Timer_Delay_8bits(float desired,ST_TIMER_config_t config)
{
	#if TIMER0_CTRL == ENABLED 
	if (config.timer == TIMER0)
	{
		uint8_t i = 0;
		uint8_t found = 0;
		EN_PRESCALAR0_t PRESCALARS[5] = {PRESCALAR0_1,PRESCALAR0_8,PRESCALAR0_64,PRESCALAR0_256,PRESCALAR0_1024};		//array of all available prescalars
		EN_PRESCALAR0_t prescalar = PRESCALAR0_1;	
		for(i=0;i<5;i++)
		{
			if((config.freq/PRESCALARS[i] < (255.0/desired)) && ((config.freq/PRESCALARS[i]) > 0))						//Find a suitable Prescalar through (FREQ/PRESCALAR) < (255/DESIRED DELAY)
			{
				prescalar = PRESCALARS[i];
				found = 1;																							// A suitable prescalar is found
				break;
			}
		}
		
		if (found==0){
			return 0;																//No suitable prescalar is found Frequency mismatch the desired delay
		}
		else{
			adjustPrescalarT0(prescalar);
			TCNT0 =(int) (255 - ((float)((config.freq*desired)/prescalar)));
			while(GETBIT(TIFR,0)==0);										/* Wait for overflow flag to rise*/
			SETBIT(TIFR,0);  												/* Clear the flag */
			
			return 1;
		}

	}
	#endif
	#if TIMER2_CTRL == ENABLED
	if (config.timer == TIMER2)
	{	
		uint8_t i = 0;
		uint8_t found = 0;
		EN_PRESCALAR2_t PRESCALARS[7] = {PRESCALAR2_1,PRESCALAR2_8,PRESCALAR2_32,PRESCALAR2_64,PRESCALAR2_128,PRESCALAR2_256,PRESCALAR2_1024}; //PRESCALARS OF TIMER2
		EN_PRESCALAR2_t prescalar = PRESCALAR2_1;	
		for(i=0;i<7;i++)
		{
			if((config.freq/PRESCALARS[i] < (255.0/desired)) && ((config.freq/PRESCALARS[i]) > 0))
			{
				prescalar = PRESCALARS[i];
				found = 1;
				break;
			}
		}
		
		if (found==0){												/*Frequency doesn't match desired delay try 16-bit timer*/
			return 0;
		}
		else{
			adjustPrescalarT2(prescalar);
			TCNT2 =(int) (255 - ((float)((config.freq*desired)/prescalar)));
			while(GETBIT(TIFR,6)==0);								 /* Wait for the overflow flag to rise */
			SETBIT(TIFR,6);  											/* Clear OF flag */
			
			return 1;
		}

	}
	#endif
return 1;
}
/*
 *Function to delay for 16-bit registers TIMER1
 *Conditions on desired delay ::: 65536 < FREQ * desired < 67,108,864 otherwise try to divide the delay on more than one time
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */
uint8_t Timer_Delay_16bits(float desired,ST_TIMER_config_t config)	
{
	
	#if TIMER1_CTRL == ENABLED
	if (config.timer == TIMER1)
	{
		uint8_t i = 0;
		uint8_t found = 0;
		EN_PRESCALAR0_t PRESCALARS[5] = {PRESCALAR0_1,PRESCALAR0_8,PRESCALAR0_64,PRESCALAR0_256,PRESCALAR0_1024};	//Available prescalars for TIMER1		
		EN_PRESCALAR0_t prescalar = PRESCALAR0_1;
		for(i=0;i<5;i++)
		{
			if((config.freq/PRESCALARS[i] < (65536.0/desired)) && ((config.freq/PRESCALARS[i]) > 0))				//Find a suitable prescalar
			{
				prescalar = PRESCALARS[i];
				found = 1;
				break;
			}
		}
		
		if (found==0){
			return 0;												/*Frequency doesn't match desired delay try dividing it*/
		}
		else{
			adjustPrescalarT1(prescalar);							/*Adjust PreScalars registers*/
			
			TCNT1H =((uint16_t) (65536 - ((float)((config.freq*desired)/prescalar)))) >> 8;			/*Put high 8 bits in high reg*/
			TCNT1L =((uint16_t) (65536 - ((float)((config.freq*desired)/prescalar)))) && 0x00FF;	/*put least 8 bits in low reg*/
			
			while(GETBIT(TIFR,2)==0);													/* Wait for overflow to rise */	
			SETBIT(TIFR,2);  															/* Clear the flag */
			
			return 1;
		}

	}	
	#endif
return 0;
}
/*
 *Function to generate PWM with 8bit resolution
 *INPUTS: uint8_t holds the duty cycle percentage, ST_TIMER_config_t timer config
 *CONDITIONs on input:  ============================== dutyCycle percentage must be between 0 and 100 ======================================
 *return 0 in input error type and 1 in success.
 */
uint8_t Timer_generate_8bitRes_PWM(uint8_t dutyCycle,ST_TIMER_config_t config)
{
	if (dutyCycle >=0 && dutyCycle <=100)								/*Check for valid input*/
	{
		#if TIMER0_CTRL == ENABLED
			
		if (config.timer == TIMER0){
			OCR0 = ((float)dutyCycle /0.01) * 255;						/*Generate pwm with duty cycle percentage of 255*/
		}
		#endif
			
		#if TIMER2_CTRL == ENABLED
		if (config.timer == TIMER2){
			OCR2 = ((float)dutyCycle /0.01) * 255;
		}
		#endif
		return 1;
	}

	else
		return 0;									//DATA input error
}