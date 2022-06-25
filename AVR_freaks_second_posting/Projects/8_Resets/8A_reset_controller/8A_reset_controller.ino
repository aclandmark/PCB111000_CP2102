
#define Reset_control_switch_up    (PINC & 0x20)

#define reset_ctl_reg                         0x3FC
#define Signal_flagged_WDTout                 eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0x10)
#define Signal_WDTout_with_interrupt          eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0x20)


#include "8A_reset_controller_header.h"


int main (void){

setup_328_HW_Arduino;
determine_reset_source;

One_25ms_WDT_with_interrupt;

set_up_PCI;
enable_PCI_on_sw1;

switch (reset_status){

case 1: User_prompt;
Serial.write("\r\nProgram running following POR\r\n"); break;
case 2: Serial.write("\r\nProgram triggered by WDTout.\r\n"); break;
case 3: Serial.write("\r\nProgram triggered by the p/r/t/D... user prompt.\r\n"); break;
case 4: Serial.write("\r\nProgram triggered by a flagged WDTout.\r\n"); break;
case 5: Serial.write("\r\nProgram recovery following system crash.\r\n"); break;}

_delay_ms(10);

while(1)wdr();
}


ISR(PCINT2_vect){ 
if (switch_1_up)return;
  sei();
  disable_PCI_on_sw1;
if((switch_2_up) && (switch_3_up));

if((switch_2_down) && (switch_3_up)){
Signal_flagged_WDTout; }

if((switch_2_up) && (switch_3_down))while(1);

SW_reset;}



ISR (WDT_vect){Signal_WDTout_with_interrupt;}

/*******************************************************************************************************************/
