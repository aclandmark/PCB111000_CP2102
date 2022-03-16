

#include "Prime_factors_header.h"

//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


/************************************************************************************************************/





int main (void)  
  { 
    char num_string[12], User_response;
    long  number;
    long factor;
    char factor_counter;
 
 setup_328_HW;
    Serial.begin(115200);
    while (!Serial);
   User_prompt;
 
   Serial.write("Integer number\t");
number = Int_Num_from_PC(num_string, '\r');
factor_counter = 0;
{int  n = 0; int m=0;
do{
factor = Product_search(number);                                   //Get lowest factor
number = number/factor;                                            //Next number to factorise
//Int_Num_to_PC(number,num_string, '\t' );
Int_Num_to_PC(factor,num_string, '\t' );n++;
factor_counter += 1;} 
while (number != 1);  

if(factor_counter == 1){Serial.write("Prime\r");}}
SW_reset;
 return 1;}




long Product_search  (long number)  {
long search_array[200]; 
int j=0;
long n=200;
long L=0;

char test_array[12];

while(1){
for(long k =0; k < n; k++) {search_array[k] = k+1+n*L;}
prime_no_generator(L,n,search_array); 
j=0; while(search_array[j] == 0)j += 1;
while (j<=200){if ((search_array[j] >= 2) &&  (number%search_array[j] == 0)){return search_array[j];}j += 1;}
if(L*200 > number)return 0;
L += 1;Serial.write('.');}}



void prime_no_generator(long L, long n,  long reg[]){
long i, m;
i=2; 
while (i*i < n*(L+1)){
m=0;
while(i*(i+m) <= n*L)m++; 
while(i*(i+m) <= n*(1+L)){reg[i*(i+m) -1 - n*L] = 0; m++; }  
i++;}}














/******************************************************************************************/
long Int_Num_from_PC(char * num_as_string,char next_char)
{char strln;

Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
//if(atol(num_as_string) > 0x7FFF){Serial.write("Number is too large"); SW_reset;}
return atol(num_as_string);}


void Int_Num_to_PC(long Int_num, char * num_as_string, char next_char)
{
ltoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);Serial.print(next_char);
}
