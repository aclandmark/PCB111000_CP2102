

#include <avr/wdt.h>


char User_response;
volatile char tick_counter; 
volatile char clock_tick;
unsigned char deci_secs_byte[4];


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
set_up_activity_leds;\
setup_PC_comms(0,16);\
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
#include "Resources_Stand_alone_clock/Basic_IO_and_Timer_extra.c"
#include "Resources_Stand_alone_clock/One_wire_transactions.c"
#include "Resources_Stand_alone_clock/Stand_alone_clock_subroutines.c"





/************************************************************************************************************************************/
