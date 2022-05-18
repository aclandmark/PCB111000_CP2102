
/*
 Enables users to drive the display manually
 This indicates that there is not necessarily any connection between 
 the display and an actual number.

 Note:  The PCB111000 bootloader enables user programs to distinguish between
 SW_resets and other resets (i.e POR and first time run following programming).
 This facility is excercised here.
 */


#include "Segment_driver_header.h"


#define message_1 "\r\nPress key a to g (x for next digit)\r\n"
#define message_2 "  ?"



int main (void){

char letter = 0, digit_num;            

setup_328_HW_extra;
set_up_PCI_on_sw2;
  enable_pci_on_sw2;


if(WDT_out_status == 1)Serial.write(message_1);
if(WDT_out_status == 2)Serial.write(message_2);

sei();


while(1){digit_num=0;
while(digit_num < 8){

if(Serial.available())                                        //Wait up to 60mS for a key press.  In the absence of one
{switch(letter = Serial.read()){                              //the program reverts back to "while(digit_num < 8){"
case 'a': case 'A':                                           //otherwise it continues and updates the display
case 'b': case 'B':                                           //Program execution is not put on hold awaiting a keypress
case 'c': case 'C':
case 'd': case 'D':
case 'e': case 'E':
case 'f': case 'F':
case 'g': case 'G': 
One_wire_comms_any_segment(letter, digit_num); break;
case 'x': case 'X': digit_num += 1;break;
default: break;}}}}}


/***************************************************************************************************************/
ISR(PCINT2_vect)
{ if (switch_2_up)return;
Signal_WDTout_with_interrupt;
  sei(); clear_display;
  SW_reset;
}
