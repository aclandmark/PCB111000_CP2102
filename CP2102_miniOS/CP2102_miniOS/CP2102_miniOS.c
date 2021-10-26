/*
Program runs on Attiny1606
and is compiled using default Studio 7 compiler settings


Note: This program is to be compatible with user projects running on an Atmega328 clocked at only 8MHz
The peripheral clock frequency must therefore be reduced from 2MHz to 1MHz.
Brightness control settings must be reduced from 500 and 3500 to 250 and 1750

Note:The one wire FW UART now runs at 5KHz (i.e. not 10KHz) and the time per transaction is now 2mS
The display multiplexer period  is still 2mS (to avoid flicker) but a transaction takes 2 periods rather than one  

EEPROM use:	
	0xFF	Brightness control high byte
	0xFE	Brightness control low byte
	0xFD	Reset control

*/


#include "Project.h"
int mag(int);


int main(void){
		
	char cal_factor;											//Used to adjust internal oscillator frequency
	char null_bit_counter;										//Counts number of blank display digits
	int array_ptr;												//Points to display digits
	
	
	CPU_CCP = 0xD8;												//Config change protection key
	CLKCTRL_MCLKCTRLB = CLKCTRL_PDIV_16X_gc | 1;				//Generates 1MHz Peripheral clock
	
	cal_factor = CLKCTRL_OSC20MCALIBA - 1;						//Adjust calibration factor if necessary
	CPU_CCP = 0xD8;
	CLKCTRL_OSC20MCALIBA = cal_factor;
	
	if(RSTCTRL.RSTFR & RSTCTRL_PORF_bm)
	{RSTCTRL.RSTFR |= RSTCTRL_PORF_bm;
		brightness_control = 250;
		eeprom_write_byte((uint8_t*)0xFF, brightness_control >> 8);
		eeprom_write_byte((uint8_t*)0xFE, brightness_control);}				//1450;//250;100			1500ok	1550 NOk					//Selects low brightness at reset
	else {brightness_control = (eeprom_read_byte((uint8_t*)0xFF) << 8)
		+ eeprom_read_byte((uint8_t*)0xFE);}
	
	
	//if((eeprom_read_byte((uint8_t*)0xFD)) == 0xFF);
	//else {eeprom_write_byte((uint8_t*)0xFD, 0xFF); _delay_ms(500);}
	
	
	
	
   	PORTA.DIR &= ~PIN2_bm;										//Configure comm port as input
   	 PORTA.OUT &= ~(PIN2_bm);										//I/O pin low when configured as output
   	 PORTA.PIN2CTRL |= PORT_PULLUPEN_bm;							//Pull-up enabled 
   
   
   
   sei();
   Start_TCA0();												//Display (2mS) tick rate
   //sei();
	
	while(1){
		while(!(transaction_complete));							//Wait here for requests from the UNO
		transaction_complete = 0;
		busy_flag = 1;											//Do not contact UNO until data processing is complete
		
	switch (transaction_type){									//Transaction complete: Process the data
	
	case 'a': break;											//One_wire_Tx_2_integers()
	case 'b': I2C_Tx_any_segment; break;			
		
	case 'A':													//When "cr" detected convert string from UNO to long number
	if(cr_keypress == 1){
	cr_keypress = 0;
	display_buffer2temp;										//Reverse string prior to conversion to binary
	Long_Num_to_UNO = atol(temp_buffer);	
	for(int m = 0; m <= 3; m++)
	data_byte[m] = Long_Num_to_UNO >> (8*(3-m));}				//Split long number into 4 bytes for re-transmission
	break;
		
	case 'B':													//When "cr" detected convert string from UNO to float
	if(cr_keypress == 1){
	cr_keypress = 0;
	check_for_dp;
	Add_dp_if_missing;											//FP arithmetic requires numbers with a dp
	display_buffer2temp;										//Reverse string prior to conversion to a FPN
	extract_dp;													//Display merges the dp with a digit  											
	Float_Num_to_UNO = atof(temp_buffer);
	char_ptr = (char*)&Float_Num_to_UNO;						//Split the number into bytes ready for return to the UNO
	for (int m = 0; m <= 3; m++)
	{data_byte[m] = *char_ptr;
	char_ptr += 1;}
	}break;
		
		
	case 'C':													//Convert long from UNO to string
	clear_display_buffer;
	clear_temp_buffer;
	ltoa(Long_Num_from_UNO, temp_buffer, 10);
	temp2display_buffer;										//Reverse string prior to display	
	break;
			
	case 'D': 													//Convert float from UNO to string
	Float_Num_from_UNO  = *float_ptr;
	ftoaL(Float_Num_from_UNO);
	Combine_dp;		 
	Insert_sign;
	Remove_lagging_zeros;
	temp2display_buffer;										//Reverse string prior to display
	if (expt){Left_justify_number;
	Add_exponent ();}
	break;
		
	case 'E':													//Return binary number (long or float) to UNO
	for(int m = 0; m <= 7; m++)
	temp_buffer[m] = display_buffer[m];							//Flash display
	clear_display_buffer;
	_delay_ms(100);
	for(int m = 0; m <= 7; m++)
	display_buffer[m] = temp_buffer[m];
	break;
	
	case 'F': break;											//Resets ATtiny1606									
	case 'G': break;											//Toggles brightness
	
	
	
	}
	if(transaction_type != 'G')mode = transaction_type;	
	transaction_type = 0;
	busy_flag = 0;
	}}



/*****************************************************************************************************************************/
	void Start_TCA0(void){										//Clock that controls display and FW comms port
	
	//_delay_ms(50);
	clear_display_buffer;										//Generate test display
	clear_digits;
	clear_display;
	Set_display_ports;
	display_ptr = 0;
	TCA0_SINGLE_CNT = 0;										//Initialise counter
	TCA0_SINGLE_CMP0 = display_tick;							//2mS period for 2MHz clock
	TCA0_SINGLE_CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | 1;			//Start clock with 2MHz clock
	TCA0_SINGLE_INTCTRL |= TCA_SINGLE_CMP0EN_bm;}				//Interrupt flag on compare match/*****************************************************************************************************************************/		//TIMES must be halved from 1800 to 900 and from 2200 to 1100///////////////////		ISR (TCA0_CMP0_vect){										//ISR which responds to clock ticks	TCA0_SINGLE_INTFLAGS |= TCA_SINGLE_CMP0EN_bm;				//Clear the interrupt flag	if(display_ptr <= 7)										//Drive the 8 display digits	{Display_driver();	if(display_ptr < 7){inc_display_clock;}						//Setup 2mS clock tick for first 7 digits	else TCA0_SINGLE_CMP0 += 1800;								//setup 0.9mS clock tick for last digit	display_ptr += 1;	return;}	display_ptr += 1;	cmp0_bkp = TCA0_SINGLE_CMP0 + 2200;							//Save 1.1mS clock tick for first digit	if (!(busy_flag))	{inc_comms_clock;											//only poll UNO if no transactions are ongoing	PORTA.DIR |= PIN2_bm;										//initiate start pulse	comms_transaction();}										//Poll the UNO	TCA0_SINGLE_CMP0 = cmp0_bkp;								//Reinstate the 1.1ms clock tick	display_ptr = 0;}										//Set display_pointer to the first digit											/*****************************************************************************************************************************/	void Display_driver(void){				switch(display_ptr){			case 0: digit_0; break;			case 1: digit_1; break;			case 2: digit_2; break;			case 3: digit_3; break;			case 4: digit_4; break;			case 5: digit_5; break;			case 6: digit_6; break;			case 7: digit_7; break;}						switch(mode){		case 'A': case'B': case 'C': case 'D': case 'E':		Char_definition(); break;				case 'a':
		
		switch (display_ptr){
			
			case 0: if(display_buffer[0] & 0x01) one_U; if(display_buffer[0] & 0x02) ONE_U;
					if(display_buffer[1] & 0x01) one_L; if(display_buffer[1] & 0x02) ONE_L;
					 break;
			
			case 1: if(display_buffer[0] & 0x04) one_U;  if(display_buffer[0] & 0x08) ONE_U;
					if(display_buffer[1] & 0x04) one_L;  if(display_buffer[1] & 0x08) ONE_L; 
					break;
					
			case 2: if(display_buffer[0] & 0x10) one_U; if(display_buffer[0] & 0x20) ONE_U;
					if(display_buffer[1] & 0x10) one_L; if(display_buffer[1] & 0x20) ONE_L;
					break;
					
			case 3: if(display_buffer[0] & 0x40) one_U;  if(display_buffer[0] & 0x80) ONE_U;
					if(display_buffer[1] & 0x40) one_L;  if(display_buffer[1] & 0x80) ONE_L;
					break;
					
					
			case 4: if(display_buffer[2] & 0x01) one_U; if(display_buffer[2] & 0x02) ONE_U;
					if(display_buffer[3] & 0x01) one_L; if(display_buffer[3] & 0x02) ONE_L;
					break;
			
			case 5: if(display_buffer[2] & 0x04) one_U;  if(display_buffer[2] & 0x08) ONE_U;
					if(display_buffer[3] & 0x04) one_L;  if(display_buffer[3] & 0x08) ONE_L;
					break;
			
			case 6: if(display_buffer[2] & 0x10) one_U; if(display_buffer[2] & 0x20) ONE_U;
					if(display_buffer[3] & 0x10) one_L; if(display_buffer[3] & 0x20) ONE_L;
					break;
			
			case 7: if(display_buffer[2] & 0x40) one_U;  if(display_buffer[2] & 0x80) ONE_U;
					if(display_buffer[3] & 0x40) one_L;  if(display_buffer[3] & 0x80) ONE_L;
					break;
					}break;				case 'b': Seg_definitions(); break;		}		Start_TCB0(brightness_control);										//TCB0 controls the brightness
		}									
								/******************************************************************************************************************/	void Char_definition()
	{switch (display_buffer[display_ptr]){
	case '0': zero; break;
	case '1': one; break;
	case '2': two; break;
	case '3': three; break;
	case '4': four; break;
	case '5': five; break;
	case '6': six; break;
	case '7': seven; break;
	case '8': eight; break;
	case '9': nine; break;
	case '-': minus; break;
			
	case 'E': case 'e': exponent; break;
	case ('0' | 0x80): zero_point; break;
	case ('1' | 0x80): one_point; break;
	case ('2' | 0x80): two_point; break;
	case ('3' | 0x80): three_point; break;
	case ('4' | 0x80): four_point; break;
	case ('5' | 0x80): five_point; break;
	case ('6' | 0x80): six_point; break;
	case ('7' | 0x80): seven_point; break;
	case ('8' | 0x80): eight_point; break;
	case ('9' | 0x80): nine_point; break;
	case ('-' | 0x80): minus_point; break;}}
	

/*******************PCB111000_CP2102**********************************************************************/
void Seg_definitions(){ char m=0;
	switch(display_ptr){
		case 0: m = 0x01; break;
		case 1: m = 0x02; break;
		case 2: m = 0x04; break;
		case 3: m = 0x08; break;
		case 4: m = 0x10; break;
		case 5: m = 0x20; break;
		case 6: m = 0x40; break;
		case 7: m = 0x80; break;}
	if (display_buffer[0] & m) PORTB.OUT &= (~(seg_a));
	if (display_buffer[1] & m) PORTC.OUT &= (~(seg_g));
	if (display_buffer[2] & m) PORTB.OUT &= (~(seg_d));
	if (display_buffer[3] & m) PORTA.OUT &= (~(seg_b));
	if (display_buffer[4] & m) PORTB.OUT &= (~(seg_c));
	if (display_buffer[5] & m) PORTA.OUT &= (~(seg_e));
	if (display_buffer[6] & m) PORTC.OUT &= (~(seg_f));}
	
	
/*************FP_display PCB*****************************************************/
/*void Seg_definitions(){ char m=0;
	switch(display_ptr){
		case 0: m = 0x01; break;
		case 1: m = 0x02; break;
		case 2: m = 0x04; break;
		case 3: m = 0x08; break;
		case 4: m = 0x10; break;
		case 5: m = 0x20; break;
		case 6: m = 0x40; break;
	case 7: m = 0x80; break;}
	if (display_buffer[0] & m) PORTB.OUT &= (~(seg_a));
	if (display_buffer[1] & m) PORTC.OUT &= (~(seg_g));
	if (display_buffer[2] & m) PORTB.OUT &= (~(seg_d));
	if (display_buffer[3] & m) PORTB.OUT &= (~(seg_b));
	if (display_buffer[4] & m) PORTB.OUT &= (~(seg_c));
	if (display_buffer[5] & m) PORTC.OUT &= (~(seg_e));
if (display_buffer[6] & m) PORTC.OUT &= (~(seg_f));}*/














/*void Seg_definitions(){ char m=0;
	switch(display_ptr){
		case 0: m = 0x01; illuminate_segments(m);break;
		case 1: m = 0x02; illuminate_segments(m);break;
		case 2: m = 0x04; illuminate_segments(m);break;
		case 3: m = 0x08; illuminate_segments(m);break;
		case 4: m = 0x10; illuminate_segments(m);break;
		case 5: m = 0x20; illuminate_segments(m);break;
		case 6: m = 0x40; illuminate_segments(m);break;
		case 7: m = 0x80; illuminate_segments(m);break;}}



void illuminate_segments(char m){
if (display_buffer[0] & m) PORTB.OUT &= (~(seg_a));
if (display_buffer[1] & m) PORTC.OUT &= (~(seg_g));
if (display_buffer[2] & m) PORTB.OUT &= (~(seg_d));
if (display_buffer[3] & m) PORTB.OUT &= (~(seg_b));
if (display_buffer[4] & m) PORTB.OUT &= (~(seg_c));
if (display_buffer[5] & m) PORTC.OUT &= (~(seg_e));
if (display_buffer[6] & m) PORTC.OUT &= (~(seg_f));	
}
*/



	/*****************************************************************************************************************************/	void Start_TCB0(int BC){						//Controls the display intensity
	TCB0_CNT = 0;									//Initialise counter
	TCB0_CCMP = BC;									//1.75mS for full brightness 0.25ms for low brightness
	TCB0_CTRLA = 1;									//Start the clock	TCB0_INTCTRL = 1;}								//Interrupt flag on compare match
		
	ISR (TCB0_INT_vect){							//Clear display
	TCB0_INTFLAGS = 1;								//Clear interrupt flag
	TCB0_CTRLA = 0;									//Stop the clock	
	clear_digits; clear_display;}	
	
	
	int mag(int m){									//Convert negative number to positive
		int n = 0;
		if (m < 0)n = m * (-1);
		else n = m;
		return n;}