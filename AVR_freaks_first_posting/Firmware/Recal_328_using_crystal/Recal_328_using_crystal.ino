
 
/*
328_Recall Routine uses watch crystalas time standard
It uses two timers T1 and T2.
T1 and clocked at 1MHz using the internal 8HMz RC clock.
T2 is clocked using a 32.768KHz watch crystal.

T2 counts from zero to 255 and overflows every 7.8125mS during which time T1 counts 
up to 7,812 if the RC clock is running at exactly 8MHz.  OSCCAL is adjusted until the error is 1% or less.

*/


#include "Project_header.h"

unsigned char OSCCAL_default;                                  //Factory calibration value (usually enables comms with PC)
unsigned char OSCCAL_2_percent;                                //Calibration accuracy of betwee 1% and 2%
unsigned char OSCCAL_test;                                     //Takes on values of between 15 and 240
unsigned char OSCCAL_previous;

//int TCNT1_BKP;

int main(void)
{char keypress;
unsigned char User_cal;                                        //User enters the value following calibration
 
long error = 0;                                                 //Calibration error
char error_percent = 0;

 
setup_328_HW;                                                   //Sets watchdog IO and UART
initialise_crystal;
sei();

OSCCAL_default = OSCCAL;                                        //Default value provided by the chip
OSCCAL_2_percent = OSCCAL;                                      //Interim value of OSCCAL guaranteed to enable PC comms
OSCCAL_test = 14;                                               //Test values OSCCAL starting with 15 and ending with 240


/***********Plot OSCCAL againt error using watch crystal as standard***************
for(int m = 15; m <= 245; m++){
error_percent = 
measure_cal_error(OSCCAL_default, m, &error);
print_cal_result(m, error, error_percent);
_delay_ms(20);
}while(1);
***********************************************************************************/


while(1){OSCCAL_test += 1;
error_percent = 
measure_cal_error(OSCCAL_default, OSCCAL_test, &error);         //Returns actual error and percentage error 
if ((error_percent <= 1) && (error_percent >= -1))break; 
else if (!(OSCCAL_test%8))Serial.write('.');}
OSCCAL_2_percent = OSCCAL_test;                                 //Save OSCCAL giving and error of between 1 and 2%

Serial.write("\r\n\r\nOSCCAL\t  Error\t   %error\r\n");
_delay_ms(10);                                                  //Complete printing before changong OSCCAL

for (int m = OSCCAL_2_percent; m <= 225; m++){                  //Continue testing OSCCAL values
OSCCAL_test = m;
error_percent = 
measure_cal_error(OSCCAL_2_percent, OSCCAL_test, &error);        //Pointer enables two values to be returned
if ((error_percent <= 1) && (error_percent >= -1))              //Print out results giving an error of < 2%
{print_cal_result(OSCCAL_test, error, error_percent);}
 OSCCAL_test += 1;}                                              //Next value of OSCCAL
 
User_cal = 0;
Serial.write("\r\rUser cal? Terminate with -cr-\r\n");

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
int EA_counter = 0;
//TCNT1_BKP = 0;
OSCCAL = OSCCAL_test; 
initialise_timers_for_cal_error();
    start_timers_for_cal_error();    
    
    while(!(TIFR2 & (1 << TOV2)));              //Wait for T2 to overflow for first time
    TIFR2 |= (1 << TOV2);                 //Reset overflow flag
    get_error(EA_counter);                  //get result and ignore it
    EA_counter = 1;                     //increment counter
    while(!(TIFR2 & (1 << TOV2)));              //Wait for T2 to overflow for second time
    TIFR2 |= (1 << TOV2);                 //Reset overflow flag
OSCCAL = OSCCAL_OK;  
*error = get_error(EA_counter);
return 100 * long(*error)/7812;}


/************************************************************************************************/
int get_error (char EA_counter){
int TCNT1_BKP, target_res;
target_res = 7812;                                
TCCR1B = 0;                           //Halt T1
TCNT1_BKP = TCNT1;                        //Copy the value of TCNT1
TCNT1 = 0;                            //Clear TCNT1
TCCR1B = cal_speed;//2;//3;                           //Get T1 running again ASAP (Note T2 has not stopped running)

if(!EA_counter)return 0;                    //Ignore first result to allow for warm up.
else
return (TCNT1_BKP - target_res);}               //return second error result


/************************************************************************************************/
void print_cal_result(unsigned char OSCCAL_test, long error, char percent) {
Serial.write("\r\n");                                         //Sends askii chars
Serial.print(OSCCAL_test);                                    //Sends number as askii string
Serial.write("\t   ");
Serial.print(error);
Serial.write("\t      ");
Serial.print(int(percent));                                   //Sends char variable as askii char
//Serial.write("\t");
//Serial.print(TCNT1);
_delay_ms(5);}



/*********************************************************************************************/
    void initialise_timers_for_cal_error(void){
    TCNT1=0;TCCR1B = 0;                   //Reset and halt T1
    TCCR2B =  0x0;  while(ASSR & (1 << TCR2BUB));     //Halt T2
    TCCR2A = 0; while(ASSR & (1 << TCR2AUB));       //Reset T2 
    TCNT2=0; while(ASSR & (1 << TCN2UB)); }       //Reset TCNT2



/*********************************************************************************************/   
    void start_timers_for_cal_error(void)
    {TCCR2B = cal_speed - 1;//1;//2                      //32,768Hz clock derived from watch crystal 
    while(ASSR & (1 << TCR2BUB));             //overflows every 7.8125mS
    TCCR1B = cal_speed;}//2;3;}                      //1MHz clock counts to 7,812 in 7.8125mS    


/*********************************************************************************************/  
