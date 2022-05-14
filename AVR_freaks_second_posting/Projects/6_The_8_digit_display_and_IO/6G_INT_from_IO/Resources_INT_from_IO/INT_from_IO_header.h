


/*********************************************************************/
#define shift_digits_left {for (int n = 0; n < 7; n++){display_buffer[7-n] = display_buffer[6-n];}}


#define Send_float_num_string \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define pause_PCI_and_Send_int_num_string \
pause_PCI;sei();Send_int_num_string;cli();reinstate_PCI;


#define initialise_display \
clear_display_buffer;\
display_buffer[0] = '0';\
pause_PCI_and_Send_int_num_string;\
sei();


#define f_number_from_mini_OS \
sei();One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); *Char_ptr = One_wire_Rx_char;\
Char_ptr += 1;}\
f_number = *Flt_ptr;





#define Int_from_mini_OS \
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){\
Long_Num_from_mini_OS = Long_Num_from_mini_OS << 8;\
Long_Num_from_mini_OS |= num_byte[m];}





