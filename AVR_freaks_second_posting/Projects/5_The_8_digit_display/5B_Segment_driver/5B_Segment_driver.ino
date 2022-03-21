
#include "Proj_2F_header_file.h"




#define message_1 "For each digit press 0 to 7 then a to g for segments."
#define message_2 "Again!"





int main (void){

char keypress = 0, digit_num=0;            

setup_HW;

if (!(watch_dog_reset))                         //Normal start up i.e. POR or post programming
String_to_PC(message_1);                        //Send normal start-up message


else {watch_dog_reset = 0;                        //Start up following SW_reset (reset watch_dog_reset flag)
newline();String_to_PC(message_2);                    //Send abbreviated message            
I2C_Tx_any_segment('h', 0);}                      //Restore display after SW_reset

do{                                   //Keep inputting data until x is received

while(1){if(isCharavailable(10)){keypress = receiveChar();break;}}  //"isCharavailable" is repeatedly executed until a character is received
                                    // when the "break" command allows program flow to escape from the "while(1)" loop

switch(keypress){                           //Test keypress
case '0': case '1': case '2': 
case '3': case '4': case '5': 
case '6': case '7': digit_num = keypress - '0'; break;          //If numeric save it as "digit_num".

case 'a': case 'b': case 'c':                     //If a letter illuminate the display 
case 'd': case 'e': case 'f': 
case 'g': I2C_Tx_any_segment(keypress, digit_num); break;

case 'x': break;                            //if x clear the display

default: {SW_reset;} break;                       //if any other key (AOK) execute a SW_reset.
}                                   //Bottom of switch block return to top of "do-loop"
}while(keypress != 'x');                        //Bottom of "do-loop" with exit condition

I2C_Tx_any_segment_clear_all();
SW_reset;}                                //Repeat program
