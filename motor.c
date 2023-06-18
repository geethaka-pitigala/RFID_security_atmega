#include "motor.h"

int gateOpen(void)
{
	DDRB = 0xFF; //PORTB as Output
	
	
		//Rotates Motor in Antilockwise
		PORTB = 0x02; //00000001
		_delay_ms(1000);

		//Stops Motor
		PORTB = 0x01; //00000011
		_delay_ms(500);
		PORTB = 0x03; //00000011
		_delay_ms(1000);


}

int gateClosed(void)
{
	DDRB = 0xFF; //PORTB as Output
	
	
	//Rotates Motor in Clockwise
	PORTB = 0x01; //00000001
	_delay_ms(1000);

	//Stops Motor
	PORTB = 0x02; //00000011
	_delay_ms(500);
	PORTB = 0x03; //00000011
	_delay_ms(1000);


}