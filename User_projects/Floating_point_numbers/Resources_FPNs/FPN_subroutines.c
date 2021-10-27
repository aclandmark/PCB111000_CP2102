



/*************************************************************************************************************/
void send_int_num(long num){
pause_pin_change_interrupt; 
One_wire_Tx_char = 'C'; 								//Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){
One_wire_Tx_char = num >> (8 * (3 - m)); 				//Split the number into 4 chars
UART_Tx_1_wire();}
reinstate_pin_change_interrupt;}										//and send them individually




/*************************************************************************************************************/
void send_float_num(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt;

Char_ptr = (char*)&FP_num;
	
One_wire_Tx_char = 'D'; 								//Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){							//Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;							//and send them individually
UART_Tx_1_wire();	
Char_ptr += 1;}
reinstate_pin_change_interrupt;}

	
