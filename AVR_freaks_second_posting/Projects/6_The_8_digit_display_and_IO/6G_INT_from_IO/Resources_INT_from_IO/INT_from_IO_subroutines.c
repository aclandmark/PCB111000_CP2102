
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




/******************************************************************************************************************************************/
void shift_display_left(void){

if((byte)display_buffer[0] & 0x80)dp_control = 1;                       //No more decimal points allowed
if (display_buffer[0] == 'e')
{exp_control = 1; neg_sign = 0;}                                       //Negative exponent allowed
else neg_sign = 1;                                                      //FP number can have one negative sign 

scroll_control = (exp_control << 2) | (dp_control << 1) | neg_sign;   

shift_digits_left; 
display_buffer[0] = '0'; 
pause_PCI_and_Send_int_num_string;
digit_entry = 1;}




/********************************************************************************************************/
void scroll_display_zero(void){				//Done
unsigned char data_zero;

switch (display_buffer[0]){
case '9': if(!(display_buffer[1])) 
display_buffer[0] = '-'; 
else display_buffer[0] = '0'; break;
case '-': display_buffer[0] = '0'; break;
default: display_buffer[0] += 1;break;}

pause_PCI_and_Send_int_num_string;
return;}










/*************************************************************************************************************/
