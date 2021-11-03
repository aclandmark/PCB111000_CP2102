

void comms_transaction(void);
void rst_cntr(void);


/*************************************************************************************************************/
void UART_Tx_1_wire(void){

Tx_complete = 0;
One_wire_mode = 1;											//Tx mode

while(PINB4_down);											//Detect edge not level
while (!(PINB4_down));
comms_transaction();
while(!(Tx_complete));										//Wait here until transmission is complete

if((PINC5_down) && (One_wire_Tx_char != 'G'))rst_cntr();}	//Respond to vertical switch press



/*************************************************************************************************************/
void UART_Rx_1_wire(void){									//Untested in interrupt free mode
One_wire_Rx_char = 0;
Rx_complete = 0;
One_wire_mode = 2;											//Rx mode

while(PINB4_down);
while (!(PINB4_down));
comms_transaction();
while (!(Rx_complete));}



/*************************************************************************************************************/
void comms_transaction(void){                               //Detect low on PINC4

	if(One_wire_mode == 1){									//Transmit character
		Start_clock_1;
		wait_for_half_comms_tick;							//Used to set the baud rate

		PORTB |= (1 << PORTB4);								//WPU

		wait_for_comms_tick;

		DDRB |= (1 << DDB4);								//OH
		wait_for_comms_tick;
		for(int m = 0; m <= 7; m++){						//Eight data bits
			if (One_wire_Tx_char & (1 << (7-m)))
			PORTB |= (1 << PORTB4);							//OH
			else PORTB &= ~(1 << PORTB4);					//OL
		wait_for_comms_tick;}
		DDRB &= ~(1 << PINB4);
		PORTB &= ~(1 << PORTB4);							//Restore Tri-state
		Tx_complete = 1;
	TCCR0B = 0;}

	if(One_wire_mode == 2){									//Receive character
		Start_clock_1;
		wait_for_half_comms_tick;

		for (int m = 0; m <= 7;m++){
			wait_for_comms_tick;
			
			One_wire_Rx_char = One_wire_Rx_char << 1;		//Assemble bits as they are received
			if (PINB & (1 << PINB4))
			{One_wire_Rx_char |= 1;}}
			TCCR0B = 0;
		Rx_complete = 1;}}
	
	
	
	
/*************************************************************************************************************/
void rst_cntr(void){ 										//Interrogates vertical switch presses

	_delay_ms(25);											//Switch bounce delay
	if(PINC5_up)return;
	_delay_ms(225);
	if(PINC5_up)
	{setRunBL_bit;}
	else{
		LED_1_on; LED_2_on;
		_delay_ms(500);
		if((PINC5_down))								//Wait for switch to be released
		{One_wire_Tx_char = 'G'; UART_Tx_1_wire(); 
		while(PINC5_down);}
	}
	SW_reset;}






