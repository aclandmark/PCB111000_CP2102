
#include "Proj_1A1_header.h"                              //Contains resources used by template and shared with programmer

int main (void){ 
 
unsigned int PORT_1, PORT_2;

setup_328_HW;                                           //see "Resources\ATMEGA_Programmer
Comms_clock = 235;
_delay_ms(500);
Num_to_PC(10, eeprom_read_byte((uint8_t*)0x3FA));
_delay_ms(50);
Num_to_PC(10, eeprom_read_byte((uint8_t*)0x3FB));
_delay_ms(50);
Num_to_PC(10, Comms_clock);
_delay_ms(50);


sei();
while(1){
PORT_1 = 1;
PORT_2 = 0x8000;
for(int m = 0; m <=15; m++){
One_wire_Tx_2_integers(PORT_1, PORT_2);
_delay_ms(30);
PORT_1 = PORT_1 << 1;
PORT_2 = PORT_2 >> 1;}}

SW_reset;
return 1;}



/*********************************************************************/
void Num_to_PC(char radix, long long_num){
char array[12];              //Long has 10 chars + sign + null terminator  
SBtoAL(array, long_num, radix);     //calls the Binary to askii subroutine
NumericString_to_PC(array);}        //Prints characters in reverse order

/*********************************************************************/
void SBtoAL(char array[], long num, char radix){          //Signed Binary to Askii
int m=0;
long sign;

if (num == 0x80000000){
switch(radix){
case 10: array[0] = '8';array[1] = '4'; array[2] = '6';   //0x80000000 * -1 = 0
array[3] = '3';array[4] = '8';array[5] = '4'; array[6] = '7';
array[7] = '4';array[8] = '1';array[9] = '2';
array[10] = '-'; array[11] = '\0'; break;

case 16: array[0] = '0';array[1] = '0'; array[2] = '0';   //0x80000000 * -1 = 0
array[3] = '0';array[4] = '0';array[5] = '0'; array[6] = '0';
array[7] = '8';array[8] = '-';array[9] = '\0';
array[10] = '\0'; array[11] = '\0'; break; } return;}

for (int n = 0; n <=11; n++)array[n] = 0; 
if ((sign = num) < 0) num = num * (-1);

do {array[m] = num % radix;
if(array[m] < 10)array[m] += '0'; else array[m] += '7';
m++;} while ((num = num/radix) > 0);
if (sign < 0) {array[m] = '-';m++;}}


/*********************************************************************/
void NumericString_to_PC(char* s){          
int n=0;
while (s[n] != '\0')n++;              //scroll to end of string counting the number of characters
for(int m = n; m; m--)Char_to_PC(*(s + m-1));}    //print last character first




void Char_to_PC(char data){
while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;}


 
