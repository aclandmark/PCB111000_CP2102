

#include "../Resources/Display_header.h"


void comms_transaction (void){if (!(transaction_type))											//No transaction in progress
{Rx_symbol = Receive_data_byte();									//Poll the UNO
if((unsigned char)Rx_symbol == 0xFF)return;							//No response from UNO
if (!(byte_counter))												//Response from UNO initiates new transaction
{byte_counter = 1;													
transaction_type = Rx_symbol;										//First symbol received defines transaction type

switch(transaction_type){
	
	case 'c':	clear_digits; clear_display; 
				clear_display_buffer; 
				transaction_complete = 1;
				byte_counter = 0;				
				break;
				
	case 'F':	CCP = 0xD8; WDT.CTRLA = 3; while(1); break;			//32mS watch dog period
	
	case 'G':	if(brightness_control == 1450)
				brightness_control = 150;
				else brightness_control = 1450;
				save_brightness_control;
				transaction_complete = 1;
				byte_counter = 0;
				break;
				}
	
return;}}
	
	
switch (transaction_type){											//Transaction in progress									

case 'a':															///One_wire_Tx_2_integers
display_buffer[byte_counter - 1] = Receive_data_byte();
byte_counter += 1;
if(byte_counter == 5){
for(int m = 4; m<=14; m++)display_buffer[m] = 0;
transaction_complete = 1;byte_counter = 0; } 
break;

case 'b': switch(byte_counter){
	case 1: letter = Receive_data_byte(); byte_counter += 1; break;		//I2C_Tx_any_segment()
	case 2: digit_num = Receive_data_byte(); byte_counter = 0;
			transaction_complete = 1; break;} break;	

case 'c': break;													//Clear display and display buffer

case 'A':															//Receiving long number string
case 'B':															//Receiving FPN string
Rx_symbol = Receive_data_byte();
if(Rx_symbol == 1){Rx_symbol = 0; cr_keypress = 1;}					//Carriage return detected
		
display_buffer[byte_counter - 1] = Rx_symbol;						//Put symbol in display buffer
byte_counter += 1;
if(byte_counter == 10)												//Display full: end transaction
{transaction_complete = 1; byte_counter = 0; }
break;

		
case 'C':															//Receive long binary number
Rx_symbol = Receive_data_byte();
Long_Num_from_UNO = (Long_Num_from_UNO << 8) | 
Rx_symbol; byte_counter += 1;
if (byte_counter == 5)												//Four bytes received
{transaction_complete = 1; byte_counter = 0;}	break;

			
case 'D':															//Receive FPN binary number
if (byte_counter == 1)												//First byte:set pointers
{float_ptr = &Float_Num_from_UNO;
char_ptr = (char*)&Float_Num_from_UNO;}								//Receive byte
Rx_symbol = Receive_data_byte();
*char_ptr = Rx_symbol;												//Save byte in FPN location
byte_counter += 1;
char_ptr += 1;
if (byte_counter == 5)												//Four bytes received
{transaction_complete = 1; byte_counter = 0;}break;
			
			
case 'E':															//Return binary FPN/long number in binary
Transmit_data_byte(data_byte[data_byte_ptr++]);
byte_counter += 1;
if(byte_counter == 5)												//Four bytes transmitted
{transaction_complete = 1; byte_counter = 0;
data_byte_ptr = 0;}
break;

case 'F': break;													//Resets ATtiny1606
case 'G': break;													//Toggles brightness


}}


/********************CP2102 versionCP2102 version***********************************************************************************************/
char Receive_data_byte (void){
	char Rx_char = 0;
	wait_for_clock_tick;	PORTA.DIR &= ~PIN2_bm;											//Restore WPU	inc_comms_clock;	wait_for_clock_tick;		Rx_char = 0;	for(int m = 0; m <= 7; m++){									//Receive character	inc_comms_clock;	wait_for_clock_tick;	Rx_char = Rx_char << 1;											//Shift left one bit	if (PORTA_IN & PIN2_bm)	Rx_char |= 1;}							//Add new bit	return Rx_char;}



		
	/********CP2102 version********************************************************************************************************************/	
	void Transmit_data_byte (char symbol){				for(int m = 0; m <= 7; m++){								//Transmit first character
		wait_for_clock_tick;
		if (symbol & (1 << (7-m)))PORTA.DIR &= ~PIN2_bm;			//WPU
		else PORTA.DIR |= PIN2_bm;									//Output low
		inc_comms_clock;}		wait_for_clock_tick;
	PORTA.DIR &= ~PIN2_bm;}
	
	