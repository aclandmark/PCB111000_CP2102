
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
char digits[12];



setup_328_HW_Arduino;
Serial.begin(115200);
while (!Serial);

Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");


Num_1 = Float_KBD_to_display(digits);                                     //Data from keyboard
while (1){
 
Sc_Num_to_PC(Num_1,1,5 ,'\r');
waitforkeypress();
Num_1 = pow(Num_1, 3);
float_num_to_display(Num_1);                                                    //Sends number to the display
}                                                                                 //Do some arithmetic

SW_reset;}
