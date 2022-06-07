
/**************Proj_5D_Acquire_and process_Data_from_the _KBD********************/

/*
Here we leave the mini_OS (the Attiny1606) to deal with all the details of displaying a number.
We can use one_wire_comms to send it a string or binary number.
If we send it a string then it will return the number in binary form.

Obviouly Arduino do not supply library functions to drive the display and therefore a
bit of DIY programming is required.
*/

volatile char next_duty_cycle = 1;

#include "display_FPN_header_with_WDT.h"
float Num_1;

int main (void){

char digits[12];
float pi = 3.14159;
int print_spaces;
float amplitude;
float duty_cycle;
int num_time_slots = 25;         //50
int num_harmonics = 30;           //60

setup_328_HW_Arduino;
set_up_PCI;
enable_PCI_on_sw1_and_sw2;

Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");
//wdt_enable(WDTO_120MS);

Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard
waitforkeypress();


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

/**********Saw tooth***********************/
/*for(int m = 1; m <= 400; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 2; p < 80; p++) {if (p%2) amplitude += sin(pi*(float)p * (float)m/100.0)/(float) p; 
else  
amplitude -= sin(pi*(float)p * (float)m/100.0)/(float) p;}

print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;}*/

/**********Square wave***********************/
/*for(int m = 1; m <= 400; m++){amplitude = sin(pi * (float)m/100.0); 
for(int p = 3; p < 80; p+=2) {amplitude += sin(pi*(float)p * (float)m/100.0)/(float) p;}
print_spaces = 200 + (int)(100.0 * amplitude);
for (int n = 0; n < print_spaces; n++){Serial.write(' ');}
Serial.write('|');_delay_ms(10);newline;}*/

/************Pulse wave*********************/
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


duty_cycle = 0.1 * 1.5;
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
if(Serial.available()){duty_cycle = (float)(Serial.read()- '0')/10.0 * 1.5;}
}



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






while(1)wdr();}
                                                        //Generates reset if result of arithmetic is too large or smallSW_reset;}


ISR(PCINT2_vect){sei();
disable_PCI_on_sw1_and_sw2;
if(switch_1_down){
Sc_Num_to_PC(Num_1,1,5 ,'\r');
Num_1 = pow(Num_1, 1.2);                                  //Do some arithmetic
float_num_to_display(Num_1);                              //Sends result to the display
} 
if(switch_2_down){while(1);}
while(switch_3_up)wdr();
enable_PCI_on_sw1_and_sw2;}                              //Generates reset if result of arithmetic is too large or small




/*
//{print_spaces = 200 + (10 * (int)((for(int p = 1; p < 10; p++) sin(pi*float(p)) * (float)m/100.0;)));
//for (int n = 0; n < print_spaces; n++){Serial.write(' ');} 
 
 */
