

/*
 Press sw3 to initialise the stop watch
 Press sw2 to pause it
 Press sw1 to restart it


Consists of two clocks, one generated by the mini-OS that increments every 200mS and
one generated by the user project that increments every 10mS.
Both use the watch crystal as their time standard.
When sw2 is pressed the 10mS clock over rides the 200mS clock
When sw1 is pressed control passes back to the 200mS clock
 
 Uses special version of "One_wire_transactions.c" that allows the "one-wire-comms" ISR
 to be interrupted when sw2 is pressed so that the precise time can be recorded.
 */

 
#include "Stopwatch_header.h"



int main (void){

setup_328_HW_Basic_IO;
initialise_T2();

Reset_ATtiny1606;
while(switch_3_up)wdr();                                     //Start stop watch

stop_watch_mode = 0;                                         //Stop watch running continuously
centi_sec_counter = 0;                                       //10mS precision
start_clock();
set_up_PCI;
enable_PCI;

while(1)
{while(clock_tick < 20)wdr(); clock_tick = 0;                 //Contact mini-os every 200mS and get it to update

switch(stop_watch_mode){
 case 0:  {Inc_OS_time;}break;                                //The mini-OS provides a clock that runs under the conrol of the project   
 case 1: centi_Seconds_to_display(stop_watch_time);           //Display paused after receiving local stop watch time 
 stop_watch_mode = 0; 
 {Inc_OS_time;}break;                                         //Continue to increment mini-OS time
  case 2:stop_watch_mode = 0;                                 //Use wishes to revert to normal mode (i.e. display mini-OS time) 
  {Inc_OS_time;}One_wire_Tx_char = 'O';                       //Instruction to mini-OS
  UART_Tx_1_wire();break;}
 }}



/***********************************************************************************************************************/
ISR(PCINT2_vect) {                                             //This ISR can interrupt the one wire comms process. 
  if((switch_1_up) &&
  (switch_2_up) && 
  (switch_3_up)){return;}
 
 if(switch_2_down)
 {disable_pci_on_sw2;
  stop_watch_time = centi_sec_counter;                          //Capture time at precise moment sw2 is pressed
  stop_watch_mode = 1;
  enable_pci_on_sw1;}
  
  if(switch_1_down){
    disable_pci_on_sw1; 
    stop_watch_mode = 2; 
 enable_pci_on_sw2;}
}
  
  
  

/***********************************************************************************************************************/
void initialise_T2(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS21);
OCR2B = 0;}


void start_clock(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 41;
TIMSK2 |= (1 << OCIE2A);}


ISR (TIMER2_COMPA_vect){ 
centi_sec_counter += 1;
  OCR2A += 41;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 99){tick_counter = -1; OCR2A -= 4;}}
  
  
  
  
  
/****************************************************************************************************************/
void centi_Seconds_to_display(long num){                        //Pauses display
One_wire_Tx_char = 'N';                                         //Command 'N' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){wdr();
One_wire_Tx_char = num >> (8 * (3 - m));                        //Split the number into 4 chars
UART_Tx_1_wire();}}                                             //and send them individually




  

/************************************************************************************************************/
