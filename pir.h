/*
 * pir.h
 *
 * Created: 5/13/2022 9:06:21 AM
 *  Author: Sandhareka Gunasiri
 */ 


#ifndef PIR_H_
#define PIR_H_

#ifndef F_CPU
#define F_CPU 16000000UL // 16MHz clock speed
#endif

 #include <avr/io.h>
#include <util/delay.h>
 #define PIR_Input PINC
 
 void pircheck(void);

#endif /* PIR_H_ */