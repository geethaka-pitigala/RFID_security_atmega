/*
 * motor.h
 *
 * Created: 5/12/2022 6:11:58 PM
 *  Author: Aysha
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#ifndef F_CPU
#define F_CPU 16000000UL // 16MHz clock speed
#endif
#include <avr/io.h>
#include <util/delay.h>

int gateOpen(void);
int gateClosed(void);

#endif /* MOTOR_H_ */