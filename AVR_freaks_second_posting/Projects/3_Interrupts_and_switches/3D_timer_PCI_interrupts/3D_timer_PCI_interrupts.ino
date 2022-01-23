#include "Timer_PCI_header.h"
volatile char T1_OVF;
unsigned int n, n_max;
long PORT_1, PORT_2;
char p = 0;
char mode = 1;

int main (void)
{ setup_328_HW;
  mode = eeprom_read_byte((uint8_t*)0);
  switch (mode)
  { case 0: case 1: case 2: break;
    default: mode = 0; break;
  }
  set_up_PCI;
  enable_PCI;
  T1_OVF = 0;
  sei();
  T1_100ms_clock_tick();
  initialise_display();
  while (1)
  { while (!(T1_OVF)); T1_OVF = 0;
    Inc_Display();
  }
}

ISR(TIMER1_COMPA_vect)
{
  OCR1A += 0x30D4;
  T1_OVF = 1;
}

ISR(PCINT2_vect)
{ if ((switch_1_up) && (switch_2_up) && (switch_3_up)) {
    return;
  }
  if (switch_1_down) eeprom_write_byte((uint8_t*)0x0, 0);
  if (switch_2_down) eeprom_write_byte((uint8_t*)0x0, 1);
  if (switch_3_down) eeprom_write_byte((uint8_t*)0x0, 2);
  SW_reset;
}

void T1_100ms_clock_tick(void)
{ TCNT1 = 0;
  OCR1A = 0x30D4;
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B = 0x03;
}

void initialise_display()
{ n = 1;
  PORT_1 = 1;
  PORT_2 = 0x8000;
  switch (mode)
  { case 0: n = 0; PORT_1 = 1 << p;
      PORT_2 = 0x8000 >> p; n_max = 16 - (2 * p); break;
    case 1:  n_max = 17; break;
    case 2: n_max = 16; break;
  }
  //sei();
  One_wire_Tx_2_integers(PORT_1, PORT_2);
}


void Inc_Display()
{ switch (mode)
  { case 0: PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1; break;

    case 1:
      if (n < 8)
      { PORT_1 |= (1 << (2 * n));
        PORT_2 |= (0x8000 >> (2 * n));
      }
      else
      { PORT_1 = PORT_1 << 2;
        PORT_2 = PORT_2 >> 2;
      } break;

    case 2: if (n < 5)
      { PORT_1 |= PORT_1 << 1;
        PORT_2 |= PORT_2 >> 1;
      }
      else
      { PORT_1 = PORT_1 << 1;
        PORT_2 = PORT_2 >> 1;
      } break;
  }
  One_wire_Tx_2_integers(PORT_1, PORT_2);
  n += 1;
  if (n == n_max)
  {
    n = 0;
    p += 1;
    p = p % 8;
    initialise_display();
  }
}
