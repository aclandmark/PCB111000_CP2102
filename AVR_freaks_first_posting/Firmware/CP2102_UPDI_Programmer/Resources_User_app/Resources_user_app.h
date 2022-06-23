

volatile char One_wire_Rx_char, One_wire_Tx_char;
volatile char Tx_complete, Rx_complete;
char display_bkp[7];

int Comms_clock;

/**********************************************************************************/
#define  comms_cal \
if (((signed char)eeprom_read_byte((uint8_t*)0x3F6) > -50)\
&&  ((signed char)eeprom_read_byte((uint8_t*)0x3F6) < 50) && ((signed char)eeprom_read_byte((uint8_t*)0x3F6)\
== (signed char)eeprom_read_byte((uint8_t*)0x3F7)))\
{Comms_clock = 200 + (signed char) eeprom_read_byte((uint8_t*)0x3F6);}


#define set_up_pin_change_interrupt  		PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT13); 
#define set_up_one_wire_comms 				PCICR |= (1 << PCIE0); PORTB &= (~(1 << PORTB4));  
#define Reset_ATtiny1606					One_wire_Tx_char = 'F'; UART_Tx_1_wire();


#define Start_clock		    	TCNT0 = 0;  OCR0A = 0; TCCR0B = (1 << CS01);


#define wait_for_comms_tick \
OCR0A +=  Comms_clock;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;

#define wait_for_half_comms_tick \
OCR0A =  Comms_clock/2;\
while (!(TIFR0 & (1 << OCF0A)));\
TIFR0 = 0xFF;  

#define 	reset_ctl_reg			0x3FC
#define 	set_Run_BL_bit			eeprom_write_byte((uint8_t*)reset_ctl_reg, (eeprom_read_byte((uint8_t*)(reset_ctl_reg)) & (~4)));

#define PINB4_down	((PINB & 0x10)^0x10)
#define PINC5_down	((PINC & 0x20)^0x20)
#define PINC5_up	(PINC & 0x20)






