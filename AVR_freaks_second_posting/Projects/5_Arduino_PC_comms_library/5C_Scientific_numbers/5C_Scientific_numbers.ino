
/*
The Arduino library accepts numbers containing a decimal point and also sends them to the PC
Here we use this facility and extend it to include scientific numbers i.e 1.25E8
*/



#include "Scientific_numbers_header.h"

/************************************************************************************************************/





int main (void)  
  { 
    char num_string[12];
    float  num;
    float index;
 
 setup_328_HW_Arduino_IO;
    
   if (reset_status == 1) User_prompt;
 
   Serial.write("\r\nScientific number\r\n");
   
num = Sc_Num_from_PC(num_string, '\r');

if (num < 0.0) index = 3;
else index = 1.5;

while(1){
  while(!(Serial.available()))wdr();
Serial.read();
num = pow (num,index);
Sc_Num_to_PC(num, 2, 4, '\r');
}

 SW_reset;
  return 1;
  }




/*****************************************************************************************/
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



/******************************************************************************************/
float Sc_Num_from_PC(char * num_as_string,char next_char)
{char strln;

pause_WDT;
Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
resume_WDT;
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
return atof(num_as_string);}




/******************************************************************************************/
