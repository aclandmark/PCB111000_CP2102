

void UART_Tx_1_wire(void);
void UART_Rx_1_wire(void);
void One_wire_Tx_2_integers(unsigned int, unsigned int);

char User_response;

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile int One_wire_Rx_int;
volatile char Tx_complete, Rx_complete;

volatile char One_wire_mode;

long Long_Num_from_UNO = 0;
char display_buffer[12], buffptr = 0;
volatile char cr_keypress;
unsigned char num_byte[4];


int Comms_clock;

char print_buffer[15];
char sign;
signed char expt;
char expt_string[5];


#define clear_print_buffer		for(int m = 0; m<=14; m++)print_buffer[m] = 0;

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
\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
comms_cal;\
set_up_pin_change_interrupt;\
USART_init(0,16);\
setup_one_wire_comms;\
set_up_activity_leds;\
\
if(!(eeprom_read_byte((uint8_t*) 0x3F1)))\
{eeprom_write_byte((uint8_t*)(0x3F1), 0xFF);\
sendString("Zero");}\
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

#define clear_display 						One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define set_up_pin_change_interrupt  		PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define pause_pin_change_interrupt  		PCICR &= (~(1 << PCIE1)); 
#define reinstate_pin_change_interrupt  	PCICR |= (1 << PCIE1); 

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


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define Send_float_num_string \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();



#define User_prompt_template \
while(1){\
do{sendString("f?  ");}	 while((isCharavailable(100) == 0));\
User_response = receiveChar();\
if((User_response == 'f') || (User_response == 'i'))break;} sendString("\r\n");

