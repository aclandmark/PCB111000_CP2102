volatile char next_duty_cycle = 1;
char digits[12];


#include "display_FPN_header_with_WDT.h"
float Num_1, Num_2;


int main (void){

float pi = 3.14159;
int print_spaces;
float amplitude;
float duty_cycle;

int num_time_slots;            //50 45
int num_harmonics;             //60 30

setup_328_HW_Arduino_plus;
set_up_PCI;

switch (WDT_out_status)
{case 1: Timer_T1_sub_with_interrupt(T1_delay_250ms);
for(int p = 0; p <10; p++)newline; break;

case 2:Serial.write("\r\n\r\nNumerical result too large for a 32 bit number.\r\n");

case 3: enable_PCI_on_sw1;
 eeprom_write_byte((uint8_t*)(0x0),'1');
 eeprom_write_byte((uint8_t*)(0x1),45); 
 eeprom_write_byte((uint8_t*)(0x2),0); 
 eeprom_write_byte((uint8_t*)(0x3),30); 
 eeprom_write_byte((uint8_t*)(0x4),0);  
 
Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");

Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard
float_to_EEPROM(Num_1, 0x5);

while(1){if((switch_2_down) || (switch_3_down))break; else wdr();}break;}


duty_cycle = (float)(eeprom_read_byte((uint8_t*)(0x0))- '0')/10.0 * 1.5;
num_time_slots = (eeprom_read_byte((uint8_t*)(0x2)) << 8) + eeprom_read_byte((uint8_t*)(0x1));
num_harmonics = (eeprom_read_byte((uint8_t*)(0x4)) << 8) + eeprom_read_byte((uint8_t*)(0x3));

for(int n = 0; n <= 100; n++){if (n<40)Serial.write (' '); else Serial.write('_');}
newline;

while(1)
{for(int m = 1; m; m++)
{amplitude = sin(duty_cycle ) * (cos(pi * (float)m/(float)num_time_slots));
for(int p = 3; p < num_harmonics; p+=2) 
{amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p * (float)m/(float)num_time_slots)/(float) p;wdr();}
print_spaces = 50 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(20);
newline;
if(m == num_time_slots/2) m = -num_time_slots/2;}}

while(1)wdr();}
                                                       

/*******************************************************************************************************************/
ISR(PCINT2_vect){
  int data;
  if (switch_1_up)return;
  sei();
  disable_PCI_on_sw1;
 
if((switch_2_up) && (switch_3_up)){
  if(Serial.available()){eeprom_write_byte((uint8_t*)(0x0),Serial.read());}}
  
 if((switch_2_down) && (switch_3_up)){data = PCI_triggers_data_from_PC(digits);
 eeprom_write_byte((uint8_t*)(0x1),data);
 eeprom_write_byte((uint8_t*)(0x2), (data >> 8));}

if((switch_3_down) && (switch_2_up)){ data = PCI_triggers_data_from_PC(digits);
 eeprom_write_byte((uint8_t*)(0x3),data);
 eeprom_write_byte((uint8_t*)(0x4), (data >> 8));}

if((switch_2_down) && (switch_3_down)){  
Num_1 = float_from_EEPROM(0x5);
Num_2 = pow(Num_1, 1.2);
if(Num_2 == Num_1)while(1);

float_num_to_display_WDT(Num_2);
float_to_EEPROM (Num_2, 0x5);

Timer_T1_sub_with_interrupt(T1_delay_250ms);
return;}

Signal_flaggged__WDTout; 
setup_watchdog; SW_reset;}
  


/*******************************************************************************************************************/
int PCI_triggers_data_from_PC(char * num_as_string)
{char strln;
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
return atoi(num_as_string);}



/*******************************************************************************************************************/
void Timer_T1_sub_with_interrupt(char Counter_speed, unsigned int Start_point){ 
TIMSK1 |= (1 << TOIE1);
TCNT1H = (Start_point >> 8);
TCNT1L = Start_point & 0x00FF;
TCCR1B = Counter_speed;}

ISR(TIMER1_OVF_vect) {TIMSK1 &= (~(1 << TOIE1)); enable_PCI_on_sw1;}



/*******************************************************************************************************************/
void float_num_to_display_WDT(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                             //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){                        //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                       //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;
wdr();}
reinstate_pin_change_interrupt_on_PC5;}




/*******************************************************************************************************************/
void float_to_EEPROM(float num, int address){
char * Char_ptr_local;

Char_ptr_local = (char*)&num;
for (int m = 0; m <= 3; m++){
eeprom_write_byte((uint8_t*)(address++), *(Char_ptr_local++));}}



/*******************************************************************************************************************/
float float_from_EEPROM(int address){
float num;
float * Flt_ptr_local;
char * Char_ptr_local;

Flt_ptr_local = &num;
Char_ptr_local = (char*)&num;
 
for (int m = 0; m <= 3; m++){
*(Char_ptr_local++) = eeprom_read_byte((uint8_t*)(address++));}
num =  * Flt_ptr_local;
return num;}


ISR (WDT_vect){
  Signal_WDTout_with_interrupt;}






/*******************************************************************************************************************/
