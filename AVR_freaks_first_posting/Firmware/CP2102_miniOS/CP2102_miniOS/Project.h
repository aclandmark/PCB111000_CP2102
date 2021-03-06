



#define F_CPU 1000000UL		
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/eeprom.h>

#define display_tick	2000							//2mS assuming a clock of 1MHz
#define comms_tick		200								//  was 200		2mS per transaction of 10 bits
#define half_comms_tick	100								// was 100	


#define wait_for_clock_tick \while (!(TCA0_SINGLE_INTFLAGS & TCA_SINGLE_CMP0EN_bm));\TCA0_SINGLE_INTFLAGS |= TCA_SINGLE_CMP0EN_bm;


#define inc_display_clock			TCA0_SINGLE_CMP0 += display_tick;
#define inc_comms_clock				TCA0_SINGLE_CMP0 += comms_tick;
#define inc_half_comms_clock		TCA0_SINGLE_CMP0 += half_comms_tick;


void Start_TCA0(void);									//Timer used to control display/comms multiplexing 
void Start_TCB0(int);									//Used to control display intensity
void Display_driver(void);								//Display multiplexer
void Char_definition(void);								//Defines a digit in terms of its segments
void Seg_definitions(void);
void comms_transaction(void);							//Transfer data or string
void Transmit_data_byte (char);							//Tx/Rx FW modules which communicate with UNO
char Receive_data_byte (void);
void Disp_CharS(signed char);
void Disp_CharU(unsigned char);
void Format_deci_secs_and_display(void);
void Format_centi_secs_and_display(void);
void timer_utoa(char);




volatile char Tx_symbol, Rx_symbol, Rx_symbol_bkp;
volatile char transaction_type = 0;						//Data/string transfer to/from UNO
volatile char transaction_complete = 0;					//Set to 1 when a data transfer is complete
volatile int byte_counter = 0;							//Counts bytes sent to or received from UNO
char mode;												//Permanent copy of transaction type
volatile int cmp0_bkp;									//Used to merge comms transaction and display multiplexer

char display_buffer[15];
char temp_buffer[15];	
volatile int display_ptr;								//Points to next digit to be driven
long Long_Num_from_UNO, Long_Num_to_UNO;
float Float_Num_to_UNO, Float_Num_from_UNO;
char cr_keypress = 0;									//Set to 1 when user presses carriage return
unsigned char data_byte[4];								//32 bit numbers are split into 4 bytes for transmission
volatile int data_byte_ptr = 0;							//Points to next FPN/long byte to be transfered to the UNO
volatile char one_char;									//Displayed as both digit and in binary form
char sign_bit;											//Used when displaying char as digit and binary



char * char_ptr;										//Used to convert float to four separate bytes
float * float_ptr;
char sign;
signed char expt;

volatile char busy_flag = 0;							//Data processing in progress: Do not poll Atmega328
int brightness_control;
int digit_num;
int  letter;

char charH, charL;										//Used for clock/stop watch
char Hours, Minutes, Seconds;
char deci_Secs, centi_Secs;
char stop_watch_mode;

long deci_sec_counter;
long centi_sec_counter;




 
 #define I2C_Tx_any_segment \
  switch (letter){\
	 case 'A': case 'a': letter = 0; break;\
	 case 'B': case 'b': letter = 3; break;\
	 case 'C': case 'c': letter = 4; break;\
	 case 'D': case 'd': letter = 2; break;\
	 case 'E': case 'e': letter = 5; break;\
	 case 'F': case 'f': letter = 6; break;\
	 case 'G': case 'g': letter = 1; break;\
 default: letter = 8; break;	}\
 if(letter == 8)break;\
 if((digit_num >= 8) || (digit_num < 0))break;\
 \
 if (transaction_type == 'c'){clear_digits;clear_display;clear_display_buffer;}\
 if (transaction_type == 'b'){if(display_buffer[letter] & (1 << digit_num))display_buffer[letter] &= (~(1 << digit_num));\
 else display_buffer[letter] |= (1 << digit_num);}
 
 
 
 
#define display_buffer2temp \
null_bit_counter = 0; \
clear_temp_buffer;\
for(int m = 0; m <= 14; m++)\
{if(!(display_buffer[14-m]))null_bit_counter += 1; else break;}\
for(int m = 0; m <= 14-null_bit_counter; m++)\
temp_buffer[m] = display_buffer[14-null_bit_counter - m];



#define temp2display_buffer \
null_bit_counter = 0;\
for(int m = 0; m <= 14; m++)\
{if(!(temp_buffer[14-m]))null_bit_counter += 1; else break;}\
for(int m = 0; m <= 14-null_bit_counter; m++)\
display_buffer[m] = temp_buffer[14-null_bit_counter - m];



#define Combine_dp \
array_ptr = 0;\
if (temp_buffer[0] == '.'){temp_buffer[0] = '0' | 0x80;}\
else\
{for(int m = 0; m <= 14; m++)\
{if (temp_buffer[m] != '.' )continue;\
else array_ptr = m; break;}\
\
temp_buffer[array_ptr-1] |= 0x80;\
for (int m = array_ptr; m <=13; m++)\
temp_buffer[m] = temp_buffer[m+1];}



#define extract_dp \
array_ptr = 0;\
for(int m = 0; m <= 14; m++)\
{if (!(temp_buffer[m] & 0x80))continue;\
else temp_buffer[m] &= 0x7F;\
array_ptr = m; break;}\
for(int  m = 14; m >=array_ptr+2; m--)\
temp_buffer[m] = temp_buffer[m-1];\
temp_buffer[array_ptr + 1] = '.';



#define Remove_lagging_zeros \
array_ptr = 14;\
while ((temp_buffer[array_ptr] == 0) ||\
(temp_buffer[array_ptr] == '0'))\
{temp_buffer[array_ptr] = 0;\
array_ptr -= 1;}


#define Left_justify_number \
while(1){array_ptr = 0;\
for (int m = 14; m; m--)\
display_buffer[m] = display_buffer[m - 1];\
display_buffer[array_ptr++] = 0;\
if (display_buffer[7]) break;}


#define check_for_dp \
array_ptr = 14;\
while ((array_ptr)&&\
(!(display_buffer[array_ptr] & 0x80)))\
array_ptr -= 1;



#define Add_dp_if_missing \
if (!(array_ptr)){\
array_ptr = 0;\
for(int m = 0; m <= 14; m++)\
{if((display_buffer[m] == 'E') ||\
(display_buffer[m] == 'e'))array_ptr = m;}\
if(array_ptr)\
display_buffer[array_ptr + 1] |= 0x80;\
\
if (!(array_ptr))\
{array_ptr = 14;\
while ((array_ptr)&&\
(!(display_buffer[array_ptr] & 0x80)))\
array_ptr -= 1;\
if (!(array_ptr))\
display_buffer[0] |= 0x80;}}



#define Insert_sign \
if (sign == '-'){\
for(int  m = 14; m; m--){\
temp_buffer[m] = temp_buffer[m - 1];}\
temp_buffer[0] = '-';}



#define save_brightness_control \
eeprom_write_byte((uint8_t*)0xFF, brightness_control >> 8);\
eeprom_write_byte((uint8_t*)0xFE, brightness_control);


#define restore_brightness_control \
brightness_control = (eeprom_read_byte((uint8_t*)0xFF) << 8)\
+ eeprom_read_byte((uint8_t*)0xFE);



#include "../Resources/One_wire_transactions.c"
#include "../Resources/Display_header.h"
#include "../Resources/FPN_subroutines.c"
#include "../Resources/Timer_subroutines.c"
