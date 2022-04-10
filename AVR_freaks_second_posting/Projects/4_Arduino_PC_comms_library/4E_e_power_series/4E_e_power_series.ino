
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
See https://en.wikipedia.org/wiki/Natural_logarithm
for an efficient way to calculate a natural log of any number
 
 */



int main (void) 

{
char Num_string[12];
char numLength;

float logN;
float Num,   Pow;
int twos_exp;
float Result;
char sign;

setup_328_HW;
Serial.begin(115200);
while (!Serial);


Serial.write("\r\nPower function: Enter number 1 to 2\r\n");
Num = Sc_Num_from_PC(Num_string, '\t');


sign = 0;
if (Num >= 1.0)
{twos_exp = 0; while (Num >= 2.0){Num = Num/2.0; twos_exp += 1;}}

if (Num < 1.0)
{twos_exp = 0; while (Num < 1.0){Num = Num*2.0; twos_exp -= 1;}}

Sc_Num_to_PC(Num, 1, 6, '\t'); Int_Num_to_PC(twos_exp, Num_string, '\r');



Reset_ATtiny1606;
logN = logE_power_series(Num) + ((float)twos_exp * 0.693147);

Serial.write("Natural log is  "); Sc_Num_to_PC(logN,1,5,'\r');


Serial.write("Enter power  ");
Pow = Sc_Num_from_PC(Num_string, '\t');

Num = logN * Pow;                           //Use Num to hold the log of the result

Result = expE_power_series(Num);

display_float_num(Result);
Sc_Num_to_PC(Result,1,5,'\r');


SW_reset;
return 1; }




/**************************************************************************************************************************/
float expE_power_series(float Num)
{float term;                                           //Power series terms
float difference;
float ans, ans_old;
long term_counter;
char sign = 0;

if (Num < 0){sign = 1; Num = Num * (-1);}

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

if(!(sign))return ans;
else return 1.0/ans;
}





/**************************************************************************************************************************/
float logE_power_series(float Num)
{float logE, logE_old;                                 //logs are calculated iteratively
float term;                                           //Power series terms
float difference;                                     //difference berween consequtive terms


Num -= 1;
if (Num > 0.9999){logE = 6.9315E-1;}
else if (Num < 0.00001){logE = 1E-6;}
else                                                  //Use power series to calculate the natural logarithm
{
int m = 1;
term = 1.0;
while(1){
term = term * Num/(float)m;
if (m == 1){logE = term; difference= logE;}
else{
  if (m%2)logE += term;
  else logE -= term;
  difference = logE - logE_old;}

if ((difference/logE > -0.0000001) && (difference/logE < 0.0000001))break; 
  
logE_old = logE;
term = term * (float)m;
if ((m += 1) > 5000)break; }}
return logE;}






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
