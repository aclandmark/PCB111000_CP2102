//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


#include "Receiver_Transmitter_header.h"

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



/************************************************************************************************************

  Use this area for saving the examples when they have been got working and finished with
  Use the space above for the active program (the one eing worked on)



********Example 1: Echoes keypresses*************************************************************************






**********Example 2: Prints out ASKII characters**************************************************************
  int main (void)                          //Example 2
  { char symbol;
  setup_328_HW;
  newline;
  symbol = '!';
  while (symbol <= '~')
  { Char_to_PC_Local(symbol);
    _delay_ms(10);
    symbol++;}
  waitforkeypress();
  SW_reset;
  return 1;}




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
    else break; }
  String_to_PC("Done\r\n");
  SW_reset;
  return 1;}



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
  return 1; }



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
    else Char_to_PC_Local('\t'); }
  while (1);
  return 1;}



*****************Example 6: Sending numbers to the PC*********************************************************

  int main (void)                          //Example 6
  { int i = 0, number = 12345;
  char s[12];
  setup_328_HW;
  do {s[i++] = number % 10 + '0';}
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)
    Char_to_PC(s[m - 1]);
  while (1);
  return 1; }



**************Example 7: Entering numbers at the keyboard*****************************************************

  int main (void)                          //Example 7
  { long num = 0;
  char keypress;
  setup_328_HW;
  num = 0; Char_to_PC('?');
  while ((keypress = waitforkeypress()) != '\r')
  { num = num * 10 + keypress  - '0';
    Int_num_to_display(num);}
  Num_to_PC(num * 2);
  Int_num_to_display(num * 2);
  SW_reset;
  return 1;}


*******Example 8: Simple arithmetic Data to & from PC*********************************************************

  int main (void)                          //Example 8
  {long num = 0;
  char numLength;
  char Num_string[12];
  setup_328_HW;
  String_to_PC("\r\n?\r\n");
  Num_string_from_KBD(Num_string);

  {int m = 0; while (Num_string[m])
  Char_to_PC(Num_string[m++]);}

  num = Askii_to_binary(Num_string);

  num = num *2;
  String_to_PC("\r\n");

  numLength = Binary_to_Askii(num, Num_string);

  for (int m = numLength; m > 0; m--)
  Char_to_PC(Num_string[m - 1]);

  Int_num_to_display(num);

  SW_reset;
  return 1;}



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
  mod = A%B;
  no_decimal_places -= 1;
  return no_decimal_places; }




************This area is for project subroutines*************************************************************/
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
