
#include "e_power_series_header.h"

/*
 Raises number Num to a power Pow
 Num must be between 1 and 2
 A power series calculates the natural log of Num
 The log is then multiplied by Pow
 The power series expansion of the exponential function
 is used to obtain the final result (i.e the antilog)
See https://en.wikipedia.org/wiki/Exponential_function
and https://en.wikipedia.org/wiki/Natural_logarithm
for the power series deffinitions
 
 */

int main (void) 

{
char Num_string[12];
char numLength;

float logN, logN_old;                                 //logs are calculated iteratively
float ans, ans_old;                                   //Final result
float Num,   Pow;
float term;                                           //Power series terms
float difference;                                     //difference berween consequtive terms
long term_counter;

int loop_counter;


setup_328_HW;
Serial.begin(115200);
while (!Serial);

Serial.write("\r\nPower function: Enter number 1 to 2\r\n");
Num = Sc_Num_from_PC(Num_string, '\t');
Num -= 1;

Reset_ATtiny1606;

if (Num > 0.9999){logN = 6.9315E-1;}
else if (Num < 0.00001){logN = 1E-6;}
/****************Use power series to calculate the natural logarithm*********************************************/
else 
{
int m = 1;
term = 1.0;
while(1){
term = term * Num/(float)m;
if (m == 1){logN = term; difference= logN;}
else{
  if (m%2)logN += term;
  else logN -= term;
  difference = logN - logN_old;}

if ((difference/logN > -0.0000001) && (difference/logN < 0.0000001))break; 
  
logN_old = logN;
term = term * (float)m;
if ((m += 1) > 5000)break; }}


Serial.write("Natural log is  ");
Sc_Num_to_PC(logN,1,5,'\r');

//Int_Num_to_PC(test, Num_string, '\r');

Serial.write("Enter power  ");
Pow = Sc_Num_from_PC(Num_string, '\t');

Num = logN * Pow;

term = 1.0;
term_counter = 1;
ans = 1.0;
ans_old = 1.0;

while(1){
term = (term * Num)/float(term_counter);  term_counter += 1;
ans += term;
difference = ans - ans_old;
if ((difference/ans > -0.0000001) && (difference/ans < 0.0000001))break;
ans_old = ans;}
display_float_num(ans);
Sc_Num_to_PC(ans,1,5,'\r');

/************************Calculate 4*Area/R^2****************************/
SW_reset;
return 1; }






/**************************************************************************************************************************/
void display_float_num(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                               //Command 'D' indicates that a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){                          //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                         //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;}
reinstate_pin_change_interrupt_on_PC5;}
