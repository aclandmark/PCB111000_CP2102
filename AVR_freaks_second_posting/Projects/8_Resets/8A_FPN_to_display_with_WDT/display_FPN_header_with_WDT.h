

#include <avr/wdt.h>

char User_response;
char WDT_out_status;

#define T1_delay_250ms 5,0xF85F

/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E

/**********************************************************************************/
#define start_reset_detected              eeprom_read_byte ((uint8_t*)0x3FC) == ~0
#define flaggged__WDTout_detected         (eeprom_read_byte ((uint8_t*)0x3F5) == (byte)~2)
#define Signal_flaggged__WDTout           eeprom_write_byte((uint8_t*)0x3F5, ~2);
#define Reset_WDT_out_register            eeprom_write_byte((uint8_t*)0x3F5, ~0);

#define WDTout_with_interrupt_detected    (eeprom_read_byte((uint8_t*)0x3F5) == (byte)~4)
#define Signal_WDTout_with_interrupt      eeprom_write_byte((uint8_t*)0x3F5, ~4);



/************************************************************************************************************************************/
#define setup_328_HW_Arduino_plus \
\
One_25ms_WDT_with_interrupt;\
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
if (start_reset_detected);\
\
else\
{if(flaggged__WDTout_detected)\
WDT_out_status = 1;\
else if (WDTout_with_interrupt_detected)WDT_out_status = 2; \
else {WDT_out_status = 3;}}\
Reset_WDT_out_register;\
sei();\
Serial.begin(115200);\
while (!Serial);


//The reset control switch is connected to PC5




/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")

#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}


#define One_25ms_WDT_with_interrupt \
wdr();\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = (1<< WDE) | (1 << WDIE) |  (1 << WDP0)  |  (1 << WDP1);


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




/************************************************************************************************************************************/
/************************************************************************************************************************************/
#define set_up_PCI                  PCICR |= (1 << PCIE2);
#define pause_PCI                   PCICR &= (~(1 << PCIE2));
#define reinstate_PCI               PCICR |= (1 << PCIE2);
#define clear_PCI                   PCIFR |= (1<< PCIF2);
#define enable_PCI_on_sw1_and_sw2   PCMSK2 |= (1 << PCINT18) | (1 << PCINT21);
#define enable_PCI_on_sw3           PCMSK2 |= (1 << PCINT23);
#define enable_PCI_on_sw1           PCMSK2 |= (1 << PCINT18);

#define disable_PCI_on_sw3          PCMSK2 &= (~(1 << PCINT23));
#define disable_PCI_on_sw1_and_sw2  PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21)));
#define disable_PCI_on_sw1          PCMSK2 &= (~(1 << PCINT18));

#define switch_1_up               (PIND & 0x04)
#define switch_2_up               (PIND & 0x20)
#define switch_3_up               (PIND & 0x80)
#define switch_1_down             (PIND & 0x04)^0x04
#define switch_2_down             (PIND & 0x20)^0x20
#define switch_3_down             (PIND & 0x80)^0x80

#define newline                   Serial.write("\r\n");



/************************************************************************************************************************************/
#define User_prompt \
while(1){\
do{Serial.write("R?    ");}   while((isCharavailable(75) == 0));\
User_response = Serial.read();\
if((User_response == 'R') || (User_response == 'r'))break;} Serial.write("\r\n");


/************************************************************************************************************************************/
#define waitforkeypress_with_WDT \
while(1){\
if (isCharavailable_with_WDT(8)){\
Serial.read();\
break;}}


/************************************************************************************************************************************/
#include "Resources_display_fpn_with_WDT\One_wire_header.h"
#include "Resources_display_fpn_with_WDT\One_wire_transactions_WDT.c"
#include "Resources_display_fpn_with_WDT\Arduino_IO_and_Timer_WDT.c"
//#include "Resources_display_fpn_with_WDT\Arduino_Rx_Tx.c"
#include "Resources_display_fpn_with_WDT\display_driver_subroutines_KBD_WDT.c"




/***************************************************************************************************************************************/
