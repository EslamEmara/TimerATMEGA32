/*
 * main.c
 *
 * Created: 9/4/2021 6:15:39 AM
 *  Author: 20109
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "BIT_MATH.h"


int main()
{
	CLRBIT(TCCR0, WGM00 );
	SETBIT(TCCR0,WGM01);
	SETBIT(TCCR0,COM00);
	//COM00 = 1;
	CLRBIT(TCCR0, COM01 );

	//COM01 = 0;
	OCR0 = 300000;
	
	while(1)
	{
		
	}
	
	return 0;
}