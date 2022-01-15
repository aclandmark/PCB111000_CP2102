
#include "UART_timer_interrupt_header.h"

int m, num_leds;
int num_leds_new = 8;
unsigned int PORT_1, PORT_2;

int main (void)
{ unsigned long counter = 1;
  unsigned long counter_squared;

  setup_328_HW;
  reset_display;
  sei();
  UCSR0B |= (1 << RXCIE0);
  T1_100ms_clock_tick();
  while (1)
  {
    do_some_arithmetic;
  }
}


ISR(TIMER1_OVF_vect)
{ UCSR0B &= (~(1 << RXCIE0));
  if (num_leds != num_leds_new)
  {
    reset_display;
  }
  TCNT1 = 0xCF2C;
  if (m < num_leds)
  { PORT_2 = (PORT_2 << 1) | 1;
    PORT_1 = PORT_1 & (~(1 << m));
  }
  else
  { PORT_2 = (PORT_2 >> 1);
    PORT_1 |= (1 << (num_leds * 2 - m - 1));
  }
  for (int m = 15; m >= num_leds; m--)
    PORT_1 &= ~(1 << m);
  sei(); One_wire_Tx_2_integers(PORT_1, PORT_2);
  m += 1;
  if (m == num_leds * 2)m = 0;
  UCSR0B |= (1 << RXCIE0);
}



void T1_100ms_clock_tick(void)
{ TCNT1 = 0xCF2C;
  TIMSK1 |= (1 << TOIE1);
  TCCR1B = 0x03;
}



ISR(USART_RX_vect)
{ switch (Char_from_PC())
  { case '2':   num_leds_new = 2; break;
    case '4':   num_leds_new = 4; break;
    case '6':   num_leds_new = 6; break;
    case '8':   num_leds_new = 8; break;
    case 'A':   num_leds_new = 10; break;
    case 'C':   num_leds_new = 12; break;
    case 'E':   num_leds_new = 14; break;
    case '0':   num_leds_new = 16; break;
  }
}
