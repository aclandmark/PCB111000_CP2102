/*

The entire commentary is programmed into flash when PCB111000_CP2102 is initially set up

The commentary is split into pages each of which starts with three * characters
and ends with the string *\0
Pages contain strings each of which is terminated in a null character

This program prints out the strings one at a time from a particular page

Three subroutines are included:
address_page_num() returns the address of a particular page
string_counter() returns the number of strings on the page
print_string_num() Formats and prints out the strings

The first string starts at location 0x607F, and occupies addresses below 0x607F.
The application and its text strings share the flash from addresses zero to 0x607F (>23kB).

Compile it using optimisation level s ONLY
Rx/Tx work at 57.6k
*/




#include "Text_verification.h"


int char_counter;																	//Counts the number of characters on a page


unsigned int address_page_num (unsigned char, int);
char string_counter(int);
void print_string_num(int, int);
void newpara(void);
void newline(void);


int main (void){

	char Num_strings;																//The number of strings on a single page
	int  page_address;																//The start address of the page
	int start_address;																//The start address of the commentary																	
	char next_string_no = 1;														//The number of the next string to be printed
	unsigned char Page_num_string[2];												//Enables user to enters required page number 
	unsigned char Page_num;															//Page number in binary form
	char keypress;
		
	char_counter = 0;																//counts the number of characters in the text file (excludes \r & \n)

	sendString("\r\n");
	start_address =	0x607F;															//start address of text
	
	sendString("Page number 1 - 12?\r\n\r\n\r\n\r\n");
	
	keypress = waitforkeypress();													//User enters page number
	Page_num_string[0] = keypress - '0';
	Page_num_string[1] = 0;
	if(isCharavailable(75)){Page_num_string[1] = Page_num_string[0]; 
	Page_num_string[0] = receiveChar() - '0';}
	
	Page_num = Page_num_string[1] * 10 + Page_num_string[0];						//Convert page number string to binary
	
	if (Page_num >= 12){wdt_enable(WDTO_15MS);										//page does not exist	
	while(1);}
	
	page_address = address_page_num(Page_num, start_address);						//Address in flash of required page
	Num_strings = string_counter(page_address);										//Number of strings on the page
		
	while(next_string_no <= Num_strings){											//Exit when last string on page has been printed
		
	print_string_num(next_string_no++,page_address);
	
	waitforkeypress();	}															//Wait for keypress before printing next string 

	sendString("No page!");
	
	wdt_enable(WDTO_15MS);															//Restore the p/r/t/D user prompt	
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
				if(star_counter == 3)break;}
			else star_counter = 0;}
		Page_num += 1;}
		Page_address = Prog_mem_address_H;
	Page_address = (Page_address << 8) | Prog_mem_address_L;
	return --Page_address;}




char string_counter(int start_address){														//Scroll through text section of flash counting the '\0' chars
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


