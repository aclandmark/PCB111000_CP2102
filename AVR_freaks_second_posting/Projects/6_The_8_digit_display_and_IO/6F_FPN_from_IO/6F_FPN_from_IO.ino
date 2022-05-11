
/*
 
 OLD design
 SW1 PORTD2 PCINT18 scrolls through the available digits 
 SW2 PORTD7 PCINT23
 SW3 PORTB2 PCINT2

 PCIE2 / PCMSK2 / PCINT2_vect     PCINT 16 to 23
 PCIE0 / PCMSK0 / PCINT0_vect     PCINT 0 to 7 

  NEW design
SW1 PORTD2 PCINT18 
SW2 PORTD5 PCINT21
SW3 PORTD7 PCINT23
  


 
 */

 
#include "FPN_from_IO_header.h"

#define shift_digits_left {for (int n = 0; n < 7; n++){display_buffer[7-n] = display_buffer[6-n];}}


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


volatile int digit_num = 7;
char display_buffer[8];
//volatile char Data_Entry_complete=0;




int main (void){

long deci_sec_counter = 0;
setup_328_HW;

sei();
Data_Entry_complete=0;
clear_display;                       
FPN_number_from_IO();
//for(int m = 0; m <= 7; m++){display_buffer[m] = m + '0';}
//cr_keypress = 1;
//Send_int_num_string;


while(1);
} 





/********************************************************************************************************/  
float FPN_number_from_IO(void){

char keypress = 0;
float f_number;
float * Flt_ptr_local;
char * Char_ptr_local;

for(int m = 0; m <= 7; m++){display_buffer[m] = 0;}                //Clear display

Flt_ptr_local = &f_number;
Char_ptr_local = (char*)&f_number;

set_up_PCI;
enable_PCI_on_sw1_and_sw2;

clear_display;

display_buffer[0] = '0';//Send_float_num_string;while(1);

do{                                                             //Repeat untill FPN string entry is complete
while((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 

enable_PCI_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                                              //Entry of FP string complete 
Send_float_num_string;                                      //Acquire FP number from display driver
cr_keypress = 0;

One_wire_Tx_char = 'E'; UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){
UART_Rx_1_wire(); *Char_ptr_local = One_wire_Rx_char;
Char_ptr_local += 1;}

f_number = *Flt_ptr_local;

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;

return f_number;}


/********************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

if((switch_1_up) && (switch_2_up) && (switch_3_up))return;
sei();
if(switch_3_down){                                        //End of data entry
if (switch_2_down){clear_display;return;}               //No backspace but dispaly can be re-initialised

for(int m = 0; m<=7; m++)
{disp_bkp[m]=display_buffer[m]; display_buffer[m]= 0;}
Send_float_num_string;
Timer_T2_10mS_delay_x_m(50);                                //Flash display
for(int m = 0; m<=7; m++)
{display_buffer[m]=disp_bkp[m];}
digit_entry = 1;
Data_Entry_complete=1;
Send_float_num_string;
while(switch_3_down);                           //Pause update of display
_delay_ms(250);
return;}


while(switch_1_down)
{scroll_display_zero();                           //Hold SW1 down to scroll throuh the availble chars (0-9, E anf -)
Timer_T2_10mS_delay_x_m(20);}

while(switch_3_down);enable_PCI_on_sw3;                   //Wait for SW3 to be released (may have been pressed to select dp)
if(switch_2_down)shift_display_left();                    //Press SW2 to accept the next char and shift the display
Timer_T2_10mS_delay_x_m(20);
clear_PCI;}                                              //was clear_PCI_on_sw1_and_sw2;}





/********************************************************************************************************/
void shift_display_left(void){

if(display_buffer[0] & 0x80)dp_control = 1;                    //No more decimal points allowed
if (display_buffer[0] == 'e')
{exp_control = 1; neg_sign = 0;}                      //Negative exponent allowed
else neg_sign = 1;                              //FP number can have one negative sign 

scroll_control = (exp_control << 2) | (dp_control << 1) | neg_sign;   

shift_digits_left; 
display_buffer[0] = '0'; 
Send_float_num_string;
digit_entry = 1;}




/********************************************************************************************************/
void scroll_display_zero(void){
unsigned char data_zero;

disable_PCI_on_sw3;

data_zero = display_buffer[0];

if (switch_3_up){display_buffer[0] &= (~(0x80));             //Decimal point dissabled

switch (display_buffer[0]){
case '9':
switch(scroll_control){ 
case 0: display_buffer[0] = '-'; break;                    //Initial state scroll 0-9 -ve 0...... dp is enabled
case 1: display_buffer[0] = '0'; break;                    //First char entered -ve sign dissabled  dp enabled
case 3: display_buffer[0] = 'e'; break;                    //Decimal point entered.  Dissable DP. Enable E.
case 6: display_buffer[0] = '-'; break;                    //E entered. Enable -ve sign
case 7: display_buffer[0] = '0'; break;}break;               //Dissable -ve sign

case '-':
switch(scroll_control){
case 0: display_buffer[0] = '0'; break;                    //Initial state
case 6: display_buffer[0] = '0'; break;}break;

case 'e':
switch(scroll_control){
case 0: display_buffer[0] = '0'; break;                    //Initial state
case 1: display_buffer[0] = '0'; break;    
case 3: display_buffer[0] = '0'; break;}break;

default: display_buffer[0] += 1; break;}}

if((switch_3_down) && (!(dp_control))){display_buffer[0] |= 0x80;      //Decimal point enabled 

switch (display_buffer[0] & (~(0x80))){
case '9': 
display_buffer[0] = ('0' | 0x80);break;
default:  display_buffer[0] += 1;break;}}

sei();Send_float_num_string;}





/************************************************************************************************************/
