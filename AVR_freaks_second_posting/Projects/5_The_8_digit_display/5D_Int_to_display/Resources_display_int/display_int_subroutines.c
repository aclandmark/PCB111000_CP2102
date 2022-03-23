


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();



#define Int_from_mini_OS \
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){\
Long_Num_from_mini_OS = Long_Num_from_mini_OS << 8;\
Long_Num_from_mini_OS |= num_byte[m];}




void int_num_to_display(long);




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
long Int_from_KBD(char display_buffer[]){                       //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
long Long_Num_from_mini_OS;
char cr_keypress;
unsigned char num_byte[4];

cr_keypress = 0;                                            	//Set to one when carriage return keypress terminates the string
for(int n = 0; n<=8; n++) display_buffer[n] = 0;           		//Clear the buffer used for the string

while(1){
keypress = waitforkeypress();
if ((!(decimal_digit(keypress)))
&& (keypress != '-'))continue;                            		//Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}
 
Send_int_num_string;
while(1){
if ((keypress = wait_for_return_key())  =='\r')break;        	//Detect return key press (i.e \r or\r\n)
if ((decimal_digit(keypress)) || (keypress == '\b')\
 || (keypress == '-'))

{if (keypress == '\b'){                         				//Backspace key
for (int n = 0; n <= 7; n++)
display_buffer[n] = display_buffer[n + 1];}
else
{for(int n = 8; n>=1; n--)                                    	//Shift display for each new keypress
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;  }                             	//Add new keypress           

Send_int_num_string;}}                                      	//Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                            	//End of string; return key press detected

Send_int_num_string;
cr_keypress = 0;

One_wire_Tx_char = 'E'; UART_Tx_1_wire();						//Command ATtiny1606:  Waiting to receive number in binary form							
for(int m = 0; m <= 3; m++){
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}

for(int m = 0; m <= 3; m++){									//Recover number as 4 bytes and re-assemble them
Long_Num_from_mini_OS = Long_Num_from_mini_OS << 8;
Long_Num_from_mini_OS |= num_byte[m];}

return Long_Num_from_mini_OS;}