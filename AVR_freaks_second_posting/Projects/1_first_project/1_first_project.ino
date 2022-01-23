
#include "First_project_header.h"




/*****************Example 1**********************************************/
/*int main (void)
  { unsigned int PORT_1;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  for (int m = 0; m <= 15; m++)
  { One_wire_Tx_2_integers(PORT_1, PORT_1);
  _delay_ms(30);
  PORT_1 = PORT_1 << 1;
  }
  SW_reset;
  return 1;
  }*/



/**************Example 2*************************************************
  int main (void)
  { unsigned int PORT_1, m = 0, n = 0;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  while (1)
  { One_wire_Tx_2_integers(PORT_1 << m, PORT_1 << m);
    _delay_ms(30);
    if (!(n)) m += 1;
    if (m == 16)n = 1;
    if (n == 1)m -= 1;
    if (m == 0)n = 0;
  }
  return 1;
  }




  ***************Example 3************************************************
  int main (void)
  { unsigned int PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1)
  { PORT_1 = 0b0000000000000001;      //1
    PORT_2 = 0b1000000000000000;     //0x8000;
    for (int m = 0; m <= 15; m++)
    { One_wire_Tx_2_integers(PORT_1, PORT_2);
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }



***************Example 4************************************************
  int main (void)
  { unsigned long PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x80000000;
    for (int m = 0; m <= 31; m++)
    { One_wire_Tx_2_integers(PORT_1, PORT_2);
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }



*****************Example 5**********************************************
  int main (void)
  { unsigned int PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x8000;
    for (int m = 0; m <= 7; m++)
    { One_wire_Tx_2_integers(PORT_1 | PORT_2,
                             (PORT_1 << 8)  | (PORT_2 >> 8));
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }





******************Example 6*********************************************
  int main (void)
  { unsigned int PORT_1, PORT_2, m = 0, n = 0;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  PORT_2 = 0x8000;
  while (1)
  { One_wire_Tx_2_integers(PORT_1 << m, PORT_2 >> m);
    _delay_ms(30);
    if (!(n)) m += 1;
    if (m == 16)n = 1;
    if (n == 1)m -= 1;
    if (m == 0)n = 0;
  }
  return 1;
  }




******************Example 7*********************************************
  int main (void)
  { unsigned int PORT_1 = 1;
  char m = 1;
  char overflow = 0;

  setup_328_HW;
  while (1)
  { One_wire_Tx_2_integers(PORT_1, ~PORT_1);
    _delay_ms(60);
    if (m <= 5)
    {
      PORT_1 |= (PORT_1 << 1);
      m += 1;
    }
    else PORT_1 = PORT_1 << 1;
    if (overflow)PORT_1 |= 1;
    if (PORT_1 & 0x8000) overflow = 1;
    else overflow = 0;
  }
  }


*****************Example 8**********************************************
  int main (void)
  { unsigned int random_num;
  long PORT_1 = 1, PORT_2 = 1;

  setup_328_HW;
  while (1)
  { random_num = (PRN_16bit_GEN(0)) % 3;
    for (int m = 0; m < random_num; m++)
    { if (!(PORT_1 = ((PORT_1 * 2) % 0x10000)))
        PORT_1 = 1;
    }
    if (!(PORT_2 = ((PORT_2 * 2) % 0x10000)))
      PORT_2 = 1;
    One_wire_Tx_2_integers(PORT_1, PORT_2);
    Timer_T2_10mS_delay_x_m(4);
  }
  }



*****************Example 9**********************************************/
char display_bkp[7];

int main (void)

{ char letter = 0;
  char digit_num = 0;
  char seg_counter = 0;
  char direction = 0;

  setup_328_HW;
  One_wire_Tx_char = 'c';  UART_Tx_1_wire();

  while (1)
  { while (seg_counter < 56) {
      letter = (PRN_16bit_GEN (0) % 7) + 'a';
      digit_num = (PRN_16bit_GEN (0) % 8);
      if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) continue;
      if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) continue;
      One_wire_comms_any_segment(letter, digit_num);
      backup_the_display(letter, digit_num);
      seg_counter += 1;
    }

    direction ^= 1;
    seg_counter = 0;
    _delay_ms(500);
  }
  SW_reset;
  return 1;
}

void backup_the_display(char segment, char digit_num)
{ display_bkp[segment - 'a'] =
    display_bkp[segment - 'a'] ^ (1 << digit_num);
}
