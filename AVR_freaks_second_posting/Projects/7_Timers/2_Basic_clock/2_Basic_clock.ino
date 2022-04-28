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

 volatile char clock_tick;
volatile char tick_counter; 

void set_time(void);
void timer_utoa(char);
void Format_time_for_display(void);//Display_time(void);

char digits[8], charH, charL, Hours, Minutes, Seconds;
unsigned int sec_counter;


int main (void){
char User_response;
setup_328_HW;
sei();


String_to_PC("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt;
if(User_response == 'R')set_time();
else {reset_clock_1; msecsH = 0; msecsL = 0;  }
Display_time;

String_to_PC("AK to start\r\n");
waitforkeypress();
binUnwantedChars();

while(1){Timer_T2_10mS_delay_x_m(100);sec_counter++; Format_time_for_display();}}




/**********************************************************************************************************************/
void Format_time_for_display(void){
Hours = sec_counter/3600;
Minutes = (sec_counter%3600)/60;
Seconds = (sec_counter%3600)%60;
timer_utoa(Hours); HoursH = charH; HoursL = charL; 
timer_utoa(Minutes); MinsH = charH; MinsL = charL; 
timer_utoa(Seconds); SecsH = charH; SecsL = charL; 
Display_time;}



/**********************************************************************************************************************/
void set_time(void){
String_to_PC("\r\nEnter start time Hours, Minutes and Seconds (12 hour clock, no spaces)\r\n");
while(isCharavailable(50) == 0){String_to_PC("T?  ");}    
    HoursH = Char_from_PC();
    while(isCharavailable(5) == 0); HoursL = Char_from_PC();
    while(isCharavailable(5) == 0); MinsH = Char_from_PC();
    while(isCharavailable(5) == 0); MinsL = Char_from_PC();
    while(isCharavailable(5) == 0); SecsH = Char_from_PC();
    while(isCharavailable(5) == 0); SecsL= Char_from_PC(); 
    msecsH = 0; msecsL = 0; 
    sec_counter = ((((HoursH -'0') * 10) + HoursL-'0') * 3600) + ((((MinsH-'0') * 10) + MinsL-'0') * 60) +(SecsH-'0') * 10 + SecsL - '0'; }
    


/**********************************************************************************************************************/
void timer_utoa(char n){                //converts an unsigned number to a string of digits
if (n>=10)
{charL = n%10;
charH = (n-charL)/10;
charL = charL + '0';
charH = charH + '0';}
else
{charH = '0'; charL = n + '0';}}







/*********************************************************************/
void binUnwantedChars (void){char bin_char;
while(1){if (isCharavailable(5)==1)bin_char = Char_from_PC();else break;}}












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
