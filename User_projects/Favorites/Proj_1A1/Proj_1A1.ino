
#include "Proj_1A1_header.h"                              //Contains resources used by template and shared with programmer

int main (void){ 
 
unsigned int PORT_1, PORT_2;

setup_328_HW;                                           //see "Resources\ATMEGA_Programmer

sei();
while(1){
PORT_1 = 1;
PORT_2 = 0x8000;
for(int m = 0; m <=15; m++){
One_wire_Tx_2_integers(PORT_1, PORT_2);
_delay_ms(30);
PORT_1 = PORT_1 << 1;
PORT_2 = PORT_2 >> 1;}}

SW_reset;
return 1;}
