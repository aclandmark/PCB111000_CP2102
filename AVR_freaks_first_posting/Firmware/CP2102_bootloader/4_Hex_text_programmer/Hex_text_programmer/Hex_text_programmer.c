/*
Bootloader for PCB111000_CP2102.
Uploads user apps to the Atmega328
Uploads commentary text file to Atmega328 flash when pcb is being set up.

Loaded at address 0x7000
Talks to three other applications
	Random_pattern_generator	Loaded at address 0x6000	A default app that runs in the absence of a user app
	Text_reader					Loaded at address 0x6480	Reads commentary text one page at a time
	Hex_verification			Loaded at address 0x6880
	Text commentary starts at 0x5FFF


EEPROM locations
0x3FF	User cal
0x3FE	User cal
0x3FD	Default cal
0x3FC	Controls reset and program flow						
	Bit 0	WD_RF	If set:	Reset was due to a WDTout			Use setWD_RF and clearWD_RF	
	Bit 1	RunBL	if set:	Running bootloader					Use set_RunBL and clear_RunBL
	Clear this register if POR is detected  (i.e. set to 0xFF)	Use clear_reset_control_reg
	Note: There is no external reset facility. User control is enabled using a switch on PINC3.

0x3FB	prog_counter high byte				No longer used
0x3FA	prog_counter low byte				No longer used
0x3F9	cmd_counter high byte				Number of commands processed by the UART ISR
0x3F8	cmd_counter low byte
0x3F7	One_wire_cal
0x3F6	One wire cal
0x3F5	Watch dog timeout					Set to zero just before SW_reset, set to 0xFF at reset
0x3F4	Used to control text print out  	No longer needed
0x3F3	Used by PRN generators
0x3F2	Used by PRN generators
0x3F1	Reserved or use by PRN
0x3F0	Reserved or use by PRN
0x3EF	Reserved or use by PRN
0x3EE	Reserved or use by PRN
0x3ED	PRN_offset 0, 1 or 2 

*/

#include "Hex_txt_bootloader.h"
#define Version "Hex_txt_bootloader_V1 "

/*#define setWD_RF_bit				eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~1)));
#define setRunBL_bit				eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~2)));
#define clear_reset_control_reg		eeprom_write_byte((uint8_t*)0x3FC, 0xFF);
#define WD_RF_bit_set				(!(eeprom_read_byte ((uint8_t*)0x3FC) & 0x01))
#define RunBL_bit_clear				(eeprom_read_byte ((uint8_t*)0x3FC) & 0x02)			
#define clear_RunBL_bit				eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) | 2));*/	
#define switch_up					(PINC & 0x20)


#define reset_ctl_reg				0x3FC
#define set_POR_bit					eeprom_write_byte((uint8_t*)reset_ctl_reg, ~1)
#define set_WDTout_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg,(eeprom_read_byte((uint8_t*)reset_ctl_reg) & ~2))
#define	set_Run_BL_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg,(eeprom_read_byte((uint8_t*)reset_ctl_reg) & ~4))
#define set_prtD_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg, ~8)
#define prtD_bit_clear				(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 8)			
#define prtD_bit_set				!(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 8)

#define WDTout_bit_set				!(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 2)
#define Run_BL_bit_clear			(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 4)
#define clear_Run_BL_bit			eeprom_write_byte((uint8_t*)reset_ctl_reg, (eeprom_read_byte((uint8_t*)reset_ctl_reg) | 4))		


char mode;																	//'h' for hex file, 't' for text file

int main (void){ 															//Loaded at address 0x7000, the start of the boot loader section
char keypress, eep_offset;

	if((MCUSR & (1<<WDRF)) &&
	(prtD_bit_clear))set_WDTout_bit;										//Record presence of a watch dog time out
	//setWD_RF_bit;
	
	//if(MCUSR & (1<<WDRF))set_WDTout_bit;
	
	
	setup_HW;																//Resets watch dog timer

if (MCUSR & (1 << PORF))													//POR detected
{MCUSR = 0;																	//Clear reset flags
	//clear_reset_control_reg;												
	set_POR_bit;////////////////
	if  (switch_up)															//No user switch activity	
	{MCUCR = (1<<IVCE);MCUCR = 0x0;											//select interrupt vector table starting at 0x0000
	Prog_mem_address_H = 0;
	Prog_mem_address_L = 0;
	read_flash ();															//Check for the presence of a user application
	if (Flash_readout == 0xFF)asm("jmp 0x6000");							//Run the default application (does not use interrupts)
	else asm("jmp 0x0000");}												//Run the user application
	//setRunBL_bit;															//User switch pressed at POR.	Run bootloader
	set_Run_BL_bit;}


																			//Reset caused by user or default application
//if(((WDTout_bit_set) && (Run_BL_bit_clear)) ||
//(prtD_bit_set)){	
																			//Reset caused by user or default application
//if((WDTout_bit_set) && (Run_BL_bit_clear)){

//if ((Run_BL_bit_clear) || (prtD_bit_set)){

if (Run_BL_bit_clear){

Prog_mem_address_H = 0;
Prog_mem_address_L = 0;
read_flash ();
if (Flash_readout == 0xFF)asm("jmp 0x6000");								//Reset default application
else asm("jmp 0x0000");}													//Reset user application

cal_device;																	//Otherwise initiate the bootloader by checking the calibration status

MCUCR = (1<<IVCE);  														//Select the interrupt vector table starting at start of boot section
MCUCR = (1<<IVSEL);

	keypress = 0;
	while(1){
	if (!(keypress)){do{sendString("p/r/t/D  ");}while((isCharavailable(100) == 0));
	keypress = receiveChar();}
	else _delay_ms(100);
	
	switch(keypress){
	case 'p':																//Program user application starting at address 09x0000
		mode = 'h';															//Hex programming mode
		hex_programmer();													//Run programmer subroutine
		asm("jmp 0x6880");													//Run hex verification routine
	
	case 'E':  eep_offset = eeprom_read_byte((uint8_t*)0x3ED);				//Required because EEP location fails after 100,000 writes
				eep_offset += 2;
				eep_offset = eep_offset%6;
	eeprom_write_byte((uint8_t*)0x3ED, eep_offset);
	keypress = 'D'; break;
		
	case 'D':																//Delete first page of the user application
		Prog_mem_address_H = 0;
		Prog_mem_address_L = 0;
		Page_erase ();
		keypress = 'r'; break;
		
	case 'r':																//Run user/default application
		//clear_Run_BL_bit;
		//clear_RunBL_bit;
		//eeprom_write_byte((uint8_t*)0x3F5, 0xFF);							//NEW LINE	Tells user app that r has just been pressed at p/r/t/D prompt
		set_prtD_bit;														//Clears RunBL_bit
		wdt_enable(WDTO_15MS);while(1);
	
	
	case 'T':																//Program text document starting at address	0x5BFF									
		mode = 't';															//Text programming mode
		text_programmer();
		keypress = 0;break;
	
	case 't':																//Read text document
		asm("jmp 0x6480");
		
	default: keypress = 0; break;
		}}
	
return 1;}





	/***************************************************************************************************************************************************/
	ISR(USART_RX_vect){
		
		unsigned char Rx_askii_char;
		
		Rx_askii_char = receiveChar();

		if (mode == 't') get_text(Rx_askii_char);
	if (mode == 'h') get_hex(Rx_askii_char);}
	



	/***************************************************************************************************************************************************/
	ISR(TIMER0_OVF_vect) {														//Timer0 times out and halts at the end of the text file download
		if(text_started == 3)													//Ignore timeouts occurring before start of file download
		{endoftext -= 1; TCCR0B = 0;TIMSK0 &= (~(1 << TOIE0));					//Shut timer down
			inc_w_pointer; store[w_pointer] = 0;								//Append two '\0' chars to the end of the text
		inc_w_pointer; store[w_pointer] = 0; }}




		/***************************************************************************************************************************************************/
	void text_programmer (void){
	int Text_start_address = 0x5FFE;											//address_in_flash;	

	w_pointer = 0; r_pointer = 0;												//Initialise variables
	text_started =0; endoftext =3;txt_counter = 0;
	Rx_askii_char_old = '0';

	sendString("\r\nText_F?\r\n");
			
	Timer_T0_sub_with_interrupt(5,0);											//Start Timer0 with interrupt
	UCSR0B |= (1<<RXCIE0); 														//Activate UART interrupt
	sei();																		//Set global interrupt

	address_in_flash = Text_start_address;										//First character will be stored at 0x607F not 0x607E

	while (1){
	while (r_pointer == w_pointer);												//wait for w_pointer to be incremented

	if(endoftext != 3)endoftext -= 1;											//Indicates that the timer has been shut down

	address_in_sram = (int)(store + r_pointer);									//Address in SRAM of characters to be written to flash
	loc_in_mem_H = address_in_sram >> 8;										//Variables used to pass the address to the assembly routines
	loc_in_mem_L = address_in_sram;

	Prog_mem_address_H = address_in_flash >> 8;									//Pass address in flash to the assembly routines
	Prog_mem_address_L = address_in_flash;										//at which the text is to be written

	write_to_page_buffer();														//assembly routine (note: these always leave the global interrupt flag set)
				
	address_in_flash -= 2;														//next address in flash
	store[r_pointer] = 0;														//clear the contents of the location in array store
	inc_r_pointer;																//restore the value of "r_pointer" to that of "w_pointer"

	if (!((Text_start_address - address_in_flash)%128)){						//If page buffer is full
	address_in_flash += 2;														//Get the address of the first entry in the page
	Prog_mem_address_H = address_in_flash >> 8;									//Prepare the address for the assembly routines
	Prog_mem_address_L = address_in_flash;

	Page_erase ();																//Assembly routine
	page_write();																//Assembly routine
	address_in_flash -=2;}														//Restore address_in_flash
	if(!(endoftext)) break;}													//Break when two '\0' chars have been appended to text stored in the array

	if((Text_start_address - address_in_flash)%128){							//Write remaining chars in partially full page buffer
	address_in_flash += (Text_start_address - address_in_flash)%128 - 126;		//Get address of first character in the page

	Prog_mem_address_H = address_in_flash >> 8;
	Prog_mem_address_L = address_in_flash;

	Page_erase ();
	page_write();
	}UCSR0B &= (~(1<<RXCIE0));cli();
	clear_read_block();															//Subroutine provided in assembly file  (Not required for mode 't'??)
	LEDs_off;}
		
		
		/*********************************************************************************************************/
		void hex_programmer(void){

		int record_counter = 0;

		PageSZ = 0x40; PAmask = 0x3FC0;										//Define flash memory parameters

		prog_led_control = 0;  record_length_old=0;							//Initialise variables
		Flash_flag = 0;  HW_address = 0;  section_break = 0; orphan = 0;
		w_pointer = 0; r_pointer = 0; short_record=0;  cmd_counter = 0;

		sendString("\r\nHex_F?");

		UCSR0B |= (1<<RXCIE0); sei();										//Receive interrupts now active

		new_record();  														//Start reading first record which is being downloaded to array "store"
		start_new_code_block(); 											//Initialise new programming block (usually starts at address zero but not exclusively so)
		Program_record();													//Copy commands from array "store" to the page_buffer
			
		while(1){
		new_record();														//Continue reading subsequent records
		if (record_length==0)break; 										//Escape when end of hex file is reached

		if (Hex_address == HW_address){										//Normal code: Address read from hex file equals HW address and lines contains 8 commands
		switch(short_record){
		case 0: if (space_on_page == (PageSZ - line_offset))				//If starting new page
		{page_address = (Hex_address & PAmask);}break;						//get new page address
						

		case 1:	start_new_code_block();										//Short line with no break in file (indicates start of text string section).
		short_record=0;break;}}
						
		if(Hex_address != HW_address){										//Break in file
		if (section_break){													//Section break: always found when two hex files are combined into one
		if((Flash_flag) && (!(orphan)))
		{write_page_SUB(page_address);}										//Burn contents of the partially full page buffer to flash
		if(orphan) write_page_SUB(page_address + PageSZ);} 					//Burn outstanding commands to the next page in flash
						
		if(page_break)														//In practice page breaks and short jumps are rarely if ever found
		{if((Flash_flag) && (!(orphan)))									//Burn contents of the partially filled page buffer to flash
		{write_page_SUB(page_address);}
		orphan = 0;}
						
		start_new_code_block();												//A new code block is always required where there is a break in the hex file.
		short_record=0;}
					
		Program_record();													//Continue filling page_buffer

		if (!(++record_counter%10))sendChar('*');}

		UCSR0B &= (~(1<<RXCIE0));	cli();									//download complete, disable UART Rx interrupt
		LEDs_off;
		while(1){if (isCharavailable(5)==1)receiveChar();else break;}		//Clear last few characters of hex file
				
		if((Flash_flag) && (!(orphan))){write_page_SUB(page_address);}		//Burn final contents of page_buffer to flash
		if(orphan) {write_page_SUB(page_address + PageSZ);}cli();

		clear_read_block();													//Subroutine provided in assembly file

		eeprom_write_byte((uint8_t*)0x3F9, cmd_counter >> 8);				//Save "cmd_counter"		Commands counted by the ISR
		eeprom_write_byte((uint8_t*)0x3F8, cmd_counter);}




		/**********************************************************************************************************************************/
		void get_text(char Rx_askii_char){									//Parses text file download and saves results to a buffer store

		if((Rx_askii_char != '*') && (!(text_started)))return;				//Ignore header text occuring before a line of * characters
		if((Rx_askii_char == '*')&&(!(text_started)))						//The number of * characters is not critical only one is required
		{ text_started = 1;return;}
		if((Rx_askii_char == '*')&&(text_started == 1))return; 				//Ignore carriage returns occurring before the first text string
		else {if (text_started == 1)text_started = 2;}
		if((text_started == 2) && ((Rx_askii_char == '\r')
		|| (Rx_askii_char == '\n')))return; else text_started = 3;			//Enter main area of text file containing strings to be written to flash

		if ((Rx_askii_char == '\r') || (Rx_askii_char == '\n')){			//Check for '\r' and or '\n' and convert to a single '\0' character
		if (Rx_askii_char_old == '\0') return;
		else Rx_askii_char = '\0';}

		TCNT0 = 0;

		if(!(txt_counter%2)){												//Each location in array "store" holds two askii characters
		store[w_pointer] = Rx_askii_char;
		store[w_pointer] = store[w_pointer] << 8;}							//"w_pointer" gives address in array of the next free location
		else{store[w_pointer] += Rx_askii_char;
		inc_w_pointer;}
		txt_counter = (txt_counter + 1);									//"txt_counter" gives the number of characters downloaded
		Rx_askii_char_old = Rx_askii_char;
			
		if(txt_counter & 0b10000000) {LEDs_on;}
		else {LEDs_off;}}
			
			
			



	/***********************************************************************************************************************************/
			
	void get_hex(char Rx_askii_char){										//Parses hex file download and saves results to the buffer store

	unsigned char Rx_Hex_char=0;
	int local_pointer;
				
	if (Rx_askii_char == ':')counter = 0;									//First char of hex file is ':'
	else {if (Rx_askii_char <= '9')
	Rx_Hex_char = Rx_askii_char - '0'; 										//Convert chars '0' to '9' to numbers 0 to 9
	else Rx_Hex_char = Rx_askii_char - '7';}								//and chars 'A' to 'F' to numbers 0xA to 0xF

	switch (counter){
	case 0x0:  	break;														//Detect -:- at start of new line
	case 0x1: 	tempInt1 = Rx_Hex_char<<4;  break;							//Acquire first digit
	case 0x2: 	tempInt1 += Rx_Hex_char;  									//Acquire second digit and combine with first to obtain number of commands in line
	char_count = 9 + ((tempInt1) *2); 										//Calculate line length in terms of individual characters
	local_pointer = w_pointer++; 											//Update pointer to array "store"
	store[local_pointer] = tempInt1; break;									//Save the number of commands in the line to the array
	case 0x3: 	tempInt1 = Rx_Hex_char<<4;  break;							//Next 4 digits give the address of the first command in the line
	case 0x4:	tempInt1 += Rx_Hex_char; tempInt1=tempInt1<<8; 
	break;																	//Acquire second digit and combine it with first
	case 0x5:	tempInt1 += Rx_Hex_char<<4;  break;							//Continue for third digit
	case 0x6: 	tempInt1 += Rx_Hex_char; 									//Acquire final digit and calculate address of next command
	local_pointer = w_pointer++; 											//Update pointers to array "store"
	store[local_pointer] = tempInt1; break;									//Save address of next command to array "store"
	case 0x7: 	break;														//chars 7 and 8 are not used
	case 0x8: 	break;
	default: 	break;}

	if ((counter > 8)&&(counter < char_count)){								//Continue to acquire, decode and store commands
	if ((counter & 0x03) == 0x01){tempInt1 = Rx_Hex_char<<4;}				//Note: Final two chars at the end of every line are ignored
	if ((counter & 0x03) == 0x02)  {tempInt1 += Rx_Hex_char;}
	if ((counter & 0x03) == 0x03)  {tempInt2 = Rx_Hex_char<<4;}
	if ((counter & 0x03) == 0x0)  	{tempInt2+= Rx_Hex_char;
	tempInt2=tempInt2<<8;tempInt1+=tempInt2;
	local_pointer = w_pointer++;
	store[local_pointer] = tempInt1; cmd_counter++;}}

	counter++;
	w_pointer = w_pointer & 0x1F;	}  										//Overwrites array after 32 entries



