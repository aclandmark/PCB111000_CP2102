

/******************************************************************************************************************************************/
void float_num_to_display(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Check_num_for_to_big_or_small(FP_num);
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                                       //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){ wdr();                                 //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                                 //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;}

reinstate_pin_change_interrupt_on_PC5;}


/******************************************************************************************************************************************/
void Int_num_to_display(long Int_num){
pause_pin_change_interrupt_on_PC5;
One_wire_Tx_char = 'C';                                 //Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){ wdr();                           //Split the number into 4 chars
One_wire_Tx_char = Int_num >> ((3-m) * 8);              //and send them individually
UART_Tx_1_wire(); wdr();
}
reinstate_pin_change_interrupt_on_PC5;}






/******************************************************************************************************************************************/