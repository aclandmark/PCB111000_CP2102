
/*Proj_6E_bitwise_ops
******************************************************************/


/*More on bitwise ops


IT INTRODUCES 

1.  The shift operators  << and >>.
These operators will frequently be encountered when setting up the HW (usually in header files).

2.  Project subroutine "binary_char_from_KBD()"

Note press x or X to escape
r or R to start
These options give 4 modes of operation.*/




#include "Bit_ops_2_header.h"


int main (void){
char op_code;
char digits[3];
unsigned char X;
char User_response, keypress;
unsigned char lfsr;


setup_328_HW;
sei();
User_instructions;
User_prompt;

String_to_PC("\r\nSelect logical operation \r\n\
1 for << X  Shifts a number left\r\n\
2 for >> X  Shifts a number right \r\n");
String_to_PC("\
3 for | (1 << X)  Changes just one bit by setting it to 1.\r\n\
4 for &(~(1 << X) Changes just one bit by setting it to 0.\r\n");
String_to_PC("\
5 for XOR(1 << X) Changes just one bit by reversing it.\r\n\
6 for &(1 << X) Tests a single bit\r\n");

Reset_ATtiny1606;
lfsr = PRN_8bit_GEN(0xF);


waitforchar();
while(1){
op_code = Char_from_PC();    


    switch(op_code){
    case '1':
    case '2': String_to_PC("X? 1-7\t"); X = waitforkeypress()-'0'; break;
    case '3':
    case '4':
    case '5':
    case '6': digits[1] = 1;  break;
    default: SW_reset; break;}     //Exit program

   
    digits[2] = 0;
    X = 1;
        
    do{
    
    if (X==1){digits[0] = PRN_8bit_GEN(lfsr); digits[1] = 1;lfsr = PRN_8bit_GEN(digits[0]);}
    digits[2] = logical_op(digits[1],digits[0], op_code, User_response);  

   
  One_wire_comms_3_bytes(digits); 
   keypress=waitforkeypress(); 

    
    switch (op_code){
    case '1': 
    case '2': X = digits[1] + X;break;  
    default: digits[1] = digits[1] << 1; X = (X + 1)%8; break;}             //X; X = (X <<1)%255;  break;} 
    
    //lfsr = PRN_8bit_GEN(digits[0]); 
    }while((keypress != 'x') && (keypress != 'X'));
    
    if(keypress == 'X'){SW_reset;}
    String_to_PC("New mode?\r\n");

    
    
    waitforchar();}} 



/*************************************************************************************/ 
char logical_op(char X, char Y, char op_code, char mode){
char result = 0, n = 0, num;
switch (op_code){

case '1': if(mode == 'r'){Rotate_Right_cyclical; 
result = Y;}else {result = Y << X;} break;
case '2': if(mode == 'r'){Rotate_left_cyclical; 
result = Y;} else {result = Y >> X;}break;

case '3': result = Y | X; break;
case '4': result = Y &(~(X)); break;
case '5': result = Y ^ (X); break;
case '6': result = Y & (X); break;}
return result;}



/*************************************************************************************/
char binary_char_from_KBD_Local(void){
char keypress=0, LSB, array[8];

for(int m = 0; m<=7; m++)array[m]=0;
do{
LSB = wait_for_return_key(); 
if (LSB == '\r')break;
if((LSB != '0') && (LSB != '1'));

else {keypress = (keypress << 1) + LSB - '0';
array[0] = keypress;
One_wire_comms_3_bytes(array);
}} while(1);
return keypress;}




/***************************************************************************************************************/
char wait_for_return_key(void){                                //Detects \r\n, \r or \n
char keypress,temp;
keypress = waitforkeypress();
if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable(1)){temp = Serial.read();}keypress = '\r';}
return keypress;}


/*********************************************************************/
void waitforchar(void){
while (!(UCSR0A & (1 << RXC0)));}
