

#include "Scientific_numbers_header.h"

//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


/************************************************************************************************************/





int main (void)  
  { 
    char num_string[12], User_response;
    float  num;
 
 setup_328_HW;
    Serial.begin(115200);
    while (!Serial);
   User_prompt;
 
   Serial.write("Scientific number\t");
num = Sc_Num_from_PC(num_string, '\r');

while(1){
num = pow (num,3);
Sc_Num_to_PC(num, 2, 4, '\r');

while(!(Serial.available()));
Serial.read();}
 SW_reset;
  return 1;
  }




/*****************************************************************************************/
void Sc_Num_to_PC(float num, char pre_dp, char post_dp, char next_char)    //SC_num_to_C
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



/******************************************************************************************/
float Sc_Num_from_PC(char * num_as_string,char next_char)
{char strln;

Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
return atof(num_as_string);}
