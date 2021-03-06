
/*
Interrupts enable several process to run at the same time.
Here the main task is to do some simple arithmetic and send the results to the PC
However a timer interrup that occcurs every 100ms is used to drive the LED display.
Code to setup a keypress interrupt is also given.  This enables the user to adjust 
the display.

When an interrupt occurs program coontrol jumps to the Interrupt Serice Routine (ISR)

*/



#include "UART_timer_interrupt_header.h"

int m, num_leds = 8;
unsigned int PORT_1, PORT_2;

int main (void)
{ unsigned long counter = 1;
  unsigned long counter_squared;

  setup_328_HW_Basic_IO;
  reset_display;
  
  UCSR0B |= (1 << RXCIE0);
  T1_100ms_clock_tick();
  while (1)
  {
    do_some_arithmetic;
    _delay_us(50);
  }
}



ISR(TIMER1_COMPA_vect)
{ UCSR0B &= (~(1 << RXCIE0));wdr();
  TCNT1 = 0;
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
{ TCNT1 = 0;
OCR1A = 12500;
  TIMSK1 |= (1 <<  OCIE1A);
  TCCR1B = 0x03;
}



ISR(USART_RX_vect)
{ switch (Char_from_PC_Basic())
  { case '2':   num_leds = 2; break;
    case '4':   num_leds = 4; break;
    case '6':   num_leds = 6; break;
    case '8':   num_leds = 8; break;
    case 'A':   num_leds = 10; break;
    case 'C':   num_leds = 12; break;
    case 'E':   num_leds = 14; break;
    case '0':   num_leds = 16; break;
  }
  reset_display;
}





void Num_to_PC_Basic (long number)
{ int i = 0;
  char s[12];
  
  do
  { s[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)Char_to_PC_Basic(s[m - 1]);
  Char_to_PC_Basic(' ');
}




/***************************************************************************************************/
