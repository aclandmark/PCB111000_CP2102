
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
pause_PCI_and_Send_float_num_string;
digit_entry = 1;}




/********************************************************************************************************/
void scroll_display_zero(void){
unsigned char data_zero;

disable_PCI_on_sw3;

data_zero = display_buffer[0];

if (switch_3_up){display_buffer[0] &= (~(0x80));             //Decimal point dissabled

switch (display_buffer[0]){
case '9':
switch(scroll_control){ 
case 0: display_buffer[0] = '-'; break;                    //Initial state scroll 0-9 -ve 0...... dp is enabled
case 1: display_buffer[0] = '0'; break;                    //First char entered -ve sign dissabled  dp enabled
case 3: display_buffer[0] = 'e'; break;                    //Decimal point entered.  Dissable DP. Enable E.
case 6: display_buffer[0] = '-'; break;                    //E entered. Enable -ve sign
case 7: display_buffer[0] = '0'; break;}break;              //Dissable -ve sign

case '-':
switch(scroll_control){
case 0: display_buffer[0] = '0'; break;                    //Initial state
case 6: display_buffer[0] = '0'; break;}break;

case 'e':
switch(scroll_control){
case 0: display_buffer[0] = '0'; break;                       //Initial state
case 1: display_buffer[0] = '0'; break;    
case 3: display_buffer[0] = '0'; break;}break;

default: display_buffer[0] += 1; break;}}

if((switch_3_down) && (!(dp_control)))
{display_buffer[0] |= 0x80;                                   //Decimal point enabled 

switch ((byte)display_buffer[0] & (~(0x80))){
case '9': 
display_buffer[0] = ('0' | 0x80);break;
default:  display_buffer[0] += 1;break;}}

pause_PCI_and_Send_float_num_string;}




/*************************************************************************************************************/
