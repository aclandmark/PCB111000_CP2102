
/*
The ATtiny1606 has a 1MHz peripheral clock.
It uses 2mS steps to drive the 8 digit display
 An extra 2mS is added for comms.
 A comms start pulse is sent to PB4 every 18mS.
 T1 clock of 1MHz counts to 18000 in this period
 Comms is allowed 10 times 0.2mS slots

Any inaccuracy in the ATtiny 1606 clock is compensated for by
a correction factor applied to the Atmega328 1-wire comms clock.
*/


#include "Project_header.h"                                 //Contains resources used by template and shared with programmer

int main (void) {
 
setup_328_HW;  

User_prompt;
/**************Measure time interval between successsive start pulses (generated by the 1606*************************************/
ATtiny1606_period = 0;                                      //Time between successive start pulses
for(int m = 0; m <= 24; m++){                               //Measure time 25 times 
measure_1606_mux_period;
ATtiny1606_period += TCNT1;}
ATtiny1606_period /= 25;                                    //Take average result

Serial.write("\r\n ATtiny1606 mux period \
in uS (should be 20000)\t");
Serial.print(ATtiny1606_period);
_delay_ms(5);


/**************Calculate correction factors to be applied to the Atmega display and comms locks*************************************/
Serial.write("\r\n\r\nCalculated comms correction \
factor\t");                                                 //Calculate correction factor to be applied to the Atmega

Comms_clock_correction = (ATtiny1606_period/9 - 2000)/10;

Serial.print (Comms_clock_correction);
_delay_ms(5);



/**************Generate table designed to illustrate that selection of the correction factors is not critical**************************/
Print_table_headings();

Comms_clock_correction -= 7;                                    //Print results for adjacent correction factors                                
for(int m = 0; m <= 15; m++){                                   //Confirms that the correction factor is not critical
Comms_clock = 200 + Comms_clock_correction;
Atmega_328_period =  Comms_clock * 90;

error = ATtiny1606_period - Atmega_328_period;
error_percent = 100 * error / ATtiny1606_period;

Print_results(Comms_clock_correction, Atmega_328_period, \
error, error_percent); 
Comms_clock_correction += 1;
_delay_ms(10);}
Serial.write("\r\n");


/*********User enters correction factor (enters calculated value for comms period)**********************************************************/
User_correction_factor = 0;
Serial.write("\r\nUser correction? Terminate with -cr- \
(twice if necessary)");

while (((keypress = waitforkeypress()) != '\r') && 
(keypress != '\n')){
User_correction_factor = 
(User_correction_factor * 10) + keypress - '0';}                      //Convert string to number
waitforkeypress();                                                 //Required where PC transmits \r and \n


/******************************User correction factor saved to EEPROM and echoed to screen**************************************************/
eeprom_write_byte((uint8_t*)0x3FB, User_correction_factor);                      //Save user cal in EEPROM 
eeprom_write_byte((uint8_t*)0x3FA, User_correction_factor);

Serial.write("\r\nSaved to EEPROM");
comms_cal;
Atmega_328_period =  Comms_clock * 90;
error = signed (ATtiny1606_period - Atmega_328_period);
error_percent = 100 * error / ATtiny1606_period;

Print_results(User_correction_factor, Atmega_328_period, error, error_percent);
Serial.write("\r\n\r\n");

SW_reset;
return 1;}



/**********************************************************************************************/
char waitforkeypress(void) {
  while (!(Serial.available()));
  return Serial.read();}
 

/**********************************************************************************************/ 
char isCharavailable (int m){int n = 0;    
while (!(Serial.available())){n++;
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}
return 1;}



/**********************************************************************************************/
void Print_results(int Comms_clock_correction,  int Atmega_328_period, long error, long error_percent)
{Serial.write("\r\n    ");
Serial.print (Comms_clock_correction);
_delay_ms(5);
Serial.write("\t     ");
Serial.print (Atmega_328_period);
_delay_ms(5);
Serial.write("\t     ");
Serial.print (error);
_delay_ms(5);
Serial.write("\t  ");
Serial.print (error_percent);
_delay_ms(25);}



/**********************************************************************************************/
void Print_table_headings(void)
{Serial.write("\r\n\r\nCorrection    TCNT1\t    Error\terror%");}
