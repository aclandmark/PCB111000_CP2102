
/*
 From this point on Arduino library functions are introduced where possible.
 For example 
 Serial.begin(115200):    This initialsed the UART for 57600 Baud (assuming an 8MHz clock)
 Serial.write:            This sends text to the PC
 Serial print:            This sends numbers to the PC as text
 atol/atoi:               This converts a text string to a long / integer number
 ltoa:                    This converts a long number to text (askii characters)

 Note all characters received by the UART are saved to a buffer.
 Serial.readBytesUntil as implemented here reads these characters and transfers them
 to a separate buffer "num_as_string" stoping only when a cairrage return (cr) is detected
 or 20 keypresses have been made.
 The keypresses contained in the buffer "num_as_string" are then converted to a number. 
 */



#include "Integer_numbers_header.h"



/************************************************************************************************************/





int main (void)  
  { 
    char num_string[12], User_response;
    int  num;
    int m = 1;
 
 setup_328_HW_Arduino;
    
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
if(atol(num_as_string) > 0x7FFF)
{Serial.write("Number is too large"); SW_reset;}
return atoi(num_as_string);}



/******************************************************************************************/
void Int_Num_to_PC(long Int_num, char * num_as_string, char next_char)
{
ltoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);
Serial.print(next_char);
}
