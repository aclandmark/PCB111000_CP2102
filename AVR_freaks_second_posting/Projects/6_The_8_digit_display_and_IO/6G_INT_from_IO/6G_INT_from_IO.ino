
/*
Takes an integer number from the IO, converts it to floating point
and then to the form A * 2^N where A is between 1 and 2 and N is an integer.

Press 
  SW1 to scroll through the digits
  SW2 to shift the display left
  SW3 to enter the number

Then press SW1 and SW3 to dsisplay A and N

Switch assignments:
    SW1 PORTD2 PCINT18 
    SW2 PORTD5 PCINT21
    SW3 PORTD7 PCINT23
*/

 
#include "INT_from_IO_header.h"


int main (void){

long Long_num;
int twos_exp;
float FPN_1_num;

setup_328_HW_Arduino_IO;

Data_Entry_complete=0;
clear_display;                    
Long_num = Int_number_from_IO();

FPN_1_num = (float)Long_num;
if(FPN_1_num < 0){

for(int m = 0; m < 5; m++){_delay_ms(50); wdr();}

FPN_1_num *= -1.0; 
float_num_to_display(FPN_1_num);}

if (FPN_1_num >= 1.0) 
{twos_exp = 0; while (FPN_1_num >= 2.0) 
{FPN_1_num = FPN_1_num/2.0; twos_exp += 1;}} 

while(1){
while(switch_1_up)wdr();
float_num_to_display(FPN_1_num);
while(switch_3_up)wdr();
Int_num_to_display(twos_exp);
while(switch_1_up)wdr();
float_num_to_display(pow(2, twos_exp) * FPN_1_num);
while(switch_3_up)wdr();
if(switch_2_down){SW_reset;}}} 





/********************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

if((switch_1_up) && (switch_2_up) && (switch_3_up))return;

if(switch_3_down){ 
if (switch_2_down){sei();clear_display;cli();
while ((switch_3_down) || (switch_2_down))wdr();
initialise_display;
return; }

digit_entry = 1;
Data_Entry_complete=1;
pause_PCI_and_Send_int_num_string;
while(switch_3_down);
return;}


while(switch_1_down)
{scroll_int_display_zero(); 
Timer_T2_10mS_delay_x_m(10);}

while(switch_3_down)wdr();enable_PCI_on_sw3;  
if(switch_2_down)shift_int_display_left();  
Timer_T2_10mS_delay_x_m(10);
clear_PCI;}       





/********************************************************************************************************/
long Int_number_from_IO(void){

char keypress = 0;
unsigned char num_byte[4];
long Long_Num_from_mini_OS;

set_up_PCI;
enable_PCI_on_sw1_and_sw2;
initialise_display;

do{      
while
((!(Data_Entry_complete)) && (!(digit_entry)))wdr();            
enable_PCI_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;  
pause_PCI_and_Send_int_num_string;
cr_keypress = 0;
Int_from_mini_OS;

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;
return Long_Num_from_mini_OS;}

/************************************************************************************************************/
