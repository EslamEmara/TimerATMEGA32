/*
 * TIMER_RegMap.h
 *
 * Created: 9/4/2021 6:13:25 AM
 *  Author: 20109
 */ 


#ifndef TIMER_REGMAP_H_
#define TIMER_REGMAP_H_

#define REG(n) (*((volatile uint8_t*)(n)))

#define TCCR0				REG(0x53)
#define TCNT0				REG(0x52)
#define OCR0				REG(0x5C)
#define TCCR1A				REG(0x4F)
#define TCCR1B				REG(0x4E)
#define TCNT1H				REG(0x4D)
#define TCNT1L				REG(0x4C)
#define TCCR2				REG(0x45)
#define TCNT2				REG(0x44)
#define OCR2				REG(0x43)
#define TIMSK				REG(0x59)
#define TIFR				REG(0x58)
#define ASSR				REG(0x42)

#define PORTB_DIR			REG(0x37)
#define PORTD_DIR			REG(0x31)




#endif /* TIMER_REGMAP_H_ */