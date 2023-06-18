#include "keypad.h"

int password_req(char password_stored[4])
{
	int e , flag = 1, count = 0;
	//char pass[4]={'3','3','3','3'};
	char arr[4];
	
	lcd_init(LCD_DISP_ON_CURSOR); /*initialize lcd,display on, cursor on */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */
	
	DDRC = 0xF0;
		
	lcd_puts("INPUT PASSCODE");
	
	char keypad()
	{
		while(1){
			PORTC=0XAF;
			e=PINC&0X0F;
			switch(e)
			{
				case 0X07:
				return('#');
				case 0X0B:
				return('9');
				case 0X0D:
				return('6');
				case 0X0E:
				return('3');
			
			}
			
			
			PORTC=0XDF;
			e=PINC&0X0F;
			switch(e)
			{
				case 0X07:
				return('0');
				case 0X0B:
				return('8');
				case 0X0D:
				return('5');
				case 0X0E:
				return('2');
				
			}
			PORTC=0XEF;
			e=PINC&0X0F;
			switch(e)
			{
				case 0X07:
				return('*');
				case 0X0B:
				return('7');
				case 0X0D:
				return('4');
				case 0X0E:
				return('1');
				
			}
			
		}
	}
	lcd_gotoxy(0,1);
	
	while(1)
	{
		for (int i = 0; i<4; i++)
		{
			lcd_gotoxy(i,1);
			arr[i] = keypad();
			lcd_putc(arr[i]);
			_delay_ms(500);			
		}
		for(int j = 0; j<4; j++)
		{
			if(arr[j] != password_stored[j])
			{
				flag = 0;
			}
			count++;
		}
		if(flag == 1 && count == 4)
		{ 
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("LOGGED IN");
			_delay_ms(2000);
			return 1;
		}
		if (flag == 0 && count == 4)
		{
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();
			lcd_puts("SORRY TRY AGAIN");
			_delay_ms(2000);
			return 0;
		}
	}
}


