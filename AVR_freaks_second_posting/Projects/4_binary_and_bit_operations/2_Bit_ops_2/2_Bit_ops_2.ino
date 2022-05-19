


#include "Bit_ops_2_header.h"


int main (void) {
  char op_code;
  char digits[3];
  unsigned char X;
  char keypress;
  unsigned char lfsr;


  setup_328_HW;
  
  Reset_ATtiny1606;
  lfsr = PRN_8bit_GEN(0xF);

  String_to_PC("\r\n\r\nSelect mode 1 to 6? Then AK to continue or x to exit\r\n");

  while (1)
  { String_to_PC("Mode?\t");

    op_code = waitforkeypress();

    switch (op_code)
    { case '1':   String_to_PC("shift number right\r\n"); break;
      case '2':   String_to_PC("shift number left\r\n"); break;

      case '3':   String_to_PC("set a bit\r\n"); break;
      case '4':   String_to_PC("clear a bit\r\n"); break;
      case '5':   String_to_PC("toggle a bit\r\n"); break;
      case '6':   String_to_PC("test a bit\r\n"); break;
    }

    digits[1] = 1;
    digits[2] = 0;
    X = 0;
    do
    { if (digits[1] == 1)
      { digits[0] = PRN_8bit_GEN(lfsr); lfsr = PRN_8bit_GEN(digits[0]);

        digits[2] = digits[0];
        One_wire_comms_3_bytes(digits);
        waitforkeypress();
      }

      digits[2] = logical_op(digits[1], digits[0], op_code);

      One_wire_comms_3_bytes(digits);
      keypress = waitforkeypress();

      if (op_code < '3')
      { if (++digits[1] == 8)digits[1] = 1;
      }
      else
      { digits[1] = (((byte)digits[1] << 1) % 255);
      }


    } while (keypress != 'x');

  }
}



/*************************************************************************************/
char logical_op(char X, char Y, char op_code) {
  char result = 0;
  switch (op_code) {

    case '1': result = Y << X; break;
    case '2': result = (byte)Y >> X; break;
    case '3': result = Y | X; break;
    case '4': result = Y & (~(X)); break;
    case '5': result = Y ^ (X); break;
    case '6': result = Y & (X); break;
  }
  return result;
}
