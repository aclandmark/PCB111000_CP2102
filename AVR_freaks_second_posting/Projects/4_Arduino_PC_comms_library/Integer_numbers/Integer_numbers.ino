

#include "Integer_numbers_header.h"

//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


/************************************************************************************************************/





int main (void)  
  { 
    char num_string[12], User_response;
    int  num;
    int m = 1;
 
 setup_328_HW;
    Serial.begin(115200);
    while (!Serial);
   User_prompt;
 
   Serial.write("Integer number\t");
num = Int_Num_from_PC(num_string, '\r');

do{
if(!(num%m)){Int_Num_to_PC(m, num_string, '\t');}
m += 1;}while(m < num);
SW_reset;
 return 1;}



/******************************************************************************************/
int Int_Num_from_PC(char * num_as_string,char next_char)
{char strln;

Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
if(atol(num_as_string) > 0x7FFF){Serial.write("Number is too large"); SW_reset;}
return atoi(num_as_string);}


void Int_Num_to_PC(long Int_num, char * num_as_string, char next_char)
{
ltoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);Serial.print(next_char);
}
