
/*
 Vey similar to Proj 3B.  
 Press sw2 when the led bars line up to make the display flash
 */

#include "Reaction_time_tester_header.h"

int main (void)
{ unsigned int Random_num;
  unsigned int PORT_1, PORT_2;

 setup_328_HW_Basic_IO;
  while (switch_2_up)wdr();

  PORT_1 = 1;
  PORT_2 = 0x8000;
  while (1)
  { while (1)
    { Timer_T2_10mS_delay_x_m(1);
      while (switch_2_up)wdr();

      shift_PORT_1;
      shift_PORT_2;
      One_wire_Tx_2_integers(PORT_1, PORT_2);

      if (PORT_1 == PORT_2)
      { Timer_T2_10mS_delay_x_m(35);
        if (switch_2_up)break;
        else while (switch_2_down)wdr();
      }

      if (PORT_1 != PORT_2)
      {
        Timer_T2_10mS_delay_x_m(8);
      }
    }

    while (switch_2_up)
    {
      flash_display;
    }
  }
}
