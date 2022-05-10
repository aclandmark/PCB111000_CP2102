
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



volatile int digit_num = 7;
char digits[8];
volatile char Data_Entry_complete=0;




int main (void){

long deci_sec_counter = 0;
setup_328_HW;
initialise_T2();
sei();

clear_display;                       
time_from_IO();

while(switch_2_up);

sei();
start_clock();
while(1)
{while(clock_tick <= 1);clock_tick = 0; 
Inc_OS_time;


if((switch_1_down) || (switch_3_down))
{TIMSK2 &= (~(1 << OCIE2A));

deci_secs_from_mini_OS;
deci_sec_counter = deci_sec_counter/10 * 10;
 
while((switch_1_down) || (switch_3_down)){
if(switch_1_down)deci_sec_counter += 10;
else deci_sec_counter -= 10;
deci_Seconds_to_display(deci_sec_counter); 
_delay_ms(25); }
while(switch_2_up);
TIMSK2 |= (1 << OCIE2A);}
}} 



/********************************************************************************************************/  
float FPN_number_from_IO(void){

char keypress = 0;
float f_number;
float * Flt_ptr_local;
char * Char_ptr_local;

for(int m = 0; m <= 7; m++){data_buff[m] = 0;}              //Clear display


num_type = FPN;                               //Floatng point

Flt_ptr_local = &f_number;
Char_ptr_local = (char*)&f_number;

setup_and_enable_PCI;
disable_pci_on_sw3;
clear_display();

do{                                     //Repeat untill FPN string entry is complete
while((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 

enable_pci_on_sw3;

digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                              //Entry of FP string complete 
float_string_to_display();                          //Acquire FP number from display driver
cr_keypress = 0;

TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);                        //Activate TWI and wait for contact from display pcb 
while (!(TWCR & (1 << TWINT)));

*Char_ptr_local =  byte(receive_byte_with_Ack());  Char_ptr_local += 1; //Build up the number as each byte is received
*Char_ptr_local =  byte(receive_byte_with_Ack());  Char_ptr_local += 1;  
*Char_ptr_local =  byte(receive_byte_with_Ack());  Char_ptr_local += 1;      
*Char_ptr_local =  byte(receive_byte_with_Nack());    
f_number = *Flt_ptr_local;
TWCR = (1 << TWINT);
disable_pci_on_sw1_and_sw2;
disable_pci_on_sw3;

return f_number;}


/********************************************************************************************************/
ISR(PCINT0_vect){                              //Press SW3 for entry of complete FPN 
char disp_bkp[8];
if (switch_2_down){clear_display();return;}               //No backspace but dispaly and be re-initialised

if(switch_3_up)return;                            //Ignore switch release

for(int m = 0; m<=7; m++)
{disp_bkp[m]=data_buff[m]; data_buff[m]= 0;}
float_string_to_display();
Timer_T0_10mS_delay_x_m(50);                        //Flash display
for(int m = 0; m<=7; m++)
{data_buff[m]=disp_bkp[m];}
digit_entry = 1;
Data_Entry_complete=1;
float_string_to_display();
while(switch_3_down);                           //Pause update of display
_delay_ms(250);}                              //Delay for switch bounce





/********************************************************************************************************/
ISR(PCINT2_vect){
if((switch_1_up) && (switch_2_up))return;
while(switch_1_down)
{scroll_display_zero();                           //Hold SW1 down to scroll throuh the availble chars (0-9, E anf -)
Timer_T0_10mS_delay_x_m(20);}
while(switch_3_down);enable_pci_on_sw3;                   //Wait for SW3 to be released (may have been pressed to select dp)
if(switch_2_down)shift_display_left();                    //Press SW2 to accept the next char and shift the display
Timer_T0_10mS_delay_x_m(20);
clear_PCI_on_sw1_and_sw2;}


  
/********************************************************************************************************/
void shift_display_left(void){

if(data_buff[0] & 0x80)dp_control = 1;                    //No more decimal points allowed
if (data_buff[0] == 'e')
{exp_control = 1; neg_sign = 0;}                      //Negative exponent allowed
else neg_sign = 1;                              //FP number can have one negative sign 

scroll_control = (exp_control << 2) | (dp_control << 1) | neg_sign;   

shift_digits_left; 
data_buff[0] = '0'; 
float_string_to_display();
digit_entry = 1;}




/********************************************************************************************************/
void scroll_display_zero(void){
unsigned char data_zero;

if(num_type == int_num){
switch (data_buff[0]){
case '9': if(!(data_buff[1])) 
data_buff[0] = '-'; 
else data_buff[0] = '0'; break;
case '-': data_buff[0] = '0'; break;
default: data_buff[0] += 1;break;}

int_string_to_display();
return;}


disable_pci_on_sw3;

data_zero = data_buff[0];

if (switch_3_up){data_buff[0] &= (~(0x80));             //Decimal point dissabled

switch (data_buff[0]){
case '9':
switch(scroll_control){ 
case 0: data_buff[0] = '-'; break;                    //Initial state scroll 0-9 -ve 0...... dp is enabled
case 1: data_buff[0] = '0'; break;                    //First char entered -ve sign dissabled  dp enabled
case 3: data_buff[0] = 'e'; break;                    //Decimal point entered.  Dissable DP. Enable E.
case 6: data_buff[0] = '-'; break;                    //E entered. Enable -ve sign
case 7: data_buff[0] = '0'; break;}break;               //Dissable -ve sign

case '-':
switch(scroll_control){
case 0: data_buff[0] = '0'; break;                    //Initial state
case 6: data_buff[0] = '0'; break;}break;

case 'e':
switch(scroll_control){
case 0: data_buff[0] = '0'; break;                    //Initial state
case 1: data_buff[0] = '0'; break;    
case 3: data_buff[0] = '0'; break;}break;

default: data_buff[0] += 1; break;}}

if((switch_3_down) && (!(dp_control))){data_buff[0] |= 0x80;      //Decimal point enabled 

switch (data_buff[0] & (~(0x80))){
case '9': 
data_buff[0] = ('0' | 0x80);break;
default:  data_buff[0] += 1;break;}}

float_string_to_display();}




/****************************************************************************************************/
void clear_display(void){
for(int m = 0; m<=7; m++)
{data_buff[m]= 0;}
data_buff[0] = '0';
dp_control = 0;       
neg_sign = 0;           
exp_control = 0;
cr_keypress = 0;
Data_Entry_complete = 0;                          //Set to 1 when FP number entry is complete
digit_entry = 0;                              //Set to 1 when digit is selected
scroll_control = 0;
float_string_to_display();}



  /****************************************************************************************************/
long Int_number_from_IO(void){

char keypress = 0;
long I_number;

for(int n = 0; n<=8; n++) data_buff[n] = 0;                //Clear display

num_type = int_num;                               //Integer

setup_and_enable_PCI;
Data_Entry_complete = 0;                          //Set to 1 when FP number entry is complete
digit_entry = 0;                              //Set to 1 when digit is selected

cr_keypress = 0;                              //Set to 1 when atoi() conversion is required  
data_buff[0] = '0';
int_string_to_display();                          //Initialise display

do{                                     //Repeat untill FPN string entry is complete
while((!(Data_Entry_complete)) && (!(digit_entry)));            //Wait for input from IO 
digit_entry = 0;
}while(!(Data_Entry_complete));
Data_Entry_complete = 0;

cr_keypress = 1;                              //Entry of FP string complete 
int_string_to_display();                          //Acquire FP number from display driver
cr_keypress = 0;


TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);                        //Activate TWI and wait for contact from display pcb 
while (!(TWCR & (1 << TWINT)));

I_number =  byte(receive_byte_with_Ack());                  //Build up the number as each byte is received
I_number = (I_number << 8) + byte(receive_byte_with_Ack());     
I_number = (I_number << 8) + byte(receive_byte_with_Ack());         
I_number = (I_number << 8) + byte(receive_byte_with_Nack());    

TWCR = (1 << TWINT);
disable_pci_on_sw1_and_sw2;
disable_pci_on_sw3;
return I_number;}



/************************************************************************************************************/
