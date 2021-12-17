/*
This program is used to verify that a text file has been successully loaded into flash.
It is loaded onto the UNO device at address 0x6C70 and works alongside the "Hex_text_programmer".
It is accessed by the "Hex_text_programmer" using an assembly jump command and a WDTout returns
controll the the "Hex_text_programmer"
The EEPROM is used to share variables between the two programs.

Compile it using optimisation level s ONLY
Rx/Tx work at 57.6k


Note:

This program contains two subroutines, one to count the number of text strings and one to print out
any given string.  The first string starts at location 0x5C7F, and occupies addresses below 0x5C7F.
The application and its text strings share the flash from addresses zero to 0x5C7F (>23kB).
Each string is termintaed with the '\0' char and the final string is ternimated wth two '\0' chars.
It is anticipated that these subroutines will be used in any user aplication putting strings in flash.
*/




#include "Text_verification.h"
unsigned int address_page_num (unsigned char, int);

int char_counter;

void newpara(void);
char string_counter(int);
void print_string_num(int, int);
void newline(void);


int main (void){

	char Num_strings;																		//The number of strings written to flash
	int  page_address;
	int start_address;
	char next_string_no = 1;																	//Address in flash of first character in a string,
	unsigned char Page_num_string[2];
	unsigned char Page_num;
	char keypress;
	
	
	char_counter = 0;																		//counts the number of characters in the text file (excludes \r & \n)

	sendString("\r\n");
	start_address =	0x5E7F;																	//start address of text
	
	sendString("Page number 1 - 12?\r\n\r\n\r\n\r\n");
	
	keypress = waitforkeypress();
	Page_num_string[0] = keypress - '0';
	Page_num_string[1] = 0;
	if(isCharavailable(75)){Page_num_string[1] = Page_num_string[0]; Page_num_string[0] = receiveChar() - '0';}
	Page_num = Page_num_string[1] * 10 + Page_num_string[0];
	
	if (Page_num >= 12){wdt_enable(WDTO_15MS);													//SW_reset after printing each string
	while(1);}
	
	page_address = address_page_num(Page_num, start_address);
	Num_strings = string_counter(page_address);
	
	
	
	while(next_string_no <= Num_strings){
		
	print_string_num(next_string_no++,page_address);
	
	waitforkeypress();	}

sendString("No page!");
	
		wdt_enable(WDTO_15MS);																	//SW_reset after printing each string
		while(1);

	return 1;}


unsigned int address_page_num (unsigned char Next_page, int start_address){
	char star_counter;
	char next_char;
	unsigned char  Page_num = 1;
	unsigned int Page_address;

if(Next_page == 1)return start_address;

	while(Page_num < Next_page){star_counter = 0;
		while(1){
			Prog_mem_address_H = start_address >> 8;
			Prog_mem_address_L = start_address;
			read_flash ();
			next_char = Flash_readout;
			start_address -= 1;
			if(next_char == '*'){star_counter += 1;
				if(star_counter == 3)break;}											//Should be 3
			else star_counter = 0;}
		Page_num += 1;}
		Page_address = Prog_mem_address_H;
	Page_address = (Page_address << 8) | Prog_mem_address_L;
	return --Page_address;}




char string_counter(int start_address){													//Scroll through text section of flash counting the '\0' chars
	char counter = 0, next, previous = 0; 													//until '\0' '\0' is detected to indicate the end of the
	while(1){																				//last string

		Prog_mem_address_H = start_address >> 8;
		Prog_mem_address_L = start_address;
		read_flash ();																			//assembly subroutine
		next = Flash_readout;																	//result provided by assembly subroutine
		
		if(next == 0){counter += 1; if ((previous == '*')) return counter-1;}
		else char_counter += 1;

		previous = next;
	start_address -= 1;}}





		/***************************************************************************************************************************************************/
		void print_string_num(int text_num, int page_address){									//scroll through text section of flash counting '\0' chars
			int null_counter = 1; 																	//until the start of the required string
			char next,line_length = 0;																//Print the characters until '\0' is detected

			while(1){
				if(null_counter == text_num)break;
				Prog_mem_address_H = page_address >> 8;
				Prog_mem_address_L = page_address;
				read_flash ();
				next = Flash_readout;
				if(next == 0)null_counter += 1;
			page_address -= 1;}

			while(1){
				Prog_mem_address_H = page_address >> 8;
				Prog_mem_address_L = page_address;
				read_flash ();
				if(Flash_readout){sendChar(Flash_readout); 
				if(Flash_readout == ':'){sendString("\t\t");line_length += 20;}
					}else break;
				line_length += 1;
				if(((line_length >= 90) && (Flash_readout == ' ')) || (Flash_readout == '\t'))
				{line_length = 0; sendString("\r\n\r\n");}
			page_address -= 1; }
			newpara();	}





			/*********************************************************************************************/
			void newpara(void){for(int m=0; m<= 10; m++)sendString ("\r\n");}


