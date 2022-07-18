

#include "Bit_ops_1_header.h"



int main (void){

char comp;
char digits[3];
unsigned char lfsr;
char BWop;                                  //bit wise operation and complement (i.e. swap ones and zeros)


setup_328_HW_Basic_IO;


String_to_PC_Basic("\r\nSelect OP:  |   ^   &   ~|  ~^  or  ~&");
BWop = waitforkeypress_Basic();
if (BWop == '~') {comp = 1; BWop = waitforkeypress_Basic();}else comp = 0;        //detect complement operator
if ((BWop != '|') && (BWop != '^') && (BWop != '&'))
SW_reset;                                                              //reset if duff char was sent 
Reset_ATtiny1606;

  
lfsr = PRN_8bit_GEN(0xF);
do{
digits[0] = PRN_8bit_GEN(lfsr);
digits[1] = PRN_8bit_GEN(digits[0]);
digits[2] =  Op(digits[0] , digits[1], comp, BWop);
lfsr = digits[1];
One_wire_comms_3_bytes(digits);}  while (waitforkeypress_Basic() !='x');                
//wdt_enable(WDTO_30MS); while(1);
SW_reset;}




/*************************************************************************************/
char Op(char A, char B, char comp, char BWOp)
{char result=0;
switch (BWOp){
case '|': result = A | B; break;
case '^': result = A ^ B; break;
case '&': result = A & B; break;}
if (comp == 1) result = ~result;
return result;}
