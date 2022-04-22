



#include <avr/wdt.h>

char User_response;




/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E




/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
comms_cal;\
set_up_pin_change_interrupt_on_PC5;\
\
setup_one_wire_comms;\
set_up_activity_leds;


//The reset control switch is connected to PC5




/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")

#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}




/************************************************************************************************************************************/
#define initialise_IO \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;

//All ports are initialised to weak pull up (WPU)

#define clear_display   One_wire_Tx_char = 'c';  UART_Tx_1_wire();


#define User_prompt \
while(1){\
do{String_to_PC("r    ");}   while((isCharavailable(40) == 0));\
User_response = Char_from_PC();\
if((User_response == 'r')||(User_response == 'R')) break;} String_to_PC("\r\n");




/************************************************************************************************************************************/


#include "Resources_Bit_ops_2/One_wire_header.h"
#include "Resources_Bit_ops_2/Basic_IO_and_Timer.c"
#include "Resources_Bit_ops_2/Bit_ops_2_subroutines.c"
#include "Resources_Bit_ops_2/One_wire_transactions.c"

#define Rotate_Right_cyclical  while (n < X) {num = Y & 0b10000000; num = num >> 7; Y = Y <<1; Y = Y | num; n++;}
#define Rotate_left_cyclical  while (n < X) {num = Y & 0b00000001; num = num << 7; Y = Y >>1; Y = Y | num; n++;}





#define message_1 \
"\r\nMore on bitwise ops\r\n\
Press r or R at the user prompt\r\n\
and x or X to escape\r\n\
giving 4 modes of operation\r\n"

#define User_instructions \
String_to_PC (message_1);


char logical_op(char, char, char, char);
char binary_char_from_KBD_Local(void);
