
/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")


#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}
#define LEDs_on  PORTB |= (1 << PB0)|(1 << PB1);



void sendChar(char);
void sendString(const char*);
void UART_Tx_1_wire(void);

volatile char One_wire_mode;




/*************************************************************************************************************/

/*void One_wire_comms(unsigned int PORT_1, unsigned int PORT_2){
One_wire_Tx_char = 'b';  UART_Tx_1_wire();
One_wire_Tx_char = PORT_1;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2;  UART_Tx_1_wire(); 

One_wire_Tx_char = PORT_1 >> 8;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2 >> 8;  UART_Tx_1_wire(); }*/

void One_wire_comms_any_segment(char letter, char digit){
One_wire_Tx_char = 'b';  UART_Tx_1_wire();
One_wire_Tx_char = letter;  UART_Tx_1_wire(); 
One_wire_Tx_char = digit;  UART_Tx_1_wire(); }



/*************************************************************************************************************/
void UART_Tx_1_wire(void){
One_wire_Rx_char = 0;
Tx_complete = 0;
One_wire_mode = 1;									//Tx mode
  
PCMSK0 |= 1 << PCINT4;				       			//set up Interrupt on pin change (IPC)
//sei();												//to detect start pulse and initiate transmision
while(!(Tx_complete));								//Wait here untill transmisson is complete 
//cli();
}





/*************************************************************************************************************/
void UART_Rx_1_wire(void){

One_wire_Rx_char = 0;
Rx_complete = 0;
One_wire_mode = 2;									//Rx mode
   
PCMSK0 |= 1 << PCINT4;		       					//set up IPC to detect start pulse
//sei();												//which intiates reception
while (!(Rx_complete));
//cli();
}




/*************************************************************************************************************/
ISR(PCINT0_vect){                                   //Detect low on PINB4
if(PINB4_down){										//If start bit:

PCMSK0 &= (~(1 << PCINT4));                         //clear IPC

if(One_wire_mode == 1){								//Transmit character
Start_clock;
wait_for_half_comms_tick;							//Used to set the baud rate

PORTB |= (1 << PORTB4);                               //WPU

wait_for_comms_tick;

DDRB |= (1 << DDB4);                                  //OH
wait_for_comms_tick;
 for(int m = 0; m <= 7; m++){                        //Eight data bits
    if (One_wire_Tx_char & (1 << (7-m)))
    PORTB |= (1 << PORTB4);                          //OH
    else PORTB &= ~(1 << PORTB4);                    //OL
   wait_for_comms_tick;}

DDRB &= ~(1 << PINB4);
PORTB &= ~(1 << PORTB4);                             //Restore Tri
Tx_complete = 1;
TCCR0B = 0;}

if(One_wire_mode == 2){								//Receive character
Start_clock;
wait_for_half_comms_tick;

for (int m = 0; m <= 7;m++){
  wait_for_comms_tick;
  
One_wire_Rx_char = One_wire_Rx_char << 1;			//Assemble bits as they are received
if (PINB & (1 << PINB4))
{One_wire_Rx_char |= 1;}}
TCCR0B = 0;
Rx_complete = 1;}}}




/*************************************************************************************************************/
/*ISR(PCINT1_vect){ 									//Interogates vertical switch presses
if(PINC5_down){
_delay_ms(250);										//Switch bounce delay
if(PINC5_up){setRunBL_bit; SW_reset;}
LED_1_on; LED_2_on;
_delay_ms(250);

if(PINC5_up)
{Reset_ATtiny1606;
SW_reset;}
_delay_ms(250);

if(PINC5_down)											//Wait for switch to be released
{One_wire_Tx_char = 'G'; UART_Tx_1_wire();
SW_reset;}}}*/


ISR(PCINT1_vect){ 									//Interogates vertical switch presses
if(PINC5_down){
_delay_ms(25);
if(PINC5_up)return;
_delay_ms(225);										//Switch bounce delay
if(PINC5_up)
{setRunBL_bit; }
else{
//LED_1_on; LED_2_on;
LEDs_on;
_delay_ms(250);
//if(PINC5_up);
if(PINC5_down)											//Wait for switch to be released
{sei();One_wire_Tx_char = 'G'; UART_Tx_1_wire(); }}
SW_reset;}}



