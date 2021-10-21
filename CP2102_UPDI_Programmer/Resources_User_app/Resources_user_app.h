

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile char Tx_complete, Rx_complete;
char display_bkp[7];


#define set_up_pin_change_interrupt  		PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define set_up_one_way_comms 				PCICR |= (1 << PCIE0); PORTB &= (~(1 << PORTB4));  
#define Reset_ATtiny1606					One_wire_Tx_char = 'F'; UART_Tx_1_wire();


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










