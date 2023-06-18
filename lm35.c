#include "lm35.h"
#include "LCD_lib/lcd.h"

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);

	// ADC Enable and Prescaler of 128
	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read ADC value
uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;

	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete
	// ADSC becomes '0' again
	
	while(ADCSRA & (1<<ADSC));

	return (ADC);
}

int temperature_req()
{
	DDRB=0xff;
	DDRD=0xff;
	uint16_t adc_result0;
	int temp;
	char buffer[10];


	// initialize ADC and LCD
	adc_init();
	lcd_init(LCD_DISP_ON_CURSOR); //CURSOR
	lcd_clrscr();
	lcd_gotoxy(0,0);
	_delay_ms(50);
    
	while(1)
	{
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Check Your");
		lcd_gotoxy(0,1);
		lcd_puts("Temperature");
		_delay_ms(1000);
		lcd_clrscr();
		
		adc_result0 = adc_read(0);      // read ADC value at PA0
		
		temp=adc_result0/2.01;   // finding the temperature

		lcd_gotoxy(0,0);
		itoa(temp,buffer,10);
		lcd_puts("Temperature=");   //display temperature
		lcd_puts(buffer);
		lcd_gotoxy(14,0);
		lcd_puts("C");
		_delay_ms(1000);
		
		if (temp>=37)
		{
			
			lcd_home();
			lcd_gotoxy(0,1);
			lcd_puts("Temp. is High");
			_delay_ms(1500);
			lcd_clrscr();
			
			return 0;
			
		}
		
		else if(temp<37 && temp>=35)
		{   
			
			lcd_home();
			lcd_gotoxy(0,1);
			lcd_puts("Temp is OK");
			_delay_ms(1000);
			lcd_clrscr();
			lcd_gotoxy(0,0);
			
			return 1;
		    
			}
		}
			
	
	
}

