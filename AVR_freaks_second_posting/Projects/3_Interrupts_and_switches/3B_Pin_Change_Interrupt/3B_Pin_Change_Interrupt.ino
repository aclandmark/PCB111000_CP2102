/*
 Target practice:
 In this example a basic LED driver routine runs in the for ground.
 The user operates user switch SW2 to shoot the LEDs down.
 
 Note SW2 is connected to a pin on the Atmega328 that is configured as input.
 When SW2 is pressed the voltage level on the pin changes from 5V to zero volts.
 A Pin Change Interrrupt (PCI) is generated.
 */



#include "Pin_Change_Interrupt_header.h"

unsigned int PORT_1;
char scan;           
char switch_control; 
volatile unsigned int mask;

int main (void)
{ setup_328_HW;
  set_up_PCI_on_sw2;
  enable_pci_on_sw2;

  mask = 0xFFFF;
  
  while (mask)
  { scan = 1;
    PORT_1 = 1;
    while (scan)
    { if (PORT_1 == 1)switch_control = 0;
      One_wire_Tx_2_integers
      (PORT_1 & mask, (~mask) ^ PORT_1);
      Timer_T2_10mS_delay_x_m(2);
      if (PORT_1 & 0x8000)scan = 0;
      else
        PORT_1 = (PORT_1 << 1);
    }
  }
  One_wire_Tx_2_integers(0, 0xFFFF);
  Timer_T2_10mS_delay_x_m(200);
  SW_reset;
}



ISR(PCINT2_vect)
{ if (switch_2_up)return;
  if (switch_control) return;
  if (mask & PORT_1)
  { mask &= ~PORT_1;
    scan = 0;
  }
  switch_control = 1;
}
