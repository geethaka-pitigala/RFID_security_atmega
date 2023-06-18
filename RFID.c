#include "RFID.h"

//simulate adding a new card using the EEPROM

int add_new_RFID_EEPROM(char *rfid_array, char *password_stored){
	uint8_t ByteOfData ;
	uint8_t no_records;

	
	no_records = (uint8_t)eeprom_read_byte((const uint8_t*)(750));
	
	for(int i=0; i<13; i++){
		ByteOfData =  (uint8_t)*(rfid_array+i) ;
		eeprom_update_byte (( uint8_t *) (30+ no_records*15 + i), ByteOfData );
	}
	//initialize the counter to 1 on local storage 
	eeprom_update_byte (( uint8_t *) (30+ no_records*15 + 14), (uint8_t)2); // ---user input ID: XcounterStoredIn---
	//initialize the random number set in which we hide the counter value | source random: https://www.tutorialspoint.com/c_standard_library/c_function_rand.html
	for(int i=0; i<9; i++){
		ByteOfData =  (uint8_t)(rand() % 10);
		eeprom_update_byte(( uint8_t *) (315 + i), ByteOfData );
	}
	/*initialize the counter to 1 on card. We are going to store the counter in the 5th location in the garbage array. 
	But the position should be calculated using the serial number of each device.
	We are going to simulate this using the card space we created within the EEPROM
	*/
	eeprom_update_byte (( uint8_t *) (319), (uint8_t)2);  // ---user input ID: XcounterCardIn---
	
	//store the password
	for (int i=0; i<=3;i++)
	{
		eeprom_update_byte(( uint8_t *) (600 + no_records*5 + i), *(password_stored+i) );
	}
	
	no_records++; //update no of records
	eeprom_update_byte (( uint8_t *) (750), (uint8_t)no_records ); //save the record count in EEPROM
	return 1;	
}

//simulate RFID validity check against the SD card using EEPROM
char rfid_validity_EEPROM(){

	uint8_t no_records;
	no_records = (uint8_t)eeprom_read_byte((const uint8_t*)(750));
	//user input through RFID module
	//char usart_in[13] = "111111111111" ;  // ---user input ID: XmainIn--- <moved to rfid_card_create function>
	//read ID number from the RFID card(we are reading this from the card we created in the EEPROM)
	char usart_in[13];
	uint8_t counter_stored, counter_card;
	for(int i=0; i<12; i++){
		usart_in[i] = (char)eeprom_read_byte ((const uint8_t*)(300 + i));
	}
	
	char rfid_stored1[13];
	char valid = '0';
	int counter_valid = 0;
	//check for the master card before others
	for(int i=0; i<13; i++){
			rfid_stored1[i] = (char)eeprom_read_byte ((const uint8_t*)(500 + i));	/* Read master card value from address. And update the temporary array variable. */
		}
		//display RFID code
		lcd_clrscr();
		lcd_home();
		lcd_puts(usart_in);
		_delay_ms(500);
		
		uint8_t not_master = 0;
		for(int i=0; i<12; i++){
			if(usart_in[i]!=rfid_stored1[i])
				not_master = 1;
		}

	if(not_master==1){
		lcd_clrscr();
		lcd_home();
		lcd_puts("Checking..");
		_delay_ms(500);
		//read RFID code from EEPROM
		for(int j=0 ; j<no_records; j++){
			//j starts from 1 to leave out the master card code
			for(int i=0; i<13; i++){
				/* Read value from address. And update the temporary array variable. We can use rfid_stored1 to check against the employee's input code array usart_in.
				If the rfid_stored1 is not equal to the input RFID code*/
				rfid_stored1[i] = (char)eeprom_read_byte ((const uint8_t*)(30+ j*15 + i));	/* Read value from address. And update the temporary array variable. */
			}
			//display RFID code
			lcd_clrscr();
			lcd_home();
			lcd_puts(rfid_stored1);
			_delay_ms(500);
		

			for(int i=0; i<12; i++){
				if(usart_in[i]!=rfid_stored1[i]){
					valid = '0';
					break;					
				}
				if(i==11){
					record_no_j =j;
					valid = '1';
					// read stored counter value
					counter_stored = eeprom_read_byte ((const uint8_t*)(30+ j*15 + 14));
					for (int a=0; a<=3; a++)
					{
						password_stored[a]=(char)eeprom_read_byte ((const uint8_t*)(600+ j*5 + a));
					}
					lcd_clrscr();
					lcd_home();
					lcd_puts("ID valid");
					lcd_gotoxy(0,1);
					lcd_puts("counter check");
					_delay_ms(500);
					// read counter value in card
					counter_card = eeprom_read_byte ((const uint8_t*)(319));
					if(counter_stored==counter_card){
						lcd_clrscr();
						lcd_home();
						lcd_puts("Counter valid");
						counter_valid = 1;

						_delay_ms(500);
						break;
					}
					else{
						counter_valid = 0;
						break;
					}
				}
			}
			if(valid=='0')
				continue;
	
			if(valid=='1' && counter_valid==1){
				lcd_clrscr();
				lcd_home();
				lcd_puts("Card Accepted");
				if((counter_card%2)==0)
					valid = '1';
				else
					valid = '2';
				_delay_ms(500);
				return valid;
			}
			else{
				lcd_clrscr();
				lcd_home();
				lcd_puts("RFID invalid..");
				_delay_ms(500);
				valid = '0';
				break;
			}
		}
	}
	else{
		master_menu();
		valid = '5';
	}
	return valid;
}

//display master card menu
void master_menu(){
	uint8_t selection = 0;

	lcd_clrscr();
	lcd_home();
	lcd_puts("#Master Menu");
	_delay_ms(1000);
	lcd_gotoxy(0,1);          /* go to 2nd row 1st col */
	lcd_puts("Selection: ");
	_delay_ms(1000);
	lcd_clrscr();
	lcd_home();
	lcd_puts("1. New card");
	lcd_gotoxy(0,1);
	_delay_ms(50);
	lcd_puts("2. Initialize");
	_delay_ms(500);
	lcd_clrscr();
	lcd_home();
	lcd_puts("Selection No: ");
	_delay_ms(500);
	lcd_gotoxy(0,1);

	// // ---user input ID: XMstmenu--
	selection = 1; //new card
	lcd_puts("1 - Entered");

	//selection = 2; //initialize
	//lcd_puts("2 - Entered");

	if(selection == 1){
		_delay_ms(500);
		lcd_clrscr();             /* clear screen of lcd */
		lcd_home();               /* bring cursor to 0,0 */
		lcd_puts("Enter RFID: ");
		_delay_ms(500);
		char user_in_RFID[13] = "081245235323"; // ---user input ID: XnewIn---
		add_new_RFID_EEPROM(user_in_RFID, "1234");
		
		lcd_clrscr();             /* clear screen of lcd */
		lcd_home();               /* bring cursor to 0,0 */
		lcd_puts(user_in_RFID);
		_delay_ms(500);
		
		lcd_clrscr();             /* clear screen of lcd */
		lcd_home();               /* bring cursor to 0,0 */
		lcd_puts("Successful");
	}
//	elseif(selection==2){
//		initializeSys(); //further implementation
//	}
}

//Initialize the system for the first time
//void initializeSys(){
//		//further implementation
//}


//upload master card code to EEPROM
int upload_Master_RFID_EEPROM(char *rfid_array){
	uint8_t ByteOfData ;
	for(int i=0; i<13; i++){
		ByteOfData =  (uint8_t)*(rfid_array+i) ;
		eeprom_update_byte (( uint8_t *) (500+i), ByteOfData );
	}
	return 1;
}

//create a separate space for the RFID card in EEPROM
void RFID_EEPROM_card_create(){
	uint8_t ByteOfData;
	time_t t;
	srand((unsigned) time(&t));
	
	char *rfid_array = "041235235325"; // ---user input ID: XmainIn---
	for(int i=0; i<12; i++){
		ByteOfData =  (uint8_t)*(rfid_array+i) ;
		eeprom_update_byte (( uint8_t *) (300 + i), ByteOfData );
	}
	
}

void rfid_initialize(){
	uint8_t no_records = 0;
	eeprom_update_byte (( uint8_t *) (750), (uint8_t)no_records );
	
	lcd_init(LCD_DISP_ON_CURSOR); /*initialize lcd,display on, cursor on */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */
	lcd_puts("Group 09..");        /* type something random */
	lcd_gotoxy(0,1);          /* go to 2nd row 1st col */
	lcd_puts("Project");  /* type something random */
	_delay_ms(500);
	
	
	//EEPROM usage | www.electronicwings.com/avr-atmega/atmega16-eeprom
	lcd_clrscr();
	lcd_home();
	lcd_puts("Writing samples RFID...");
	_delay_ms(500);
	//write MASTER card code to EEPROM
	char masterCard[13] = "111111111111" ;
	upload_Master_RFID_EEPROM(masterCard);
	
	//write a RFID code to EEPROM
	char sample_stored_RFID[13] = "091235235325";
	char *password1 = "1234";
	add_new_RFID_EEPROM(sample_stored_RFID, password1);
	
	//write 2nd sample RFID code to EEPROM
	char sample_stored_RFID2[13] = "041235235325";
	char *password2 = "5678";
	add_new_RFID_EEPROM(sample_stored_RFID2, password2);
	
	lcd_clrscr();
	lcd_home();
	lcd_puts("Done..");
	
	//create virtual RFID card in the EEPROM
	_delay_ms(500);
	lcd_clrscr();
	lcd_home();
	lcd_puts("creating V-RFID");
	RFID_EEPROM_card_create();
}

void update_counters(int j){
	uint8_t counter_stored = eeprom_read_byte ((const uint8_t*)(30+ j*15 + 14));
	//update card counter
	eeprom_update_byte(( uint8_t *) (319), (char)(counter_stored+1) );
	//update local counter
	eeprom_update_byte(( uint8_t *) (30+ j*15 + 14), (char)(counter_stored+1) );
}

//Completed: add a master card authorization to insert a new card *****
//Completed: create a separate data space to simulate a RFID card | size: 30 bytes . 
//In progress: anti spoofing mechanism coding
//TODO: create a method to initialize the system. Should be authorized by master card.

/*System inputs management:
	> search for the relevant input ID to locate the line to edit.
	> Master card code: 111111111111
	> Valid Card codes: 091235235325, 041235235325
	> Input normal card numbers(valid or invalid) or the Master card in input ID "XmainIn"
	> If the above input is master card and you are planning on registering a new card, input the new card number in input ID "XnewIn"
	> Invalid Card codes: any 12 digit long input other than the above two
*/

/*Additional Notes:
	> If the input is detected as master card, the master card menu will be displayed. Otherwise, input will be check agaist the stored records.
	> Based on the counter value stored, we can avoid asking the employees for passwords on their way out
	> Simulatoin scenarios
		+ employee inputs a valid RFID card.        | Relevant input ID: XmainIn
		+ employee inputs an invalid RFID card.		| Relevant input ID: XmainIn
		+ Supervisor inputs the master card. | Relevant input ID: XmainIn | ,Then a menu will be displayed to the user. He/she can use the menu to register a new card. | Relevant input ID: XnewIn |
		+ Card counter value | Relevant input ID: XcounterCardIn
		+ Stored counter value | Relevant input ID: XcounterStoredIn
	> Position of the counter within the card is determined by a simple algorithm applied to the serial number of the device.
	> All values around the counter stored in the card is changed each time the card is used. And the counter is also updated.
	
	Return Codes of rfid_validity_EEPROM()
	--------------------------------------
	 '0' = card invalid
	 '1' = card valid & counter is even | going inside
	 '2' = card valid & counter is odd | going outside
	 '5' = master card operation
*/ 

