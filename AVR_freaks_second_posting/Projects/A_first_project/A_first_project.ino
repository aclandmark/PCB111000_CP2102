
#include "First_project_header.h"




/*****************Example 1**********************************************/
int main (void) {
  unsigned int PORT_1;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  for (int m = 0; m <= 15; m++) {
    One_wire_Tx_2_integers(PORT_1, PORT_1);
    _delay_ms(30);
    PORT_1 = PORT_1 << 1;
  }
  SW_reset;
  return 1;
}




/**************Example 2*************************************************
  int main (void) {
  unsigned int PORT_1, m = 0, n = 0;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  while (1) {
    One_wire_Tx_2_integers(PORT_1 << m, PORT_1 << m);
    _delay_ms(30);
    if (!(n)) m += 1; if (m == 16)n = 1; if (n == 1)m -= 1;
    if (m == 0)n = 0;
  }
  return 1;
  }




  /***************Example 3************************************************
  int main (void) {
  unsigned int PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1) {
    PORT_1 = 1;
    PORT_2 = 0x8000;
    for (int m = 0; m <= 15; m++) {
      One_wire_Tx_2_integers(PORT_1, PORT_2);
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }




***************Example 4************************************************
  int main (void) {
  unsigned long PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1) {
    PORT_1 = 1;
    PORT_2 = 0x80000000;
    for (int m = 0; m <= 31; m++) {
      One_wire_Tx_2_integers(PORT_1, PORT_2);
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }




  *****************Example 5**********************************************
  int main (void) {
  unsigned int PORT_1, PORT_2;

  setup_328_HW;
  sei();
  while (1) {
    PORT_1 = 1;
    PORT_2 = 0x8000;
    for (int m = 0; m <= 7; m++) {
      One_wire_Tx_2_integers(PORT_1 | PORT_2,
                             (PORT_1 << 8)  | (PORT_2 >> 8));
      _delay_ms(30);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }
  }
  return 1;
  }




******************Example 6*********************************************
  int main (void) {
  unsigned int PORT_1, PORT_2, m = 0, n = 0;

  setup_328_HW;
  sei();
  PORT_1 = 1;
  PORT_2 = 0x8000;
  while (1) {
    One_wire_Tx_2_integers(PORT_1 << m, PORT_2 >> m);
    _delay_ms(30);
    if (!(n)) m += 1;
    if (m == 16)n = 1;
    if (n == 1)m -= 1;
    if (m == 0)n = 0;
  }
  return 1;
  }




******************Example 7*********************************************
  int main (void) {
  unsigned int PORT_1 = 1;
  char m = 1;
  char overflow = 0;

  setup_328_HW;
  while (1) {
    One_wire_Tx_2_integers(PORT_1, ~PORT_1);
    _delay_ms(60);
    if (m <= 5) {
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
  int main (void) {
  unsigned int random_num;
  long PORT_1 = 1, PORT_2 = 1;

  setup_328_HW;
  while (1) {
    random_num = (PRN_16bit_GEN(0)) % 3;
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

*****************************************************************/
