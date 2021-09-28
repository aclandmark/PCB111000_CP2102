

void UART_Tx_1_wire(void);
void UART_Rx_1_wire(void);
void I2C_Tx_any_segment(char, char);

void backup_the_display(char, char);
unsigned int PRN_16bit_GEN(unsigned int);

char User_response;

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile int One_wire_Rx_int;
volatile char Tx_complete, Rx_complete;

volatile char One_wire_mode;

char display_bkp[7];






/************************************************************************************************************************************/
#define setup_328_HW \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
\
USART_init(0,16);\
setup_one_wire_comms;\
Reset_ATtiny1606;



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
#define User_prompt_proj_2C1 \
while(1){\
do{sendString("r    ");}	 while((isCharavailable(120) == 0));\
User_response = receiveChar();\
if(User_response == 'r') break;} sendString("\r\n");




/************************************************************************************************************************************/
#define setup_one_wire_comms \
PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT11);\
PORTC &= (~(1 << PORTC4));

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


#define PINC4_down  ((PINC & 0x10)^0x10)
#define PINC3_down  ((PINC & 0x08)^0x08)







