
/*
 
Switch assignments:
    SW1 PORTD2 PCINT18 
    SW2 PORTD5 PCINT21
    SW3 PORTD7 PCINT23
*/

 
#include "INT_from_IO_header.h"







int main (void){

long Long_num;

int twos_exp;

setup_328_HW;

sei();
Data_Entry_complete=0;
clear_display;                       
Long_num = Int_number_from_IO();
} 





/********************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

if((switch_1_up) && (switch_2_up) && (switch_3_up))return;

if(switch_3_down){                                        //End of data entry
if (switch_2_down){sei();clear_display;cli();

while ((switch_3_down) || (switch_2_down));

initialise_display;
return; }



for(int m = 0; m<=7; m++)
{disp_bkp[m]=display_buffer[m]; display_buffer[m]= 0;}
pause_PCI_and_Send_int_num_string;
Timer_T2_10mS_delay_x_m(25);                                //Flash display
for(int m = 0; m<=7; m++)
{display_buffer[m]=disp_bkp[m];}
digit_entry = 1;
Data_Entry_complete=1;
pause_PCI_and_Send_int_num_string;
while(switch_3_down);                                     //Pause update of display
return;}


while(switch_1_down)
{scroll_display_zero();                                   //Hold SW1 down to scroll throuh the availble chars (0-9, E anf -)
Timer_T2_10mS_delay_x_m(10);}

while(switch_3_down);enable_PCI_on_sw3;                   //Wait for SW3 to be released (may have been pressed to select dp)
if(switch_2_down)shift_display_left();                    //Press SW2 to accept the next char and shift the display
Timer_T2_10mS_delay_x_m(10);
clear_PCI;}                                              //was clear_PCI_on_sw1_and_sw2;}





/********************************************************************************************************/
long Int_number_from_IO(void){

char keypress = 0;
unsigned char num_byte[4];
long Long_Num_from_mini_OS;

set_up_PCI;
enable_PCI_on_sw1_and_sw2;

initialise_display;

do{                                                           //Repeat untill FPN string entry is complete
while
((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 

enable_PCI_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                              //Entry of FP string complete 

pause_PCI_and_Send_int_num_string;

cr_keypress = 0;
Int_from_mini_OS;

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;
return Long_Num_from_mini_OS;}

/************************************************************************************************************/
