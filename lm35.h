/*
 * lm35.h
 *
 * Created: 5/12/2022 10:53:14 AM
 *  Author: Ayodya Ranthunga
 */ 


#ifndef LM35_H_
#define LM35_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

int temperature_req();
void adc_init();
uint16_t adc_read(uint8_t ch);



#endif /* LM35_H_ */