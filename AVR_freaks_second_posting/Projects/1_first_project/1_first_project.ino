
#include "First_project_header.h"


int main (void)                          //Example 8
{ unsigned int random_num;
  unsigned char PRN_counter;
  long PORT_1 = 1, PORT_2 = 1;
  
  setup_328_HW;  
  PRN_counter = 0;
  random_num = PRN_16bit_GEN (0, &PRN_counter);
  while (1)
  { for (int m = 0; m < random_num % 3; m++)
    { if (!(PORT_1 = ((PORT_1 * 2) % 0x10000)))
        PORT_1 = 1;
    }
    if (!(PORT_2 = ((PORT_2 * 2) % 0x10000)))PORT_2 = 1;
    One_wire_Tx_2_integers(PORT_1, PORT_2);
    Timer_T2_10mS_delay_x_m(4);
    random_num = PRN_16bit_GEN (random_num, &PRN_counter);
  }
}


/***********************************************************************

  Use this area for saving the examples when they have been got working and finished with
  Use the space above for the active program (the one eing worked on)

  int main (void)                          //Example 1
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
  }



  int main (void)                          //Example 2
  { unsigned int PORT_1, m = 0, n = 0;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  while (1)
  { One_wire_Tx_2_integers(PORT_1 << m, PORT_1 << m);
    _delay_ms(30);
    if (!(n))m += 1;
    if (m == 16)n = 1;
    if (n == 1)m -= 1;
    if (m == 0)n = 0;
  }
  return 1;
  }




 ***************Example 3************************************************
  int main (void)                          //Example 3
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
  int main (void)                          //Example 4
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
  int main (void)                          //Example 5
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
  int main (void)                          //Example 6
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




******************Example 7********************************************
  int main (void)                          //Example 7
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




*****************Example 9**********************************************
  char display_bkp[7];

  int main (void)

  { char letter = 0;
  char digit_num = 0;
  char seg_counter = 0;
  char direction = 0;
  unsigned int PRN;
  unsigned char PRN_counter;

  setup_328_HW;
  clear_display;

  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);

  while (1)
  { while (seg_counter < 56) {
      letter = (PRN % 7) + 'a';
      PRN = PRN_16bit_GEN (PRN, &PRN_counter);
      digit_num = (PRN % 8);
      if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) {PRN_counter -= 1; continue;}
      if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) {PRN_counter -= 1; continue;}
      One_wire_comms_any_segment(letter, digit_num);
      backup_the_display(letter, digit_num);
      seg_counter += 1;
     Timer_T2_10mS_delay_x_m(4);
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



*****************Example 10**********************************************
  int main (void)
  {unsigned int PRN;
  unsigned char PRN_counter;

  setup_328_HW;
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
  sei();
  while(1)
  {PRN = PRN_16bit_GEN (PRN, &PRN_counter);
  One_wire_Tx_2_integers(PRN, (PRN<<((PRN%2) + 1)));
  Timer_T2_10mS_delay_x_m(10);}}

**************************************************************************/
