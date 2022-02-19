//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


#include "Receiver_Transmitter_header.h"


/********Example 1 Echoes keypresses*************************************
  int main (void)
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





**********Example 2 Prints out ASKII characters**************************************
  int main (void)
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




********Example 3  Echo character string or prints file*******************************

  int main (void)
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



********Example 4 Send strings to the PC**************************************

  int main (void)
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



************Example 5 Generate an ASKII table***********************************

  int main (void)
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



*****************Example 6  Sending numbers to the PC*************************/

  int main (void)
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



/**************Example 7    Entering numbers at the keyboard*************************

int main (void)
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


*******Example 8    More on pointers***************************************************

void test_SR( char, char*);

int main (void)
  { char keyboard_input;
  char test = 1;
    setup_328_HW;
  Char_to_PC('?');
  _delay_ms(10);
  while(1)
  {keyboard_input = waitforkeypress();
test_SR( keyboard_input, &test);
}
  }

void test_SR(char any_letter, char * offset )
{Char_to_PC_Local (any_letter + *offset); *offset += 1;}

********************************************************************************************/

void Char_to_PC_Local(char data)
{ while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}
