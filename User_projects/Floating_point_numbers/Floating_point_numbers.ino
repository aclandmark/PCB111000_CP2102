
#include "FPN_project.h"                              //Contains resources used by template and shared with programmer



int main (void){ 
  
char keypress;
long int_num;
float FPN_1, FPN_2;
char FP_string[12];
char op;                                                //+, -, *, /, pow

setup_328_HW;                                           //see "Resources\ATMEGA_Programmer


while(1){

sei();                                                    //Required to control intensity
  
User_prompt_template;

if (User_response =='i')

/*{sendString("Enter integer from KBD (terminate in cr)\r\n");

while (int_num = Int_from_KBD()){
sendString("AK to do arithmetic\r\n");
waitforkeypress();
Long_Num_to_UNO = Long_Num_from_UNO * 2;                //Simple arithmetic to check operation of binary/string conversions
send_int_num(Long_Num_to_UNO);
sendString("New number?\r\n");}}*/


{while(1){
int_num = 10;
while(int_num < 99999999){
send_int_num(int_num);
  _delay_ms(10); 
  //waitforkeypress(); 
  int_num = int_num*10/9;}}}


if (User_response =='f'){
 sendString("Enter FPN from KBD (terminate in cr)\r\n"); 
 FPN_1 =  Float_from_KBD();
 for(int m = 0; m<=100; m++)                                                  
  {if (!m)sendString("\r\nEnter zero to exit \
or +,-,*,/ or ^ followed by new number.\r\n");

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

send_float_num(FPN_1);
sei();                                                  //Required for intensity control
}}}


SW_reset;
return 1;}


 
