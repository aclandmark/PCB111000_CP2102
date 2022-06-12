
/**************Proj_5D_Acquire_and process_Data_from_the _KBD********************/

/*
Here we leave the mini_OS (the Attiny1606) to deal with all the details of displaying a number.
We can use one_wire_comms to send it a string or binary number.
If we send it a string then it will return the number in binary form.

Obviouly Arduino do not supply library functions to drive the display and therefore a
bit of DIY programming is required.
*/

volatile char next_duty_cycle = 1;
char digits[12];


#include "display_FPN_header_with_WDT.h"
float Num_1;

int main (void){


float pi = 3.14159;
int print_spaces;
float amplitude;
float duty_cycle;

int num_time_slots;            //50 45
int num_harmonics;             //60 30

setup_328_HW_Arduino_plus;
set_up_PCI;

wdt_enable(WDTO_120MS);

if(WDT_out_status == 2){Timer_T1_sub_with_interrupt(T1_delay_250ms);
for(int p = 0; p <10; p++)newline;}


if(WDT_out_status == 1){Serial.write('A');
enable_PCI_on_sw1;
 eeprom_write_byte((uint8_t*)(0x0),'1');
 eeprom_write_byte((uint8_t*)(0x1),45); 
 eeprom_write_byte((uint8_t*)(0x2),0); 
 eeprom_write_byte((uint8_t*)(0x3),30); 
 eeprom_write_byte((uint8_t*)(0x4),0);  
 
Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");

Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard
waitforkeypress_with_WDT;}

duty_cycle = (float)(eeprom_read_byte((uint8_t*)(0x0))- '0')/10.0 * 1.5;
num_time_slots = (eeprom_read_byte((uint8_t*)(0x2)) << 8) + eeprom_read_byte((uint8_t*)(0x1));
num_harmonics = (eeprom_read_byte((uint8_t*)(0x4)) << 8) + eeprom_read_byte((uint8_t*)(0x3));


for(int n = 0; n <= 100; n++){if (n<40)Serial.write (' '); else Serial.write('_');}
newline;
while(1){

for(int m = 1; m; m++)
{
amplitude = sin(duty_cycle ) * (cos(pi * (float)m/(float)num_time_slots));
for(int p = 3; p < num_harmonics; p+=2) 
{amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p * (float)m/(float)num_time_slots)/(float) p;}
print_spaces = 50 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(20);
newline;
if(m == num_time_slots/2) m = -num_time_slots/2;
wdr();}
}




while(1)wdr();}
                                                        //Generates reset if result of arithmetic is too large or smallSW_reset;}


ISR(PCINT2_vect){
  int data;
  if (switch_1_up)return;
  sei();
  disable_PCI_on_sw1;
 Signal_WDTout_with_interrupt; 
 
if((switch_2_up) && (switch_3_up)){
  if(Serial.available()){eeprom_write_byte((uint8_t*)(0x0),Serial.read());}}
  
 if((switch_2_down) && (switch_3_up)){data = PCI_triggers_data_from_PC(digits);
 eeprom_write_byte((uint8_t*)(0x1),data);
 eeprom_write_byte((uint8_t*)(0x2), (data >> 8));}

if((switch_3_down) && (switch_2_up)){ data = PCI_triggers_data_from_PC(digits);
 eeprom_write_byte((uint8_t*)(0x3),data);
 eeprom_write_byte((uint8_t*)(0x4), (data >> 8));}
 
  clear_display;
  SW_reset;}
  



int PCI_triggers_data_from_PC(char * num_as_string)
{char strln;
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
return atoi(num_as_string);
//eeprom_write_byte((uint8_t*)(0x1),atoi(num_as_string));
}


void Timer_T1_sub_with_interrupt(char Counter_speed, unsigned int Start_point){ 
TIMSK1 |= (1 << TOIE1);
TCNT1H = (Start_point >> 8);
TCNT1L = Start_point & 0x00FF;
TCCR1B = Counter_speed;}


ISR(TIMER1_OVF_vect) {TIMSK1 &= (~(1 << TOIE1)); enable_PCI_on_sw1;}



/*ISR(PCINT2_vect){sei();
disable_PCI_on_sw1_and_sw2;
if(switch_1_down){
Sc_Num_to_PC(Num_1,1,5 ,'\r');
Num_1 = pow(Num_1, 1.2);                                  //Do some arithmetic
float_num_to_display(Num_1);                              //Sends result to the display
} 
if(switch_2_down){while(1);}
while(switch_3_up)wdr();
enable_PCI_on_sw1_and_sw2;}                              //Generates reset if result of arithmetic is too large or small
*/



/*
//{print_spaces = 200 + (10 * (int)((for(int p = 1; p < 10; p++) sin(pi*float(p)) * (float)m/100.0;)));
//for (int n = 0; n < print_spaces; n++){Serial.write(' ');} 
 
 */

/*for(int m = 1; m <= 400; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 2; p < 80; p++) {if (p%2) amplitude += sin(pi*(float)p * (float)m/100.0)/(float) p; 
else  amplitude -= sin(pi*(float)p * (float)m/100.0)/(float) p;}


for(int p = 1; p < 80; p++) {if (p%2) amplitude -= sin(pi*(float)p * (float)(m+10)/100.0)/(float) p; 
else  amplitude += sin(pi*(float)p * (float)(m+10)/100.0)/(float) p;}

print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');
//_delay_ms(10);
newline;}*/

/*duty_cycle = 0.1 * 1.5;
while(1){
for(int m = -25; m < 25; m++){amplitude = sin(duty_cycle ) * (cos(pi * (float)m/50.0));
for(int p = 3; p < 40; p+=2) {amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p * (float)m/50.0)/(float) p;}
print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');//_delay_ms(10);
newline;}
if(Serial.available()){duty_cycle = (float)(Serial.read()- '0')/10.0 * 1.5;}}
*/

/**********Square wave***********************/
/*for(int m = 1; m <= 400; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 3; p < 80; p+=2) {amplitude += sin(pi*(float)p * (float)m/100.0)/(float) p;}
print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;}*/

/**********Saw tooth***********************/
/*for(int m = 1; m <= 400; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 2; p < 80; p++) {if (p%2) amplitude += sin(pi*(float)p * (float)m/100.0)/(float) p; 
else  
amplitude -= sin(pi*(float)p * (float)m/100.0)/(float) p;}

print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;}*/



/*
for(int m = 1; m <= 200; m++){
print_spaces = 200 + (int)(10.0 * (sin(pi*(float)m/100.0) + sin(2.0 * pi*(float)m/100.0) + sin(3.0 * pi*(float)m/100.0) + sin(4.0 * pi*(float)m/100.0) + sin(5.0 * pi*(float)m/100.0) + sin(6.0 * pi*(float)m/100.0) + sin(7.0 * pi*(float)m/100.0) + sin(8.0 * pi*(float)m/100.0)));  

for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;
//Unsigned_Int_to_PC(print_spaces, digits, '\r');
}*/

/*for(int m = 1; m <= 100; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 2; p < 20; p++) amplitude += sin(pi*(float)p * (float)m/100.0);  
print_spaces = 200 + (int)(10.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;}*/



/************Pulse wave*********************/
/*duty_cycle = 0.1 * 1.5;
while(1){
for(int m = -num_time_slots/2; m < num_time_slots/2; m++)
//for(int m = 1; m <= num_time_slots; m++)
{amplitude = sin(duty_cycle ) * (cos(pi * (float)m/(float)num_time_slots));
for(int p = 3; p < num_harmonics; p+=2) 
{amplitude += sin(duty_cycle * (float)p) * cos(pi*(float)p * (float)m/(float)num_time_slots)/(float) p;}
print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);
newline;}
if(Serial.available()){duty_cycle = (float)(Serial.read()- '0')/10.0 * 1.5;}}*/
