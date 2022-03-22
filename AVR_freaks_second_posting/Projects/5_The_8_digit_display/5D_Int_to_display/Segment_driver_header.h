

volatile char cr_keypress;

#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();

#include <avr/wdt.h>

char User_response;


#define Int_from_mini_OS \
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){\
Long_Num_from_UNO = Long_Num_from_UNO << 8;\
Long_Num_from_UNO |= num_byte[m];}



/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E

#define zero "abcdef"          //chars a,b,c,d,e,f stored in array named "zero"
#define one "bc"
#define two "abged"
#define three "abcdg"
#define four "fgbc"
#define five "afgcd"
#define six "fegdc"
#define seven "abc"
#define eight "abcdefg"
#define nine "abcfg"
#define null '\0'


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
setup_one_wire_comms;\
set_up_activity_leds;\
sei();

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
#define set_up_pin_change_interrupt      PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define pause_pin_change_interrupt      PCICR &= (~(1 << PCIE1)); 
#define reinstate_pin_change_interrupt    PCICR |= (1 << PCIE1); 

#define Reset_ATtiny1606 \
One_wire_Tx_char = 'F'; UART_Tx_1_wire();


/************************************************************************************************************************************/
#define set_up_PCI_on_sw2         PCICR |= (1 << PCIE2);
#define enable_pci_on_sw2         PCMSK2 |= (1 << PCINT21);
#define switch_2_up               (PIND & 0x20)

/************************************************************************************************************************************/
#define User_prompt \
while(1){\
do{Serial.write("R?    ");}   while((isCharavailable(75) == 0));\
User_response = Serial.read();\
if((User_response == 'R') || (User_response == 'r'))break;} Serial.write("\r\n");



/************************************************************************************************************************************/
#include "Resources_segment_driver\One_wire_header.h"
#include "Resources_segment_driver\One_wire_transactions.c"
#include "Resources_segment_driver\Basic_IO_and_Timer.c"
#include "Resources_segment_driver\First_project_subroutines.c"
