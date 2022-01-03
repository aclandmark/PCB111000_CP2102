
#include <avr/wdt.h>

char User_response;
char print_buffer[15];
char sign;
signed char expt;

/************************************************************************************************************************************/
#define setup_328_HW \
\
\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
comms_cal;\
set_up_pin_change_interrupt;\
USART_init(0,16);\
setup_one_wire_comms;\
set_up_activity_leds;\
\
sei();

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


/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}




/************************************************************************************************************************************/
#define User_prompt \
while(1){\
do{sendString("f?  ");}   while((isCharavailable(100) == 0));\
User_response = receiveChar();\
if((User_response == 'f') || (User_response == 'i'))break;} sendString("\r\n");



#include "Resources_FPNs\One_wire_header.h"
#include "Resources_FPNs\One_wire_transactions.c"
#include "Resources_FPNs\ASKII_subroutines.c"
#include "Resources_FPNs\Basic_IO_and_Timer.c"
#include "Resources_FPNs\FPN_subroutines.c"
