


/*********************************************************************/
#define shift_digits_left {for (int n = 0; n < 7; n++){display_buffer[7-n] = display_buffer[6-n];}}


#define Float_num_string_to_display \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define Int_num_string_to_display \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();




#define initialise_display \
clear_display_buffer;\
display_buffer[0] = '0';\
pause_PCI_and_Send_int_num_string;



#define Int_from_mini_OS \
S_reg_bkp = SREG; sei();\
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){\
Long_Num_from_mini_OS = Long_Num_from_mini_OS << 8;\
Long_Num_from_mini_OS |= num_byte[m];}\
SREG = S_reg_bkp;




#define f_number_from_mini_OS \
S_reg_bkp = SREG; sei();\
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); *Char_ptr = One_wire_Rx_char;\
Char_ptr += 1;}\
f_number = *Flt_ptr;\
SREG = S_reg_bkp;



void float_num_to_display(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                                       //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){                                  //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                                 //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;}
reinstate_pin_change_interrupt_on_PC5;}


/******************************************************************************************************************************************/
void int_num_to_display(long Int_num){
pause_pin_change_interrupt_on_PC5;

One_wire_Tx_char = 'C';                                 //Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){                            //Split the number into 4 chars
One_wire_Tx_char = Int_num >> ((3-m) * 8);              //and send them individually
UART_Tx_1_wire(); 
}
reinstate_pin_change_interrupt_on_PC5;}


