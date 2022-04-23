


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = digits[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = 1;  UART_Tx_1_wire();





#include "Division_subroutine_header.h"
void Num_string_from_KBD(char *);
long Askii_to_binary(char *);
void fraction_to_decimal_string_Local(long, long, char*);

int main (void){
long Num_1, Num_2;
char digits[8];

setup_328_HW;
  sei();

  
while(1){
String_to_PC("Num_1?  ");

Num_string_from_KBD(digits);
Num_1 = Askii_to_binary(digits);

//Num_1 = Num_from_KBD(digits);Num_to_PC(10,Num_1); newline();      //"num_from_KBD" subroutine provides a number in binary form

String_to_PC("Num_2?  ");
Num_string_from_KBD(digits);
Num_2 = Askii_to_binary(digits);


//Num_2 = Num_from_KBD(digits);Num_to_PC(10,Num_2);newline();

String_to_PC("Answer =   ");

if (Num_1 > Num_2)fraction_to_decimal_string_Local(Num_2, Num_1, digits); 
else fraction_to_decimal_string_Local(Num_1, Num_2, digits); 
String_to_PC("\r\n");}SW_reset;}



/**************************************************************************************************/
void fraction_to_decimal_string_Local(long remainder, long denominator, char digits[]){
long digit;
int m=6;
clear_display;
digits[7]= '0';
digits[6] = '_';
String_to_PC("0.");

while(switch_2_up){
digit = divide_A_by_B(product_AB(remainder,10),denominator);    //uses local routine for divide function
remainder = A_modulo_B(product_AB(remainder,10),denominator);   //uses local function to provide the remainder
Char_to_PC(digit+'0');
if(m){digits[m-1] = (digit+'0');m--;
Send_int_num_string(digits);
Timer_T2_10mS_delay_x_m(12);}
Timer_T2_10mS_delay_x_m(6);}}



/**************************************************************************************************/
long product_AB(long A, long B){                  //Product is simply multiple addition
long product = 0;
while(B){product += A; B--;}                    //Check with paper and pencil   
return product;}



/**************************************************************************************************/
long divide_A_by_B(long A, long B){                 //Division is multiple subtraction while result exceeds zero
long result = 0;
while(A>0){A-=B;result++;}
if(!(A))return result;
else return result-1;}



/**************************************************************************************************/
long A_modulo_B(long A, long B){                  //Check with paper and pencil 
return (A - product_AB(divide_A_by_B(A,B),B));}




/****************************************************************************************************/



/************This area is for project subroutines*************************************************************/
void Num_string_from_KBD(char * array_ptr)
{ char keypress;
  while ((keypress = waitforkeypress()) != '\r')
  { *array_ptr = keypress;
    array_ptr += 1;
  }
  *array_ptr = '\0';
}



/********************************************************************************************************/
long Askii_to_binary(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';
    }
  }
  return num;
}
