



void One_wire_comms_3_bytes(char *  Char_array){
  pause_pin_change_interrupt_on_PC5; 
One_wire_Tx_char = 'H';  UART_Tx_1_wire(); 
One_wire_Tx_char = Char_array[0];  UART_Tx_1_wire(); 
One_wire_Tx_char = Char_array[1];  UART_Tx_1_wire(); 
One_wire_Tx_char = Char_array[2];  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt_on_PC5;}


/*****************************************************************/
unsigned char PRN_8bit_GEN(unsigned char lfsr){
unsigned int bit;

bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 4)) & 1;
lfsr = (lfsr >> 1) | (bit << 7);
return lfsr;}
