

/*NOTE ARDUINO automatically configures the UART for 115200 Baud
This translates to 57600 for PCB111000_PCB2102
The PCB111000 bootloader includes a subroutine to initiate the UART
so this does not have to be done by the user projects.

Arduino provides a comprehensive library for sending data to and from a PC.
However simple DIY (do it yourself) functions are used here to illustate
the steps involved and introduce the Atmega328 data sheet.
*/



#include "Receiver_Transmitter_header.h"




/************************************************************************************************************

  Use this area for saving the examples when they have been got working and finished with
  Use the space above for the active program (the one being worked on)



********Example 1: Echoes keypresses*************************************************************************
  int main (void)                          //Example 1
  { setup_328_HW;
  Char_to_PC('?');
  _delay_ms(10);
  newline;
  while (1)
  { Char_to_PC_Local
    (waitforkeypress());
  }
  return 1;
  }






**********Example 2: Prints out ASKII characters**************************************************************
  int main (void)                          //Example 2
  { char symbol;
  setup_328_HW;
  newline;
  symbol = '!';
  while (symbol <= '~')
  { Char_to_PC_Local(symbol);
    _delay_ms(10);
    symbol++;
  }
  waitforkeypress();
  SW_reset;
  return 1;
  }




********Example 3: Echo character string or prints file*******************************************************
  int main (void)                          //Example 3
  { setup_328_HW;
  while (!(isCharavailable(65)))
    Char_to_PC('?');
  newline;
  Char_to_PC(Char_from_PC());
  while (1)
  { if (isCharavailable(10))
      Char_to_PC(Char_from_PC());
    else break;
  }
  String_to_PC("Done\r\n");
  SW_reset;
  return 1;
  }





********Example 4: Send strings to the PC********************************************************************
  int main (void)                          //Example 4
  { setup_328_HW;
  String_to_PC("\r\nDefining and using text strings\r\n");
  const char *message_1 = "Hello world\r\n";
  const char *message_2 = "Sending text to a PC\r\n";
  const char message_3[] = "Writing C programs and\r\n";
  const char message_4[] = "Uploading them to a device\r\n";
  String_to_PC(message_1);
  String_to_PC(message_2);
  String_to_PC(message_3);
  String_to_PC(message_4);
  while (1);
  return 1;
  }




************Example 5: Generate an ASKII table****************************************************************
  int main (void)                          //Example 5
  { char symbol = '!';
  setup_328_HW;
  newline;
  while (symbol <= '~')
  { Num_to_PC(symbol);
    Char_to_PC_Local(symbol++);
    _delay_ms(50);
    if (!((symbol - '!') % 8))newline;
    else Char_to_PC_Local('\t');
  }
  while (1);
  return 1;
  }





*****************Example 6: Sending numbers to the PC*********************************************************
  int main (void)                          //Example 6
  { int i = 0, number = 12345;
  char s[12];
  setup_328_HW;
  do {
    s[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)
    Char_to_PC(s[m - 1]);
  while (1);
  return 1;
  }



**************Example 7: Entering numbers at the keyboard*****************************************************
  int main (void)                          //Example 7
  { long num = 0;
  char keypress;
  setup_328_HW;
  num = 0; Char_to_PC('?');
  while ((keypress = waitforkeypress()) != '\r')
  { num = num * 10 + keypress  - '0';
    Int_num_to_display(num);
  }
  Num_to_PC(num * 2);
  Int_num_to_display(num * 2);
  SW_reset;
  return 1;
  }




*******Example 8: Simple arithmetic Data to & from PC*********************************************************
int main (void)                          //Example 8
{ long num = 0;
  char numLength;
  char Num_string[12];
  setup_328_HW;
  String_to_PC("\r\n?\r\n");
  Num_string_from_KBD(Num_string);

  { int m = 0; while (Num_string[m])
      Char_to_PC(Num_string[m++]);
  }

  num = Askii_to_binary(Num_string);

  num = num * 2;
  String_to_PC("\r\n");

  numLength = Binary_to_Askii(num, Num_string);

  for (int m = numLength; m > 0; m--)
    Char_to_PC(Num_string[m - 1]);

  Int_num_to_display(num);

  SW_reset;
  return 1;
}



*************Example 9: Arithmetic: More on pointers********************************************************
 int main (void)                          //Example 9
  { char keyboard_input;
  char Num_string[12];
  long Num, A = 55; long B = 7; long Div; long mod;
  int no_decimal_places;

    setup_328_HW;
  String_to_PC("?\r\n");
  _delay_ms(10);

  for(int m = 0; m <=2; m++)
  {Num_string_from_KBD(Num_string);
  Num = Askii_to_binary(Num_string);
  switch (m)
  { case 0: A = Num; Char_to_PC('?');break;
  case 1: B = Num; String_to_PC("?\r\n");break;
  case 2: no_decimal_places = Num; break;}}

  divide(A, B, &Div, &mod, no_decimal_places);
  Num_to_PC(Div);
  String_to_PC(". ");
    while (no_decimal_places) {
  no_decimal_places =    divide(mod*10, B, &Div, &mod, no_decimal_places);
  Num_to_PC(Div);}
  String_to_PC("\r\n");
   SW_reset;
  return 1; }

  long divide(long A, long B, long *Div, long *mod, int no_decimal_places)
  {*Div = A/B;
  *mod = A%B;
  no_decimal_places -= 1;
  return no_decimal_places; } 




****************************PIE calculator*********************************************************************
A circle is drawn over a fine grid of squares of side 1 unit in length
The number of squares within the circle is counted to give its area 
from which pie is calculated.**********************************************************************************/


int main (void) 

 {long Area;                    //The area of a 90 degree segment of circle which has its centre at location 0,0.
 unsigned long R;               //The radius of the circle
 unsigned long X;               //The x coordinate of a column of squares
 unsigned long Y;               //The y coordinate at which the column intersects the circle
 char no_decimal_places = 8;
char Num_string[12];
char numLength;


unsigned long r_mem;

setup_328_HW;
if (eeprom_read_byte ((uint8_t*)0x3FC) == 0xFF)
eeprom_write_byte((uint8_t*)0x3F5, 0xFF);                               //POR detected

if(!(eeprom_read_byte ((uint8_t*)0x3F5)))
String_to_PC("Again?\r\n");    
else{eeprom_write_byte((uint8_t*)0x3F5, 0xFF);
String_to_PC("\r\nEstimate value for PIE. Enter radius (65500 max)\r\n");}

Num_string_from_KBD(Num_string);
String_to_PC(Num_string);
String_to_PC("\t");
R = Askii_to_binary(Num_string);String_to_PC("\r\n");

//for(int p = 0; p <= 249; p++){

r_mem = R;
numLength = Binary_to_Askii (r_mem, Num_string);
for (int q = numLength; q > 0; q--)
    Char_to_PC(Num_string[q - 1]);String_to_PC("\t");

Y = 1;
Area = 0;

for(unsigned int m = 1; m <= R; m++){
X = R - m;  
while (Y*Y <= ((R*R) - (X*X))) Y += 1; Y -= 1;
Area += Y;}

divide(Area, R*R/4, no_decimal_places, Num_string);
String_to_PC(Num_string);
String_to_PC("\t");


divide_float(Area, R*R/4, no_decimal_places, Num_string);
String_to_PC(Num_string);
String_to_PC("\t");String_to_PC("\t");


R = r_mem + 100;
//waitforkeypress();
for(int n = 0; n <= 11; n++)Num_string[n] = 0;
numLength = 0;

//}



eeprom_write_byte((uint8_t*)0x3F5, 0);
SW_reset;
return 1; }




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



/********************************************************************************************************/
int Binary_to_Askii (long number, char * array_ptr)
{ int i = 0;
  do {
    array_ptr[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  array_ptr[i] = '\0';
  return i;
}


/********************************************************************************************************/
void Char_to_PC_Local(char data)
{ while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}






/**********************************************************************************************************/
void divide(unsigned long num, unsigned long den, char no_decimal_places, char * Num_string){
unsigned long quotient, mod;  
char  array_ptr = 0;

division_step (num, den,  &quotient, &mod, no_decimal_places);
Num_to_PC(quotient);
den /= 10;
String_to_PC(". ");

while (no_decimal_places) {
no_decimal_places =  division_step ( mod, den, &quotient, &mod, no_decimal_places);
if(den >= 100)den /= 10;
else mod = mod*10;

Num_string[array_ptr++] = quotient + '0';
}

Num_string[array_ptr] = 0;
scanArray(Num_string);
}




/********************************************************************************************************/
 char division_step(unsigned long A, unsigned long B, unsigned long *Div,  unsigned long *mod, int no_decimal_places)
  {*Div = A/B;
  *mod = A%B;
  
  no_decimal_places -= 1;
  return no_decimal_places; } 






/********************************************************************************************************/
void divide_float(unsigned long dividend, unsigned long divisor, int no_decimal_places, char * Num_string){

float A = (float)dividend;
float B = (float)divisor; 
float result;

result = A/B;

FPN_to_askii(result, Num_string, no_decimal_places);}


//divide_float(Area, R*R/4, no_decimal_places, Num_string);

/*************************************************************************************************************************************************/
void FPN_to_askii(float FPN, char * print_buff,  char num_dec_places){

long binary_places = 0;                                                   //Binary equivalent of decimal places
long binary_digits = 0;                                                   //Includes binary digits on both sides of the binary point
int expt_2 = 0;                                                           //Exponent to which binary number is raised.
long LHS_of_dp = 0;
unsigned long FPN_LF = 0;                                                 //FPN in unsigned long format
char print_buff_ptr = 0;



/*********Obtain the twos exponent and use it to determine LHS of the binary point******************/
FPN_LF = *(unsigned long*)&FPN;                                       //The FPN_to_askii routine treats the FPN as an unsigned long integer
expt_2 = ((FPN_LF >> 23) & 0x1FF) - 127;                              //Recover the exponent
binary_digits = FPN_LF & (~(0xFF800000));                             //Mask of exponent and sign, leaving bits on both the LHS & RHS of the point.
binary_digits |= 0x800000;                                            //Reinstate the missing 1 (the most significant bit)
LHS_of_dp = binary_digits >> (23 - expt_2);                           //Remove binary places leaving just the LHS of the binary point




/*********Convert the LHS of the binary point to decimal string and save it in print_buff***********/
for(int m = 0; m<=11; m++)print_buff[m] =0;                           //Clear the buffer
ltoa(LHS_of_dp, print_buff, 10);                                      //Convert LHS_of_dp to askii and save the string to print_buff
print_buff_ptr = 0;
while (print_buff[print_buff_ptr++]);                                 //Find the end of the string
print_buff[print_buff_ptr-1] = '.';                                   //and add the decimal point





/********Isolate the binary digits on the RHS of the binary point******************************************************************/
binary_places = 
binary_digits  & (~(LHS_of_dp << (23 - expt_2)));                     //Remove bits on the LHS of the binary point 

binary_places_to_decimal
(binary_places, expt_2, num_dec_places, print_buff, &print_buff_ptr );}    //Adds decimal places to print_buff






/*********************************************************************************************************************************/
void binary_places_to_decimal(long binary_points, int expt, int Num_dps, char* array, char * array_ptr){
long denominator = 1;                                                       
char result = 0;                                                                //Takes the binary places as an integer number
long remainder = 0;                                                             //converts it to a fraction and
                                                                            //converts this to decimal places
if (expt >= -4)                                                           
{denominator = (unsigned long)0x80000000 >> (8 + expt);                     //Fails for shifts of less than 4
remainder = binary_points;}
else
{denominator = (unsigned long)0x80000000 >> (4);                            //If the exponent is less than -4
remainder = binary_points >> -expt - 4;}                                    //we must also shift the binary points

for (int m = 0; m < Num_dps; m++){
result = ((remainder * 10)/ denominator);
remainder = (remainder * 10) % denominator;
array[(*array_ptr)++] = result + '0';}}





/******************Looks for the ':' char and corrects it*************************************************************************/
void scanArray (char * array){
char ptr = 0;
  
while (array[ptr])ptr += 1;
while ((array[ptr] != ':') && (ptr + 1))ptr -= 1;
if(!(ptr))return;

while(1){
array[ptr--] = '0';
array[ptr] += 1;
if (array[ptr] != ':')break;}
}

 
