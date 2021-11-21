


#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>


void Print_table_headings(void);
void Print_results(int, int, long, long);
char waitforkeypress(void);
char isCharavailable (int);

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
if ((eeprom_read_byte((uint8_t*)0x3FA) > -50)\
&&  (eeprom_read_byte((uint8_t*)0x3FA) < 50) && (eeprom_read_byte((uint8_t*)0x3FA)\
== eeprom_read_byte((uint8_t*)0x3FB)))\
{Comms_clock = 200 + eeprom_read_byte((uint8_t*)0x3FA);}


/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
Comms_clock = 200;\
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




 
