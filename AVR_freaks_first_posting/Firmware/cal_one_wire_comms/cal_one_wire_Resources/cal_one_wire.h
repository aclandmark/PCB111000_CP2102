

void One_wire_Tx_2_integers(unsigned int, unsigned int);
void Print_table_headings(void);
void Print_results(int, int, long, long);
char waitforkeypress(void);
char isCharavailable (int);
int Int_from_KBD(void);
char wait_for_return_key(void);
char decimal_digit (char);


char User_response;
char keypress;

long ATtiny1606_period;                             //Time between ATtiny comms start pulses  (nominally 18mS)
int Atmega_328_period;                              //Equivalent period for the Atmega        (90 0.2mS time slots)
long error;                                         //Difference between the two periods
long error_percent;                                 //Error as a percentage

int Comms_clock;                                    //Determines Atmega comms baud rate       (nominally 200uS)
int Comms_clock_correction;                         //Matches Atmega and ATtiny baud rates
int User_correction_factor;                         //Value chosen by user
int User_correction_factor_previous;

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile char Tx_complete, Rx_complete;

volatile char One_wire_mode;





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
comms_cal;\
set_up_pin_change_interrupt;\
Serial.begin(115200);\
while (!Serial);\
setup_one_wire_comms;\
set_up_activity_leds;\
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
if((User_response == 'r') || (User_response == 'R'))break;} Serial.write("\r\n");


/************************************************************************************************************************************/

#define setup_one_wire_comms \
PCICR |= (1 << PCIE0); PCMSK0 |= (1 << PCINT4);\
PORTB &= (~(1 << PORTB4));


#define clear_display 						One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define set_up_pin_change_interrupt      PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define pause_pin_change_interrupt      PCICR &= (~(1 << PCIE1)); 
#define reinstate_pin_change_interrupt    PCICR |= (1 << PCIE1); 

#define Reset_ATtiny1606 \
One_wire_Tx_char = 'F'; UART_Tx_1_wire();



/************************************************************************************************************************************/
#define Start_clock		    	TCNT0 = 0;  OCR0A = 0; TCCR0B = (1 << CS01);

#define wait_for_comms_tick \
OCR0A +=  Comms_clock;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;


#define wait_for_half_comms_tick \
OCR0A =  Comms_clock/2;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;  

#define boot_reset_ctl_reg			0x3FC
#define 	set_Run_BL_bit			eeprom_write_byte((uint8_t*)boot_reset_ctl_reg, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~4)));

//#define setRunBL_bit        eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~2)));
#define PINB4_down  ((PINB & 0x10)^0x10)
#define PINC5_down  ((PINC & 0x20)^0x20)
#define PINC5_up  (PINC & 0x20)


/************************************************************************************************************************************/
#define  set_up_activity_leds \
DDRB |= (1 << DDB0) | (1 << DDB1);\
LED_1_off;\
LED_2_off;

#define LED_1_off   PORTB &= (~(1 << PB1));
#define LED_1_on   PORTB |= (1 << PB1);

#define LED_2_off  PORTB &= (~(1 << PB0));
#define LED_2_on   PORTB |= (1 << PB0);


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
 