


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();



#define Send_float_num_string \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
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



void Check_num_for_to_big_or_small(float);






/******************************************************************************************************************************************/
void float_num_to_display(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Check_num_for_to_big_or_small(FP_num);
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D'; 								//Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){							//Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;							//and send them individually
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
long Int_KBD_to_display(char display_buffer[]){                       //Acquires an integer string from the keyboard and returns the binary equivalent
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




/********************************************************************************************************************************************/
float Float_KBD_to_display(char display_buffer[]){                              //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char cr_keypress;
float Float_Num_from_UNO = 0;
float * Flt_ptr_local;
char * Char_ptr_local;
char SREG_BKP;

SREG_BKP = SREG;
sei();

Flt_ptr_local = &Float_Num_from_UNO;
Char_ptr_local = (char*)&Float_Num_from_UNO;

cr_keypress = 0;                                                //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=7; n++) display_buffer[n] = 0;              //Clear the buffer used to the string

while(1){
keypress = waitforkeypress();
if ((!(decimal_digit(keypress)))
&& (keypress != '-')
&& (keypress != '.'))continue;                                //Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}

if (keypress == '.')display_buffer[0] = '0' | 0x80;


Send_float_num_string;                                        //Update display with the first key press
while(1){
if ((keypress = wait_for_return_key())  =='\r')break;           //Detect return key press (i.e \r or\r\n)

if ((decimal_digit(keypress)) || (keypress == '.')
|| (keypress == '\b')|| (keypress == '-')
|| (keypress == 'E') || (keypress == 'e'))

{if(keypress == '\b'){for (int n = 0; n <= 7; n++)
display_buffer[n] = display_buffer[n + 1];}

else

{if(keypress != '.')
{for(int n = 7; n>=1; n--)                                    	//Shift display for each new keypress except '.'
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;}                                  //Add new keypress           
else display_buffer[0] |= 0x80;}                				//Intregrate decimal point and its parent digit

Send_float_num_string;}}                                      	//Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                              	//End of string; return key pressed
Send_float_num_string;
cr_keypress = 0;

One_wire_Tx_char = 'E'; UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){
UART_Rx_1_wire(); *Char_ptr_local = One_wire_Rx_char;
Char_ptr_local += 1;}

Float_Num_from_UNO = *Flt_ptr_local;

SREG = SREG_BKP;
return Float_Num_from_UNO;}








