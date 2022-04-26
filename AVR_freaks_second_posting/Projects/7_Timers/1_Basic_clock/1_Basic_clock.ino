/****************************************
Time reference
Use 32768 watch crystal with /32 prescaler giving 1024 clock
Counts to 1024 in 1 second
Counts to 102 in 100mS
Counts to 204 in 200mS
Counts to 918 in 900mS
Counts 106 in the last 100mS

TCNT2 = 102
Start clock
9 times (At interrupt TCNT2 = (TCNT2 + 102)%256    Update display)
On the tenth time wait for overflow

 
 ****************************************/


#define Display_time \
{One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int p = 0; p <= 7; p++){\
switch (p){\
  case 2:\
  case 4:\
  case 6: One_wire_Tx_char = digits[p] | 0x80; UART_Tx_1_wire(); break;\
  default: One_wire_Tx_char = digits[p]; UART_Tx_1_wire(); break;}}}

 
#include "Basic_clock_header.h"


char digits[8];

int main (void){
char User_response;

setup_328_HW;
sei();
String_to_PC("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt;

if(User_response == 'R')set_time();
else {reset_clock_1;}
Display_time;

String_to_PC("AK to start\r\n");
waitforkeypress();

while(1){Timer_T2_10mS_delay_x_m(10);Inc_display();}}




/**********************************************************************************************************************************************************/
void Inc_display(void){
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

Display_time;}

/**********************************************************************************************************************************************************/
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
