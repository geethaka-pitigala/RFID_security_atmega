
 #include "pir.h"

  void pircheck_or_gracetime(void)
  {
	 DDRC = DDRC&0b01111111;	/* Set the PIR port(PC7)as input port */
	int gracetime=0;
	while(gracetime<=5000){  
		if ((PIR_Input&0b10000000)==(0b10000000))
			break;  
		_delay_ms(1); 
		gracetime++;
	}
  }


