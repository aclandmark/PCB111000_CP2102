
/*
 Almost identical to 5A
 */


#include "Segment_driver_header.h"


#define message_1 "\r\nFor each digit press 0 to 7 then a to g for segments.\t"
#define message_2 "Again!\t"





int main (void){

char keypress = 0, digit_num=0;            

setup_328_HW;

Serial.begin(115200);
    while (!Serial);
if (eeprom_read_byte ((uint8_t*)0x3FC) == 0xFF)
eeprom_write_byte((uint8_t*)0x3F5, 0xFF);                               //POR detected

if(!(eeprom_read_byte ((uint8_t*)0x3F5)))
Serial.write(message_2);    
else{eeprom_write_byte((uint8_t*)0x3F5, 0xFF);
Serial.write(message_1);}
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

case 'x': {eeprom_write_byte((uint8_t*)0x3F5, 0);
clear_display;SW_reset;} break;                                          //if any other key (AOK) execute a SW_reset.

defaut: break;

}                                                                        //Bottom of switch block return to top of "do-loop"
}
}                                                                         //Repeat program
