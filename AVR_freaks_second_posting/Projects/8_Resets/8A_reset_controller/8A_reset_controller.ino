
#define Reset_control_switch_up    (PINC & 0x20)

#define reset_ctl_reg                         0x3FC
#define Signal_flagged_WDTout                 eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0x10)
#define Signal_WDTout_with_interrupt          eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0x20)


#include "8A_reset_controller_header.h"
volatile char test;

int main (void){

char copy_of_reset_ctl_reg;

setup_328_HW_Arduino_IO;
//determine_reset_source;

//One_25ms_WDT_with_interrupt;

set_up_PCI;
enable_PCI_on_sw1;
test = 0;
switch (reset_status){

case 1: User_prompt_Arduino;
Serial.write("\r\nProgram running following POR\r\n"); break;
case 2: Serial.write("\r\nProgram triggered by a SW_reset.\r\n"); break;
case 3: Serial.write("\r\nProgram triggered by the p/r/t/D... user prompt.\r\n"); break;
case 4: Serial.write("\r\nProgram triggered by a flagged WDTout.\r\n"); break;}

Char_to_PC_as_binary((byte)copy_of_reset_ctl_reg);
_delay_ms(10);

while(!(test))wdr();
while(1);
return 1;
}


ISR(PCINT2_vect){ 
if (switch_1_up)return;
  sei();
  disable_PCI_on_sw1;
if((switch_2_up) && (switch_3_up));

if((switch_2_down) && (switch_3_up)){
Signal_flagged_WDTout; }

if((switch_2_up) && (switch_3_down))while(1);

if ((switch_2_down) && (switch_3_down)){Serial.write('G');cli(); while(1);}

SW_reset;}



ISR (WDT_vect){Signal_WDTout_with_interrupt;WDTout;}


void Char_to_PC_as_binary(unsigned char num){
  Serial.write("\t\t");
for(int m = 0; m <= 7; m++)
{if (num & (1 << (7 - m)))Serial.write('1'); else Serial.write('0');}}

/*******************************************************************************************************************/
