

/*
 
*/



#include "Receiver_Transmitter_header.h"



/****************************PIE calculator*********************************************************************
A circle is drawn over a fine grid of squares of side 1 unit in length
The number of squares within the circle is counted to give its area 
from which pie is calculated.**********************************************************************************/


int main (void) 

 {long Area;                    //The area of a 90 degree segment of circle which has its centre at location 0,0.
 unsigned long R;               //The radius of the circle
 unsigned long X;               //The x coordinate of a column of squares
 unsigned long Y;               //The y coordinate at which the column intersects the circle
 char no_decimal_places = 8;
char Num_string[12];
char numLength;
float pie;

unsigned long r_mem;

setup_328_HW;
 Serial.begin(115200);
    while (!Serial);

if (eeprom_read_byte ((uint8_t*)0x3FC) == 0xFF)
eeprom_write_byte((uint8_t*)0x3F5, 0xFF);                               //POR detected

if(!(eeprom_read_byte ((uint8_t*)0x3F5)))
Serial.write("Again?\r\n");    
else{eeprom_write_byte((uint8_t*)0x3F5, 0xFF);
Serial.write("\r\nEstimate value for PIE. Enter radius (65500 max)\r\n");}


R = Unsigned_Int_from_PC(Num_string, '\r'); 


for(int p = 0; p <= 60; p++){

r_mem = R;

Int_Num_to_PC(R, Num_string, '\t');
Y = 1;
Area = 0;

for(unsigned int m = 1; m <= R; m++){
X = R - m;  
while (Y*Y <= ((R*R) - (X*X))) Y += 1; Y -= 1;
Area += Y;}

divide(Area, R*R/4, no_decimal_places, Num_string);
Serial.write(Num_string);
Serial.write("\t");



if ((pie = (float)Area / (float)R / (float)R * 4) < 0.0)
Serial.write ("Overflows");
else {Serial.print (pie,8);
send_float_num(pie);}

R = r_mem + 1000;

for(int n = 0; n <= 11; n++)Num_string[n] = 0;
numLength = 0;
_delay_ms(100);
}



eeprom_write_byte((uint8_t*)0x3F5, 0);
SW_reset;
return 1; }



/******************************************************************************************/
unsigned long Unsigned_Int_from_PC(char * num_as_string,char next_char)
{char strln;
int num;

Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
//Serial.write(num_as_string);
//Serial.write(next_char);

num = atoi(num_as_string);
return (unsigned int )num;}



/******************************************************************************************/
void Int_Num_to_PC(unsigned long Int_num, char * num_as_string, char next_char)
{
ultoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);
Serial.print(next_char);
}


/**********************************************************************************************************/
void divide(unsigned long num, unsigned long den, char no_decimal_places, char * Num_string){
unsigned long quotient, mod;  
char  array_ptr = 0;

division_step (num, den,  &quotient, &mod, no_decimal_places);
Num_string[array_ptr++] = quotient + '0'; 
den /= 10;
Num_string[array_ptr++] = '.';  

while (no_decimal_places) {
no_decimal_places =  division_step ( mod, den, &quotient, &mod, no_decimal_places);
if(den >= 100)den /= 10;
else mod = mod*10;

Num_string[array_ptr++] = quotient + '0';
}

Num_string[array_ptr] = 0;
scanArray(Num_string);
}




/********************************************************************************************************/
 char division_step(unsigned long A, unsigned long B, unsigned long *Div,  unsigned long *mod, int no_decimal_places)
  {*Div = A/B;
  *mod = A%B;
  
  no_decimal_places -= 1;
  return no_decimal_places; } 


/******************Looks for the ':' char and corrects it*************************************************************************/
void scanArray (char * array){
char ptr = 0;
  
while (array[ptr])ptr += 1;
while ((array[ptr] != ':') && (ptr + 1))ptr -= 1;
if(!(ptr))return;

while(1){
array[ptr--] = '0';
array[ptr] += 1;
if (array[ptr] != ':')break;}
}


/**************************************************************************************************************************/
 void send_float_num(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){              //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;             //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;}
reinstate_pin_change_interrupt_on_PC5;}
