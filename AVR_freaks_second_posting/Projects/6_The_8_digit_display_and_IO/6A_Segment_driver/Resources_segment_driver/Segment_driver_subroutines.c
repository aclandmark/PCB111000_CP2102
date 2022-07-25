





/************************************************************************************************************************************************/
void One_wire_comms_any_segment(char letter, char digit_num){
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'b';			UART_Tx_1_wire(); wdr();
One_wire_Tx_char = letter;		UART_Tx_1_wire(); wdr();
One_wire_Tx_char = digit_num;	UART_Tx_1_wire(); wdr();
reinstate_pin_change_interrupt_on_PC5;}





