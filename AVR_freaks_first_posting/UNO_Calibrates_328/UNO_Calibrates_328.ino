
 
/*
Calibrating the Atmega 328
UNO generates PCI on PB5 every 8.192mS
Target 328 clock is 8 MHz
TCCR1B = 1 << CS11; gives /8 prescaling ie 1MHz clock
T1 counts to 8192 between pin changes
*/


#include "Project_header.h"

unsigned char OSCCAL_default;                                  //Factory calibration value (usually enables comms with PC)
unsigned char OSCCAL_2_percent;                                //Calibration accuracy of betwee 1% and 2%
unsigned char OSCCAL_test;                                     //Takes on values of between 15 and 240
unsigned char OSCCAL_previous;


int main(void)
{char keypress;
unsigned char User_cal;                                        //User enters the value following calibration
 
long error = 0;                                                 //Calibration error
char error_percent = 0;

setup_328_HW;                                                   //Sets watchdog IO and UART
sei();

OSCCAL_default = OSCCAL;                                        //Default value provided by the chip
OSCCAL_2_percent = OSCCAL;                                      //Interim value of OSCCAL guaranteed to enable PC comms
OSCCAL_test = 14;                                               //Test values OSCCAL starting with 15 and ending with 240

while(1){OSCCAL_test += 1;
error_percent = 
measure_cal_error(OSCCAL_default, OSCCAL_test, &error);         //Returns actual error and percentage error 
if ((error_percent <= 1) && (error_percent >= -1))break;} 
OSCCAL_2_percent = OSCCAL_test;                                 //Save OSCCAL giving and error of between 1 and 2%

Serial.write("\r\nOSCCAL\t Error\t%error\tTCNT1\r\n");
_delay_ms(10);                                                  //Complete printing before changong OSCCAL

for (int m = OSCCAL_2_percent; m <= 225; m++){                  //Continue testing OSCCAL values
OSCCAL_test = m;
error_percent = 
measure_cal_error(OSCCAL_2_percent, OSCCAL_test, &error);        //Pointer enables two values to be returned
if ((error_percent <= 1) && (error_percent >= -1))              //Print out results giving an error of < 2%
{print_cal_result(OSCCAL_test, error, error_percent);}
 OSCCAL_test += 1;}                                              //Next value of OSCCAL
 
User_cal = 0;
Serial.write("\r\rUser cal? Terminate with -cr-");

User_cal = Int_from_KBD();

if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {
OSCCAL_previous = eeprom_read_byte((uint8_t*)0x3FF);}
else OSCCAL_previous = 0;

eeprom_write_byte((uint8_t*)0x3FF, User_cal);                      //Save user cal in EEPROM 
eeprom_write_byte((uint8_t*)0x3FE, User_cal);
eeprom_write_byte((uint8_t*)0x3FD, OSCCAL_default);                 //Save default OSCCAL in EEPROM

Serial.write("\r\nSaved to EEPROM");

OSC_CAL;                                                            //Retrieves OSCCAL value from EEPROM

error_percent = measure_cal_error(OSCCAL, OSCCAL, &error);          //Check error values and 
print_cal_result(OSCCAL, error, error_percent);                     //print the out

Serial.write("\r\n\r\nDefault value of OSCCAL is\t   ");
Serial.print(OSCCAL_default);
_delay_ms(5);                                                       //Required to complete printing

if(OSCCAL_previous){
Serial.write("\r\nPrevious value of OSCCAL was  ");
Serial.print(OSCCAL_previous);
_delay_ms(5);}

return 1;}




/************************************************************************************************/
char measure_cal_error(unsigned char OSCCAL_OK, unsigned char OSCCAL_test, long * error ){

OSCCAL = OSCCAL_test; 

TCNT1 = 0;
while (!(PINB & (1 << PINB5)));                             //wait while low
while (PINB & (1 << PINB5));                                //wait while high
TCCR1B |= (1 << CS11);                                      //start T1
while (!(PINB & (1 << PINB5)));                             //wait while low
TCCR1B &= (~(1 << CS11));

OSCCAL = OSCCAL_OK;                                         //Gives error of < 2%
*error = long((signed(TCNT1 - 8192)));                      //Note: strict use of casting is enforced
return 100 * long((signed(TCNT1 - 8192))) / 8192;}



/************************************************************************************************/
void print_cal_result(unsigned char OSCCAL_test, long error, char percent) {
Serial.write("\r\n");                                         //Sends askii chars
Serial.print(OSCCAL_test);                                    //Sends number as askii string
Serial.write("\t   ");
Serial.print(error);
Serial.write("\t      ");
Serial.print(int(percent));                                   //Sends char variable as askii char
Serial.write("\t");
Serial.print(TCNT1);
_delay_ms(5);}
