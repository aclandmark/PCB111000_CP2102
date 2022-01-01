
/*
User enters floating point numbers at keyboard
They are sent to the 7 segment display and PC
and used for some simple arithmetic  
*/




#include "FPN_project.h"                              //Contains resources used by template and shared with programmer


int main (void){ 
 
float FPN_1, FPN_2;
char op;                                                //+, -, *, /, pow

setup_328_HW;                                           //see "Resources\ATMEGA_Programmer
while(1){
sei();                                                  //Reads switch and changes intensity
User_prompt_template;

if (User_response =='f'){clear_display;
sendString("Enter FPN from KBD \
(terminate in cr)\r\n"); 
FPN_1 =  Float_from_KBD();                              //Sends string to display and returns binary

for(int m = 0; m<=100; m++)                                                  
{if (!m){sendString("\r\nEnter zero to exit \
or +,-,*,/ or ^ followed by new number.\r\n");
sendFloat(FPN_1);sendString("\r\n");}                   //Send number to PC
op = waitforkeypress();
if(op == '0')break;
FPN_2 = Float_from_KBD();

switch (op){                                            //Do some arithmetic
  case '+': FPN_1 = (FPN_1 + FPN_2);break;
  case '-': FPN_1 = (FPN_1 - FPN_2);break;
  case '*': FPN_1 = (FPN_1 * FPN_2);break;
  case '/': FPN_1 = (FPN_1 / FPN_2);break;
  case '^': FPN_1 = pow(FPN_1, FPN_2);break;
  default: break;}

check_for_overflow_underflow(FPN_1);                      //Reset if yes
send_float_num(FPN_1);                                    //Display result
sendFloat(FPN_1);sendString("\r\n");                      //Send result to PC

}}}
return 1;}




/****************************************************************************************/
void check_for_overflow_underflow(float FPN){
unsigned long *long_ptr;
long_ptr = (unsigned long *) &FPN;
if((*long_ptr == 0X0) || (*long_ptr == 0X80000000))
{sendString("Zero\r\n");Reset_ATtiny1606;SW_reset;}
if((*long_ptr == 0x7F800000) || (*long_ptr == 0xFF800000))
{sendString("Infinity\r\n");Reset_ATtiny1606;SW_reset;}}



/****************************************************************************************/
void sendFloat(float FPN){
char expt_string[5];
ftoaL(FPN);
if(sign == '-') sendChar(sign);
if (print_buffer[0] == '.')sendChar('0');
sendString(print_buffer);
if(expt){sendChar('E');
itoa (expt, expt_string, 10 );
sendString(expt_string);}}
