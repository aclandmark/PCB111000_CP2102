

void UART_Tx_1_wire(void);
void UART_Rx_1_wire(void);
void One_wire_comms_any_segment(char, char);


volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile int One_wire_Rx_int;
volatile char Tx_complete;
char display_bkp[7];

int Comms_clock;


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
	
	

/**********************************************************************************/
#define		reset_ctl_reg			0x3FC
#define 	set_Run_BL_bit			eeprom_write_byte((uint8_t*)reset_ctl_reg, (eeprom_read_byte((uint8_t*)(reset_ctl_reg)) & (~4)));
#define		clear_reset_ctl_reg		eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0)



/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
comms_cal;\
set_up_pin_change_interrupt;\
setup_one_wire_comms;\
set_up_activity_leds;\
clear_reset_ctl_reg;


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



/************************************************************************************************************************************/
#define setup_one_wire_comms 				PORTB &= (~(1 << PORTB4));
#define clear_display 						One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define set_up_pin_change_interrupt  		PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define Reset_ATtiny1606					One_wire_Tx_char = 'F'; UART_Tx_1_wire();



/************************************************************************************************************************************/
#define Start_clock		    	OCR0A = 0; TCNT0 = 0;  TCCR0B = (1 << CS01);


#define PINB4_down			((PINB & 0x10)^0x10)
#define PINC5_down			((PINC & 0x20)^0x20)
#define PINC5_up			(PINC & 0x20)



#define wait_for_comms_tick \
OCR0A +=  Comms_clock;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;


#define wait_for_half_comms_tick \
OCR0A =  Comms_clock/2;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;  


#define  set_up_activity_leds \
DDRB |= (1 << DDB0) | (1 << DDB1);\
LED_1_off;\
LED_2_off;

#define LED_1_off			PORTB &= (~(1 << PB1));
#define LED_1_on			PORTB |= (1 << PB1);

#define LED_2_off			PORTB &= (~(1 << PB0));
#define LED_2_on			PORTB |= (1 << PB0);




