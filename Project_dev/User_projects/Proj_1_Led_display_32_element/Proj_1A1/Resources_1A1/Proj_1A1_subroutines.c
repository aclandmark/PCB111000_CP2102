




void One_wire_Tx_2_integers(unsigned int PORT_1, unsigned int PORT_2){
pause_pin_change_interrupt;
One_wire_Tx_char = 'a';  UART_Tx_1_wire();
One_wire_Tx_char = PORT_1;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2;  UART_Tx_1_wire(); 

One_wire_Tx_char = PORT_1 >> 8;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2 >> 8;  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt;}