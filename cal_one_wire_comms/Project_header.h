


#include <avr/wdt.h>
#include "cal_one_wire_Resources/ASKII_subroutines.c"

void Print_table_headings(void);
void Print_results(int, int, long, long);
char waitforkeypress(void);
char isCharavailable (int);
int Int_from_KBD(void);


char User_response;
char keypress;

long ATtiny1606_period;                             //Time between ATtiny comms start pulses  (nominally 18mS)
int Atmega_328_period;                              //Equivalent period for the Atmega        (90 0.2mS time slots)
long error;                                         //Difference between the two periods
long error_percent;                                 //Error as a percentage

int Comms_clock;                                    //Determines Atmega comms baud rate       (nominally 200uS)
int Comms_clock_correction;                         //Matches Atmega and ATtiny baud rates
int User_correction_factor;                         //Value chosen by user



/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}


/**********************************************************************************/
#define  comms_cal \
if (((signed char)eeprom_read_byte((uint8_t*)0x3F6) > -50)\
&&  ((signed char)eeprom_read_byte((uint8_t*)0x3F6) < 50) && ((signed char)eeprom_read_byte((uint8_t*)0x3F6)\
== (signed char)eeprom_read_byte((uint8_t*)0x3F7)))\
{Comms_clock = 200 + (signed char) eeprom_read_byte((uint8_t*)0x3F6);}


/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
Comms_clock = 200;\
set_up_pin_change_interrupt;\
set_up_activity_leds;\
Serial.begin(76800);\
while (!Serial);\
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

//Sets all IO to week pull up

/************************************************************************************************************************************/
#define User_prompt \
while(1){\
do{Serial.write("r    ");}   while((isCharavailable(40) == 0));\
User_response = Serial.read();\
if(User_response == 'r') break;} Serial.write("\r\n");



/************************************************************************************************************************************/
# define measure_1606_mux_period \
TCNT1 = 0;\
while (!(PINB & (1 << PINB4)));\
while (PINB & (1 << PINB4));\
TCCR1B |= (1 << CS11);\
while (!(PINB & (1 << PINB4)));\
while (PINB & (1 << PINB4));\
TCCR1B &= (~(1 << CS11));


/*waits for high to low transition
 * Starts counter with 1MHz clocks
 * waits for next high to low transition
 * Stops counter and records the value of TCNT1
 */


/************************************************************************************************************************************/
#define set_up_pin_change_interrupt      PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define pause_pin_change_interrupt      PCICR &= (~(1 << PCIE1)); 
#define reinstate_pin_change_interrupt    PCICR |= (1 << PCIE1); 



#define setRunBL_bit        eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~2)));
#define PINB4_down  ((PINB & 0x10)^0x10)
#define PINC5_down  ((PINC & 0x20)^0x20)
#define PINC5_up  (PINC & 0x20)


#define  set_up_activity_leds \
DDRB |= (1 << DDB0) | (1 << DDB1);\
LED_1_off;\
LED_2_off;

#define LED_1_off   PORTB &= (~(1 << PB1));
#define LED_1_on   PORTB |= (1 << PB1);

#define LED_2_off  PORTB &= (~(1 << PB0));
#define LED_2_on   PORTB |= (1 << PB0);



 
