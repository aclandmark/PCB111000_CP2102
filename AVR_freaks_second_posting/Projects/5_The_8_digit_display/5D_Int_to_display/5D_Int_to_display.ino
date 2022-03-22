
/**************Proj_3E_Acquire_and process_Data_from_the _KBD********************/
/*Open terminal program, press 'r' at the user prompt, enter number and then press any key (AK)*/

#include "Segment_driver_header.h"

int main (void){
long Num_1;
char digits[8];
int counter = 0;

setup_328_HW;                                                             //(i.e. the address of string "zero", "one", "two" etc....) 
Serial.begin(115200);
    while (!Serial);
User_prompt;

Serial.write("Enter positive number & terminate with Return key.\r\n");
Num_1 = Int_from_KBD_Local(digits);                                         //Acquires data from keyboard

do{
Serial.print(++counter); Serial.write('\t');Serial.print(Num_1); 
Serial.write("\r\n");                                                         //Converts numbers strings and sends them to the pc.
int_num_to_display(Num_1);                                                         //Sends number to the display
waitforkeypress();
Num_1 = (Num_1 / 2) *3;} while (Num_1 < 66666666);                          //Do some arithmetic

Num_1 = (Num_1 / 3) *2; 

do{Num_1 = (Num_1 / 3) *2;                                                   //Do the arithmetic in reverse
Serial.print(--counter); Serial.write('\t');Serial.print(Num_1); Serial.write("\r\n");                                             
int_num_to_display(Num_1);
waitforkeypress();}while (counter-1);}





/******************************************************************************************/
long Int_from_KBD_Local(char display_buffer[]){                                       //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
long I_number;
unsigned char num_byte[4];
long Long_Num_from_UNO;

cr_keypress = 0;                                              //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=8; n++) display_buffer[n] = 0;              //Clear the buffer used for the string


while(1){if(decimal_digit(keypress = waitforkeypress()))break;}
display_buffer[0] = keypress;
 
Send_int_num_string;
while(1){
if ((keypress = wait_for_return_key())  =='\r')break;         //Detect return key press (i.e \r or\r\n)

if (decimal_digit(keypress))
{

{for(int n = 8; n>=1; n--)                                      //Shift display for each new keypress
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;  }                              //Add new keypress           

Send_int_num_string;}}                                        //Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                              //End of string; return key press detected

Send_int_num_string;
cr_keypress = 0;
Int_from_mini_OS;
return Long_Num_from_UNO;}
