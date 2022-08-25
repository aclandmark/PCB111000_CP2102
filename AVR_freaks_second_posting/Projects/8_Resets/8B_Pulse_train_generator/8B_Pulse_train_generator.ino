
/*
Program synthesises a pulse waveform on the PC screen and also does some floating point arithmetic.
Floating point results of zero or infinity cause the program to crash and trigger a WDTout with interrupt
Switch presses are used to start the waveform adjust its parameters and trigger the FP arithmetic.
A SW_reset is triggered after 25 uninterrupted waveform cycles.
 */


#include "Pulse_train_generator_header.h"

float Num_1, Num_2;
char digits[12];

int main (void){

float pi = 3.14159;
int print_spaces;
float amplitude;
float duty_cycle;

int num_time_slots;            //45
int num_harmonics;             //30

setup_328_HW_Arduino_IO;

set_up_PCI;

switch (reset_status)
{case 4: Timer_T1_sub_with_interrupt(T1_delay_250ms);                                       //Flagged WDTout
for(int p = 0; p <10; p++)newline; break;

case 5:Serial.write("\r\n\r\nNumerical result too large for a 32 bit number.\r\n");         //WDTout with interrupt
case 2:                                                                                     //SW_reset
case 3:                                                                                     //Post prtD
 eeprom_write_byte((uint8_t*)(0x0),1);                                                      //1 to 9 gives mark space ratio
 eeprom_write_byte((uint8_t*)(0x1),45);                                                     //Waveform period < 65536
 eeprom_write_byte((uint8_t*)(0x2),0); 
 eeprom_write_byte((uint8_t*)(0x3),30);                                                     //Number of harmonics
 eeprom_write_byte((uint8_t*)(0x4),0);  
 
Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");

Num_1 = Float_KBD_to_display(digits); 
float_to_EEPROM(Num_1, 0x5);

while(1){if((switch_2_down) || (switch_3_down))break; else wdr();}
enable_PCI_on_sw1;break;}                                                                 //Press switch 2 or 3 to start

duty_cycle = (float)(eeprom_read_byte((uint8_t*)(0x0)))/10.0 * 1.5;
num_time_slots = (eeprom_read_byte((uint8_t*)(0x2)) << 8) +
eeprom_read_byte((uint8_t*)(0x1));
num_harmonics = (eeprom_read_byte((uint8_t*)(0x4)) << 8) +
eeprom_read_byte((uint8_t*)(0x3));

for(int n = 0; n <= 100; n++){if (n<40)Serial.write (' '); 
else Serial.write('_');}
newline;


{int counter = 0;                                               
while(counter < 25)                                                           //Exit after 25 cycles without interrupt
{for(int m = 1; m; m++)                                                       //Calculate amplitude for every time slot (m). Exit when m is zero

{amplitude = sin(duty_cycle ) *
(cos(pi * (float)m/(float)num_time_slots));                                   //Calculation for the fundamental

for(int p = 3; p < num_harmonics; p+=2)                                       //Add in odd harmonics

{amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p
* (float)m/(float)num_time_slots)/(float) p; 
wdr();}

print_spaces = 50 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(20);
newline;wdr();

if(m == num_time_slots/2) m = -num_time_slots/2;} counter += 1;}}


Serial.write("\r\nTimed out: Reset initiated\r\n");
setup_watchdog; SW_reset;}


                                                       

/*******************************************************************************************************************/
ISR(PCINT2_vect){
  int data;
  if (switch_1_up)return;
  sei();
  disable_PCI_on_sw1;



if((switch_2_down) && (switch_3_down)){                                 //Do some arithmetic
Num_1 = float_from_EEPROM(0x5);
Num_2 = pow(Num_1, 1.2);
if(Num_2 == Num_1)while(1);

float_num_to_display_WDT(Num_2);
float_to_EEPROM (Num_2, 0x5);

Timer_T1_sub_with_interrupt(T1_delay_250ms);
return;}


data = PCI_triggers_data_from_PC(digits);
if(!(data)){Timer_T1_sub_with_interrupt(T1_delay_250ms);return;} 

if((switch_2_up) && (switch_3_up)){                               //Set duty cycle
if(data > 9)data = data%10 + 1;
eeprom_write_byte((uint8_t*)(0x0),data);}
    
 if((switch_2_down) && (switch_3_up))                             //Set period
 {eeprom_write_byte((uint8_t*)(0x1),data);
 eeprom_write_byte((uint8_t*)(0x2), (data >> 8));}

if((switch_3_down) && (switch_2_up))                               //Set number of harmonics
{ eeprom_write_byte((uint8_t*)(0x3),data); 
 eeprom_write_byte((uint8_t*)(0x4), (data >> 8));}


Signal_flagged_WDTout;                                            //Return after requesting new waveform
setup_watchdog; SW_reset;}
  



/*******************************************************************************************************************/
ISR(TIMER1_OVF_vect) {TIMSK1 &= (~(1 << TOIE1)); enable_PCI_on_sw1;}


ISR (WDT_vect){
  Signal_WDTout_with_interrupt;}






/*******************************************************************************************************************/



/*
 {int counter = 0;                                               
while(counter < 25)                                                           //Exit after 25 cycles without interrupt
{for(int m = 1; m; m++)                                                       //Calculate amplitude for every time slot (m). Exit when m is zero

{amplitude = sin(duty_cycle ) *
(cos(pi * (float)m/(float)num_time_slots));

for(int p = 3; p < num_harmonics; p+=2) 

{amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p
* (float)m/(float)num_time_slots)/(float) p; 
wdr();}

print_spaces = 50 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(20);
newline;wdr();

if(m == num_time_slots/2) m = -num_time_slots/2;} counter += 1;}}
*/
