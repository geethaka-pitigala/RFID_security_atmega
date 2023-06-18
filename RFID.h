/*
 * RFID.h
 *
 * Created: 5/12/2022 11:07:11 AM
 *  Author: Geethaka Pitigala
 */ 


#ifndef RFID_H_
#define RFID_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "LCD_lib/lcd.h"
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>  
#include <time.h>
#include <avr/eeprom.h>  /* Include AVR EEPROM header file */


char rfid_validity();
int add_new_RFID_EEPROM(char *rfid_array, char *password_stored);
char rfid_validity_EEPROM();
void master_menu();
int upload_Master_RFID_EEPROM(char *rfid_array);
void RFID_EEPROM_card_create();
void rfid_initialize();
void update_counters(int j);

extern char password_stored[4];
char password_stored[4];
extern int record_no_j;
int record_no_j;



#endif /* RFID_H_ */