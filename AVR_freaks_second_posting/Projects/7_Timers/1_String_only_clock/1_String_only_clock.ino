/****************************************************************************************************************
Time reference
Use 32768 watch crystal with /32 prescaler giving 1024 clock
Counts to 1024 in 1 second
Counts to 102 in 100mS
Counts to 204 in 200mS
Counts to 918 in 900mS
Counts 106 in the last 100mS
****************************************************************************************************************/

 
#include "Basic_clock_header.h"
 


char digits[8];
volatile char clock_tick;
volatile char tick_counter; 

int main (void){
char User_response;

setup_328_HW;
initialise_T2();
sei();
String_to_PC("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt;

if(User_response == 'R')
set_time();
else {reset_clock_1;}
Display_time;
clock_tick = 0;


String_to_PC("AK to start\r\n");
waitforkeypress();

start_clock();
while(1){while(clock_tick <= 1);clock_tick = 0; Inc_time();Inc_time();Display_time;}}


/****************************************************************************************************************/
void Inc_time(void){
 if (msecsH < '9') msecsH++; 
  else {msecsH = '0'; if ((SecsL) < '9') SecsL++;   
              else {SecsL = '0'; if (SecsH < '5') SecsH++; 
                          else {SecsH = '0';  if ((MinsL) < '9') MinsL++; 
                                      else {MinsL = '0'; if (MinsH < '5') MinsH++; else {MinsH = '0';

 switch (HoursH){ case '0': if ((HoursL & 0x7F) < '9')HoursL++; else {HoursL='0' | 0x80; HoursH++;} break;
 case '1': if((HoursL) < '1')HoursL++; else {HoursL='0'; HoursH='0';} break;}
 
 }  //  update msecs, seconds units and tens, minutes units and tens and hours
 }  //  update msecs, seconds units and tens and minutes units and tens
 }  //  update msecs, seconds units and tens and minutes units
 }  //  update msecs and seconds units and tens
 }  //  update msecs and seconds units
}

/****************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0;
String_to_PC("Enter start time Hours, Minutes and Seconds\
\r\n(12 hour clock with no spaces). Terminate with cr\r\n");

while(isCharavailable(50) == 0){String_to_PC("T?  ");}

digits[7] = Char_from_PC();Display_time;
for (int m = 0; m<=4; m++){while(isCharavailable(5) == 0);
if(m == 4){digits[2] = Char_from_PC();msecsH = '0'; msecsL = 0;}
else digits[6 - m] = Char_from_PC(); 
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
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}
  
  
 /*Binary_to_Askii (OCR2A, string) ;
  String_to_PC("\r\n");
  String_to_PC(string);*/
  
  }

   
int Binary_to_Askii (long number, char * array_ptr)
{ int i = 0;
  do {
    array_ptr[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  array_ptr[i] = '\0';
  return i;
}


/****************************************************************************************************************/
