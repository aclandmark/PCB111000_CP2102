


#include <avr/wdt.h>

#define newline String_to_PC("\r\n")
char WDT_out_status;

/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E

#define POR_detected                      eeprom_read_byte ((uint8_t*)0x3FC) == 0xFF
#define WDTout_with_interrupt_detected    !(eeprom_read_byte ((uint8_t*)0x3F5))
#define Signal_WDTout_with_interrupt      eeprom_write_byte((uint8_t*)0x3F5, 0);
#define Reset_WDT_out_register            eeprom_write_byte((uint8_t*)0x3F5, 0xFF);

/************************************************************************************************************************************/
#define setup_328_HW_extra \
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
set_up_activity_leds;\
\
if (POR_detected)\
Reset_WDT_out_register;\
if(WDTout_with_interrupt_detected)\
WDT_out_status = 2;\
else\
{WDT_out_status = 1;}\
Reset_WDT_out_register;\
sei();



//The reset control switch is connected to PC5  USART_init(0,16);


/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")

#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}


#define One_Sec_WDT_with_interrupt \
wdr();\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = (1<< WDE) | (1 << WDIE) |  (1 << WDP2)  |  (1 << WDP1);



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

#define switch_2_up               (PIND & 0x20)


/************************************************************************************************************************************/
#include "Resources_e_power_series\One_wire_header.h"
#include "Resources_e_power_series\One_wire_transactions.c"
#include "Resources_e_power_series\Arduino_IO_and_Timer.c"
#include "Resources_e_power_series\Arduino_Rx_Tx.c"
