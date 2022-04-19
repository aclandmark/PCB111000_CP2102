
/*
 Almost identical to 5A
 */


#include "Segment_driver_header.h"


#define message_1 "\r\nFor each digit press 0 to 7 then a to g for segments.\t"
#define message_2 "Again!\t"





int main (void){

char keypress = 0, digit_num=0;            

setup_328_HW_extra;

Serial.begin(115200);
    while (!Serial);


if(WDT_out_status == 1)Serial.write(message_1);
if(WDT_out_status == 2)Serial.write(message_2);

sei();

while(1){                                                               //Keep inputting data until x is received

while(!(Serial.available())); keypress = Serial.read();            
  
switch(keypress){                                                       //Test keypress
case '0': case '1': case '2': 
case '3': case '4': case '5': 
case '6': case '7': digit_num = keypress - '0'; break;                  //If numeric save it as "digit_num".

case 'a': case 'b': case 'c':                                           //If a letter illuminate the display 
case 'd': case 'e': case 'f': 
case 'g': One_wire_comms_any_segment(keypress, digit_num); break;

case 'x': {Signal_WDTout_with_interrupt;
clear_display;SW_reset;} break;                                          //if any other key (AOK) execute a SW_reset.

defaut: break;

}                                                                        //Bottom of switch block return to top of "do-loop"
}
}                                                                         //Repeat program
