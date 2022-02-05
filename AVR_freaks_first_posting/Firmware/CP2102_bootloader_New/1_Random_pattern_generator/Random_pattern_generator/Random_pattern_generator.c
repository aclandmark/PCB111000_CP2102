

/*
Default project included with bootloader.  Runs in the absence of user projects to confirm everything is OK.
It is not loaded at 0x0000 or 0x7000 and cannot easily use interrupts.
The interrupt on pin change (IPC) required by the one wire FW UART is replaced by polling.
*/

#include "Proj_2C1_header.h"													//Contains resources used by template and shared with programmer



int main (void){

	char letter=0;
	char digit_num=0;
	char seg_counter = 0;
	char direction = 0;
	unsigned int PRN_L;

	setup_328_HW;																		//see "Resources\header file
	One_wire_Tx_char = 'c';  UART_Tx_1_wire();											//Clear display

PRN_L = (eeprom_read_byte((uint8_t*)(0x3F2)) << 8) + eeprom_read_byte((uint8_t*)(0x3F3));


	while(1){																			//Generate pattern
		while(seg_counter < 56){															//There are 56 segments in total
			letter = (PRN_L%7) + 'a';
			PRN_L = (PRN_16bit_GEN (PRN_L));
			digit_num = (PRN_L%8);
			if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) continue;		//Continue statements skip back to the top of the while-loop
			if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) continue;		//This is to ensure segments are not turned-off before
			One_wire_comms_any_segment(letter, digit_num);												//they have all been turned on.
			backup_the_display(letter, digit_num);												//keep backup up to date
		seg_counter += 1;
		PRN_L = (PRN_16bit_GEN (PRN_L));}

eeprom_write_byte((uint8_t*)(0x3F2),(PRN_L>>8));
eeprom_write_byte((uint8_t*)(0x3F3),PRN_L);
		direction ^= 1;																		//Toggle the direction_counter value
		seg_counter = 0;
	_delay_ms(500);}
	SW_reset;
return 1;}







/*int main (void){

	char letter=0;
	char digit_num=0;
	char seg_counter = 0;
	char direction = 0;


setup_328_HW;																		//see "Resources\header file
One_wire_Tx_char = 'c';  UART_Tx_1_wire();											//Clear display

while(1){																			//Generate pattern
while(seg_counter < 56){															//There are 56 segments in total
letter = (PRN_16bit_GEN (0)%7) + 'a';
digit_num = (PRN_16bit_GEN (0)%8);
if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) continue;		//Continue statements skip back to the top of the while-loop
if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) continue;		//This is to ensure segments are not turned-off before
One_wire_comms_any_segment(letter, digit_num);												//they have all been turned on.
backup_the_display(letter, digit_num);												//keep backup up to date
seg_counter += 1;}

direction ^= 1;																		//Toggle the direction_counter value
seg_counter = 0;
_delay_ms(500);}
SW_reset;
return 1;}*/



