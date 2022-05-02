/****************************************************************************************************************
Time reference
Use 32768 watch crystal with /32 prescaler giving 1024 clock
Counts to 1024 in 1 second
Counts to 102 in 100mS
Counts to 204 in 200mS
Counts to 918 in 900mS
Counts 106 in the last 100mS
****************************************************************************************************************/

 
#include "Stand_alone_clock_header.h"

/*volatile char clock_tick;
volatile char tick_counter; 

char digits[8], charH, charL ;
char Hours, Minutes, Seconds, deci_Secs;
long deci_sec_counter;



int main (void){
char User_response;
setup_328_HW;
initialise_T2();
sei();
clear_display;

String_to_PC("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt;
if(User_response == 'R')set_time();
else {reset_clock_1; deci_SecsH = '0'; deci_SecsL = '0';  }
Display_time;

String_to_PC("AK to start\r\n");
waitforkeypress();


start_clock();
while(1){while(clock_tick <= 1);clock_tick = 0; Inc_OS_time;
}}
*/



void time_from_IO(void);
volatile int digit_num = 7;
char digits[8];
volatile char Data_Entry_complete=0;
char keypress = 0;
volatile char tick_counter; 
volatile char clock_tick;

 
int main (void){
char display_mode;

setup_328_HW;
initialise_T2();
sei();
clear_display;                       
User_instructions;
time_from_IO();
//I2C_Tx_OS_timer(AT_clock_mode, digits);           //Send Start clock command (AT clock mode is 7)



/********************Clock Control loop**************************************************************************/

/*display_mode = 0;
while(1){                           //Operation continuously cycles around this loop 
Timer_T1_sub(T1_delay_100ms);
switch (display_mode){                      //Beware of switch bounce

case 0: if(switch_2_down){Timer_T1_sub(T1_delay_500ms); display_mode = 'A';}
    if(switch_1_down){display_mode = 'B';I2C_Tx_Clock_command(hide_clock);while(switch_1_down);}
    if(switch_3_down){display_mode = 'C';I2C_Tx_Clock_command(pause_clock);while(switch_3_down);}break;

case 'A': if(switch_2_up)display_mode = 1; else {while(switch_2_down); display_mode = 2;} break;
case 'B':if(switch_1_down){display_mode = 0;I2C_Tx_Clock_command(display_clock);while(switch_1_down);}break;
case 'C':if(switch_3_down){display_mode = 0; I2C_Tx_Clock_command(display_clock);while(switch_3_down);}break;


case 1: if (switch_1_down){I2C_Tx_Clock_command(increment_seconds);Timer_T1_sub(T1_delay_200ms);}
    if (switch_3_down){I2C_Tx_Clock_command(increment_minutes);Timer_T1_sub(T1_delay_200ms);}
    if(switch_2_down){ while (switch_2_down);display_mode = 0; }break;
    
case 2: if (switch_1_down){I2C_Tx_Clock_command(decrement_seconds);Timer_T1_sub(T1_delay_200ms);}
    if (switch_3_down){I2C_Tx_Clock_command(decrement_minutes);Timer_T1_sub(T1_delay_200ms);}
    if(switch_2_down){while (switch_2_down);display_mode = 0; }break;}}
    */
    }



/***********************************************************************************************************************/

void time_from_IO(void){
char temp=0;
set_up_PCI;
enable_PCI;
disable_pci_on_sw2;
for(int m = 0; m<= 7; m++)digits[m] = 0;
digits[7] = '_';Display_time(digits);
sei();
while(!(Data_Entry_complete));              //Line A. wait here for pci interrupts used to enter data
Data_Entry_complete = 0;        
for(int m = 0; m<=3; m++)               //Reverse "start_time" array
{temp = digits[m]; 
digits[m] = digits[7-m];
digits[7-m] = temp;}}


/***********************************************************************************************************************/

ISR(PCINT2_vect) {                    //input number: store keypresses in array -start_time
if((switch_1_up) && (switch_3_up))return;
Timer_T1_sub(T1_delay_50ms);               //Place delay here to trap bounce on sw release
clear_PCI;

if (switch_1_down){                   //Switch_1: used to scroll through the permissible                    
switch(digit_num){                    //characters for each digit on the display
case 7: 
switch (digits[7]){                 //Enter Digit 7 hours 0,1 or 2
case '0': case '1': digits[7]++; break;
case '2': digits[7] = '0';break;
default:digits[7]='0';break; }break;

case 6:
if (digits[7]== '2'){               //Enter Digit 6 hours 0,1,2 or 3
switch (digits[6]){
case '0': case '1': case '2': digits[6]++; break;
case '3': digits[6] = '0';break;
default:digits[6]='0';break;}} 

else                          //Enter Digit 6 hours 0 to 9
switch (digits[6]){
case '_': case '9': digits[6] = '0'; break;
default:digits[6]++;break;}
break;

case 4:                         //Enter Digit 4 minutes 0 to 5
switch (digits[4]){
case '0': case '1': case '2':
case '3': case '4': digits[4]++; break;
case '5': digits[4] = '0'; break;
default:digits[4]='0';break;} break;


case 3:                         //Enter Digit 3 minutes 0 to 9
switch (digits[3]){
case '_': case '9': digits[3] = '0'; break;
default:digits[3]++;break;} break;


case 1:                         //Enter Digit 1 seconds 0 to 5
switch (digits[1]){
case '0': case '1': case '2':
case '3': case '4': digits[1]++; break;
case '5': digits[1] = '0'; break;
default:digits[1]='0';break;} break;

case 0:                         //Enter Digit 0 secondes 0 to 9
switch (digits[0]){
case '_': case '9': digits[0] = '0'; break;
default:digits[0]++;break;} break;}

Display_time(digits);}           //Keep display up-to date 
      


if (switch_3_down){                   //Switch_3: Used to select a character and move onto the next digit
switch(digit_num){
case 7: case 4: case 1:
digit_num--;digits[digit_num] = '_';break;
case 6: case 3: digit_num -=2; digits[digit_num] = '_'; break;
case 0: digit_num = 7; Data_Entry_complete = 1;
disable_pci_on_sw1_and_sw3;
digits[2] = ' ';
digits[5] = ' ';
while(switch_3_down);Timer_T1_sub(T1_delay_100ms); 
break;}
Display_time(digits);}}            //return to Line A when sw1 is released






















/*******************************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0;
String_to_PC("Enter start time Hours, Minutes and Seconds\
\r\n(24 hour clock with no spaces). Terminate with cr\r\n");

while(isCharavailable(50) == 0){String_to_PC("T?  ");}

digits[7] = Char_from_PC();Display_time;
for (int m = 0; m<=4; m++){while(isCharavailable(5) == 0);
if(m == 4)
{digits[2] = Char_from_PC();deci_SecsH = '0'; deci_SecsL = '0'; }
else 
digits[6 - m] = Char_from_PC(); 
Display_time;}

waitforkeypress();

clear_display;
_delay_ms(50);}







/****************************************************************************************************************/
void initialise_T2(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}


void start_clock(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}


ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}
  

/************************************************************************************************************/
