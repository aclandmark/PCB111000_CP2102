
/**************Proj_5D_Acquire_and process_Data_from_the _KBD********************/

/*
Here we leave the mini_OS (the Attiny1606) to deal with all the details of displaying a number.
We can use one_wire_comms to send it a string or binary number.
If we send it a string then it will return the number in binary form.

Obviouly Arduino do not supply library functions to drive the display and therefore a
bit of DIY programming is required.
*/



#include "display_FPN_header.h"


int main (void){
float Num_1;
float power;
char digits[12];



setup_328_HW_Arduino_IO;


Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");


Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard

if(Num_1 > 0.0)power = 1.5; else power = 3.0;

while (1){
 
Sc_Num_to_PC(Num_1,1,5 ,'\r');                            //Send number to PC
waitforkeypress_A();
Num_1 = pow(Num_1, power);                                  //Do some arithmetic
float_num_to_display(Num_1);                              //Sends result to the display
}                                                         //Generates reset if result of arithmetic is too large or small

SW_reset;}
