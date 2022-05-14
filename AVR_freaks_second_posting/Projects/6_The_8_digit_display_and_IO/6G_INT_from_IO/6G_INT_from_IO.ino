
/*
 
Switch assignments:
    SW1 PORTD2 PCINT18 
    SW2 PORTD5 PCINT21
    SW3 PORTD7 PCINT23
*/

 
#include "INT_from_IO_header.h"





#define Int_from_mini_OS \
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); num_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){\
Long_Num_from_mini_OS = Long_Num_from_mini_OS << 8;\
Long_Num_from_mini_OS |= num_byte[m];}







int main (void){

float FPN_1_num;
long ipart, Fnum_int;
int twos_exp;

setup_328_HW;

sei();
Data_Entry_complete=0;
clear_display;                       
FPN_1_num = FPN_number_from_IO();

if(FPN_1_num < 0){
_delay_ms(250);
FPN_1_num *= -1.0; 
float_num_to_display(FPN_1_num);}


if (FPN_1_num >= 1.0)                                   //Multiply or divide number by 2 untill it
{twos_exp = 0; while (FPN_1_num >= 2.0)                 //is between 1 and 2 and adjust its twos_exp 
{FPN_1_num = FPN_1_num/2.0; twos_exp += 1;}}                  //so that its value remains unchanged 

if (FPN_1_num < 1.0)
{twos_exp = 0; while (FPN_1_num < 1.0)
{FPN_1_num = FPN_1_num*2.0; twos_exp -= 1;}}

while(1){
while(switch_1_up);
float_num_to_display(FPN_1_num);
while(switch_3_up);
int_num_to_display(twos_exp);
while(switch_1_up);
float_num_to_display(pow(2, twos_exp) * FPN_1_num);
while(switch_3_up);
if(switch_2_down){SW_reset;}}} 





/********************************************************************************************************/  
float FPN_number_from_IO(void){

char keypress = 0;
float f_number;
float * Flt_ptr;
char * Char_ptr;

Flt_ptr = &f_number;
Char_ptr = (char*)&f_number;

set_up_PCI;
enable_PCI_on_sw1_and_sw2;

initialise_display;

do{                                                         //Repeat untill FPN string entry is complete
while
((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 

enable_PCI_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                                          //Entry of FP string complete 
pause_PCI_and_Send_float_num_string;                     //Acquire FP number from display driver
cr_keypress = 0;

f_number_from_mini_OS;

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;

return f_number;}


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
pause_PCI_and_Send_float_num_string;
Timer_T2_10mS_delay_x_m(25);                                //Flash display
for(int m = 0; m<=7; m++)
{display_buffer[m]=disp_bkp[m];}
digit_entry = 1;
Data_Entry_complete=1;
pause_PCI_and_Send_float_num_string;
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
long Long_Num_from_mini_OS;

//for(int n = 0; n<=8; n++) data_buff[n] = 0;                //Clear display

//num_type = int_num;                               //Integer

set_up_PCI;
enable_PCI_on_sw1_and_sw2;

initialise_display;


//Data_Entry_complete = 0;                          //Set to 1 when FP number entry is complete
//digit_entry = 0;                              //Set to 1 when digit is selected

//cr_keypress = 0;                              //Set to 1 when atoi() conversion is required  
//data_buff[0] = '0';
//int_string_to_display();                          //Initialise display

do{                                                           //Repeat untill FPN string entry is complete
while
((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 

enable_PCI_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                              //Entry of FP string complete 

pause_PCI_and_Send_int_num_string;

//int_string_to_display();                          //Acquire FP number from display driver
cr_keypress = 0;

Int_from_mini_OS;


disable_pci_on_sw1_and_sw2;
disable_pci_on_sw3;
return Long_Num_from_mini_OS;}

/************************************************************************************************************/
