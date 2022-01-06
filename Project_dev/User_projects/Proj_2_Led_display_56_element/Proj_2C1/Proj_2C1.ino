
#include "Proj_2C1_header.h"                                    //Contains resources used by template and shared with programmer



int main (void){ 

char letter=0;
char digit_num=0;
char seg_counter = 0;
char direction = 0;


setup_328_HW;                                                 //see "Resources\ATMEGA_Programmer
                                                     //needed for intensity control
//User_prompt_proj_2C1;

One_wire_Tx_char = 'c';  UART_Tx_1_wire();



while(1){                                                      //Generate pattern
while(seg_counter < 56){                                       //There are 56 segments in total
letter = (PRN_16bit_GEN (0)%7) + 'a';
digit_num = (PRN_16bit_GEN (0)%8);
                                                              //Continue statements skip back to the top of the while-loop
                                                              //This is to ensure segments are not turned-off before
                                                              //they have all been turned on.

if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) continue;
if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) continue;

I2C_Tx_any_segment(letter, digit_num);

backup_the_display(letter, digit_num);                        //keep backup up to date

seg_counter += 1;}

direction ^= 1;                                                //Toggle the direction_counter value
seg_counter = 0;
_delay_ms(500);}

SW_reset;
return 1;}
