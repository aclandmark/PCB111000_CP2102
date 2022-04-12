
/**************Proj_5D_Acquire_and process_Data_from_the _KBD********************/

/*
Here we leave the mini_OS (the Attiny1606) to deal with all the details of displaying a number.
We can use one_wire_comms to send it a string or binary number.
If we send it a string then it will return the number in binary form.

Obviouly Arduino do not supply library functions to drive the display and therefore a
bit of DIY programming is required.
*/



#include "display_int_header.h"


int main (void){
float Num_1;
char digits[12];
//int counter = 0;

setup_328_HW;
Serial.begin(115200);
while (!Serial);

Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");


Num_1 = Float_KBD_to_display_Local(digits);                                     //Data from keyboard
while (1){
Sc_Num_to_PC(Num_1,1,5 ,'\r');
waitforkeypress();
Num_1 = pow(Num_1, 0.8);
float_num_to_display(Num_1);                                                    //Sends number to the display
}                                                                                 //Do some arithmetic

SW_reset;}



/********************************************************************************************************************************************/
float Float_KBD_to_display_Local(char display_buffer[]){                              //Acquires an integer string from the keyboard and returns the binary equivalent
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
{for(int n = 7; n>=1; n--)                                    //Shift display for each new keypress except '.'
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;}                                  //Add new keypress           
else display_buffer[0] |= 0x80;}                //Intregrate decimal point and its parent digit

Send_float_num_string;}}                                      //Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                              //End of string; return key pressed
Send_float_num_string;
cr_keypress = 0;

One_wire_Tx_char = 'E'; UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){
UART_Rx_1_wire(); *Char_ptr_local = One_wire_Rx_char;
Char_ptr_local += 1;}

Float_Num_from_UNO = *Flt_ptr_local;



SREG = SREG_BKP;
return Float_Num_from_UNO;}





/*************************************************************************************************************************/
void Sc_Num_to_PC(float num, char pre_dp, char post_dp, char next_char)
{int A = 1;
char keypresses[12];
char sign = '+';
int Exp = 0;

Check_num_for_to_big_or_small(num);

if (num < 0){sign = '-'; num = num * (-1);}

while(--pre_dp){A = A*10;}
while (num >= A){num = num/10.0; Exp += 1;}
while (num <= A){num = num*10.0; Exp -= 1;}

if(sign == '-')num = num * (-1);

Serial.print(num, post_dp);
if(Exp) {Serial.write ('E'); Serial.print(Exp);}
Serial.write(next_char);}




/*****************************************************************************************/
void Check_num_for_to_big_or_small(float num)
{unsigned long * long_ptr;
long_ptr = (unsigned long *)&num;
if (*long_ptr == 0x7F800000){Serial.write("+ve Num too large\r\n");SW_reset;}
if (*long_ptr == 0xFF800000){Serial.write("-ve Num too large\r\n");SW_reset;}
if (*long_ptr == 0X0){Serial.write("+ve Num too small\r\n");SW_reset;}
if (*long_ptr == 0X80000000){Serial.write("-ve Num too small\r\n");SW_reset;}}
