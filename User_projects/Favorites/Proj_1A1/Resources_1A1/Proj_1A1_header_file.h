

void UART_Tx_1_wire(void);
void UART_Rx_1_wire(void);
void One_wire_Tx_2_integers(unsigned int, unsigned int);

char User_response;

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile int One_wire_Rx_int;
volatile char Tx_complete, Rx_complete;

volatile char One_wire_mode;






/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
set_up_pin_change_interrupt;\
USART_init(0,16);\
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


/************************************************************************************************************************************/
#define User_prompt_proj_1A1 \
while(1){\
do{sendString("r    ");}	 while((isCharavailable(40) == 0));\
User_response = receiveChar();\
if(User_response == 'r') break;} sendString("\r\n");




/************************************************************************************************************************************/
#define setup_one_wire_comms \
PCICR |= (1 << PCIE0); PCMSK0 |= (1 << PCINT4);\
PORTB &= (~(1 << PORTB4));

//#define pause_comms		PCICR &= (~(1 << PCIE0)); PCMSK0 &= (~(1 << PCINT4));
//#define resume_comms	PCICR |= (1 << PCIE0); PCMSK0 |= (1 << PCINT4);

#define clear_display 						One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define set_up_pin_change_interrupt  		PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define pause_pin_change_interrupt  		PCICR &= (~(1 << PCIE1)); 
#define reinstate_pin_change_interrupt  	PCICR |= (1 << PCIE1); 

#define Reset_ATtiny1606 \
One_wire_Tx_char = 'F'; UART_Tx_1_wire();





/************************************************************************************************************************************/
#define Tx_clock_1     		200			//5K Baud rate	
#define Rx_clock_1     		200		
#define Start_clock_1    	TCNT0 = 0;  TCCR0B = (1 << CS01);
#define Half_Rx_clock_1 	100


#define wait_for_comms_tick \
OCR0A +=  Rx_clock_1;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;


#define wait_for_half_comms_tick \
OCR0A =  Half_Rx_clock_1;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;  


#define setRunBL_bit				eeprom_write_byte((uint8_t*)0x3FC, (eeprom_read_byte((uint8_t*)(0x3FC)) & (~2)));
#define PINB4_down	((PINB & 0x10)^0x10)
#define PINC5_down	((PINC & 0x20)^0x20)
#define PINC5_up	(PINC & 0x20)


#define  set_up_activity_leds \
DDRB |= (1 << DDB0) | (1 << DDB1);\
LED_1_off;\
LED_2_off;

#define LED_1_off	 PORTB &= (~(1 << PB1));
#define LED_1_on	 PORTB |= (1 << PB1);

#define LED_2_off	 PORTB &= (~(1 << PB0));
#define LED_2_on	 PORTB |= (1 << PB0);




