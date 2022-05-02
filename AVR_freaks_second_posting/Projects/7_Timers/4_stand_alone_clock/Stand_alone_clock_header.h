

#include <avr/wdt.h>

char User_response;

#define message_1 \
"\r\nSTAND-a-LONE CLOCK\r\n\
Use sw1 and 3 to enter time (24Hr clock).\r\n\
\r\n\
Press sw1 to toggle the display on and off\r\n"

#define message_2 \
"Press sw3 to pause or resume the clock\r\n\
To adjust the clock:\r\n"

#define message_3 \
"pulse sw2 then press sw1 and sw3 to advance the time\r\n\
or press and hold sw2 (for 500ms)\r\n\
then press sw1 and sw3 to retard the time\r\n\
Always pulse sw2 when the time is correct\r\n"

#define User_instructions \
String_to_PC(message_1);\
String_to_PC(message_2);\
String_to_PC(message_3);



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
setup_one_wire_comms;\
\
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

#define clear_display             One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define switch_2_up               (PIND & 0x20)

#define User_prompt \
while(1){\
do{String_to_PC("r    ");}   while((isCharavailable(40) == 0));\
User_response = Char_from_PC();\
if((User_response == 'r')||(User_response == 'R')) break;} String_to_PC("\r\n");



/************************************************************************************************************************************/
#define set_up_PCI                  PCICR |= (1 << PCIE2);
#define pause_PCI                   PCICR &= (~(1 << PCIE2));
#define reinstate_PCI               PCICR |= (1 << PCIE2);
#define clear_PCI                   PCIFR |= (1<< PCIF2);
#define enable_PCI                  PCMSK2 |= (1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23);
#define dissable_PCI                PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23)));
#define disable_pci_on_sw2          PCMSK2 &= (~(1 << PCINT21));
#define disable_pci_on_sw1_and_sw3  PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT23)));

#define switch_1_up               (PIND & 0x04)
#define switch_2_up               (PIND & 0x20)
#define switch_3_up               (PIND & 0x80)
#define switch_1_down             (PIND & 0x04)^0x04
#define switch_2_down             (PIND & 0x20)^0x20
#define switch_3_down             (PIND & 0x80)^0x80





/************************************************************************************************************************************/


#include "Resources_Stand_alone_clock/One_wire_header.h"
#include "Resources_Stand_alone_clock/clock_timer_header.h"
#include "Resources_Stand_alone_clock/Basic_IO_and_Timer.c"
#include "Resources_Stand_alone_clock/One_wire_transactions.c"
