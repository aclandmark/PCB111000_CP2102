
char User_response;



/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}



/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
Set_LED_ports;\
LEDs_off;\
\
USART_init(0,68);



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
PORTD = 0xFF;\
Prog_Port &= (~(1 << Prog_pin));

//Prog pin stays as Hi Z input

/************************************************************************************************************************************/
#define Set_LED_ports 	DDRB = (1 << DDB0) | (1 << DDB1);
#define LED_1_on  	PORTB |= (1 << PB0);
#define LED_2_on  	PORTB |= (1 << PB1);
#define toggle_led_2	PORTB ^= (1 << PB1);
#define LEDs_off  	PORTB &= (~((1 << PB0)|(1 << PB1)));


