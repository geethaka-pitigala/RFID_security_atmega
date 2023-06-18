/*
 * main.c
 *
 * Created: 5/12/2022 11:07:11 AM
 *  Author: Aysha Ramzi
 */ 



#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//import header files
#include "keypad.h"
#include "lm35.h"
#include "RFID.h"
#include "motor.h"
#include "pir.h"


int main(void)
{	
	rfid_initialize();	
	_delay_ms(4000);
	
	//check against RFID codes stored in the EEPROM
	while(1){
		//testcode

		//test end
		
		lcd_clrscr();             /* clear screen of lcd */
		lcd_home();               /* bring cursor to 0,0 */
		lcd_puts("Enter RFID: ");
		_delay_ms(5000);
		switch (rfid_validity_EEPROM())
		{
			case '1':
			{	
				//test code
				lcd_clrscr();             /* clear screen of lcd */
				lcd_home();               /* bring cursor to 0,0 */
				lcd_puts(password_stored);
				_delay_ms(5000);
				//test code end
				if(password_req(password_stored)==1)
					if(temperature_req()==1){
						update_counters(record_no_j);
						lcd_clrscr();             /* clear screen of lcd */
						lcd_home();               /* bring cursor to 0,0 */
						lcd_puts("Welcome..");
						
						_delay_ms(2000);
						//gate open
						lcd_clrscr();             /* clear screen of lcd */
						lcd_home();               /* bring cursor to 0,0 */
						lcd_puts("Gate Open");
						gateOpen();
						//check for the PIR input
						pircheck_or_gracetime();
						_delay_ms(10);
						//close the gate
						lcd_clrscr();             /* clear screen of lcd */
						lcd_home();               /* bring cursor to 0,0 */
						lcd_puts("Gate Closing");
						gateClosed();
					}
						_delay_ms(5000);
						break;
					}				
			case '5':
			case '2':
			{
				update_counters(record_no_j);
				//gate open
				lcd_clrscr();             /* clear screen of lcd */
				lcd_home();               /* bring cursor to 0,0 */
				lcd_puts("Gate Open");
				gateOpen();
				//check for the PIR input
				pircheck_or_gracetime();
				_delay_ms(10);
				//close the gate
				lcd_clrscr();             /* clear screen of lcd */
				lcd_home();               /* bring cursor to 0,0 */
				lcd_puts("Gate Closing");
				gateClosed();
									
				_delay_ms(1000);
				break;
			}
			case '0':
				continue;
		}
	_delay_ms(500);		
	}
}

