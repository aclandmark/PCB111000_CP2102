
/*
 Enables users to drive the display manually
 This indicates that there is not necessarily any connection between 
 the display and an actual number.

 Note:  The PCB111000 bootloader enables user programs to distinguish between
 SW_resets and other resets (i.e POR and first time run following programming).
 This facility is excercised here.
 */


#include "Segment_driver_header.h"


int main (void){

char letter = 0, digit_num;            

setup_328_HW;
set_up_PCI_on_sw2;
  enable_pci_on_sw2;
 Serial.begin(115200);
    while (!Serial);

if (eeprom_read_byte ((uint8_t*)0x3FC) == 0xFF)
eeprom_write_byte((uint8_t*)0x3F5, 0xFF);                     //POR detected
    
if(!(eeprom_read_byte ((uint8_t*)0x3F5)))
Serial.write("  ?");    

else{eeprom_write_byte((uint8_t*)0x3F5, 0xFF);
Serial.write("\r\nPress key a to g \
(x for next digit)\r\n");}
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
eeprom_write_byte((uint8_t*)0x3F5, 0);
  sei(); clear_display;
  SW_reset;
}
