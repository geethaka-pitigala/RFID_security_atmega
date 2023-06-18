/*
 * keypad.h
 *
 * Created: 5/12/2022 10:48:14 AM
 *  Author: Sandhareka Gunasiri
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#ifndef F_CPU
#define F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include<util/delay.h>
#include "LCD_lib/lcd.h"

int password_req(char password_stored[4]);

#endif /* KEYPAD_H_ */