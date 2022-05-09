

/*
 Press sw2 to start and stop timer
 Press sw1 to restart it
 Press sw3 to change intensity

 Uses special version of One_wire_transactions.c
 */

 
#include "Stopwatch_header.h"



int main (void){

setup_328_HW;
initialise_T2();
sei();

                      
Reset_ATtiny1606;

while(switch_2_up);

sei();
stop_watch_mode = 0;
centi_sec_counter = 0;
start_clock();
set_up_PCI;
enable_PCI;


while(1)
{while(clock_tick < 20); clock_tick = 0; 

switch(stop_watch_mode){
  case 0: {Inc_OS_time;}break;
  case 1: centi_Seconds_to_display(stop_watch_time);stop_watch_mode = 0; {Inc_OS_time;}break;}
}}





/***********************************************************************************************************************/
ISR(PCINT2_vect) { 
  if((switch_1_up) && (switch_2_up) && (switch_3_up)){return;}
 
 if(switch_2_down)
 {disable_pci_on_sw2;
  stop_watch_time = centi_sec_counter;
  stop_watch_mode = 1;
  enable_pci_on_sw1;}
  
  if(switch_1_down){
    disable_pci_on_sw1;  
  One_wire_Tx_char = 'O';    
sei();UART_Tx_1_wire();
enable_pci_on_sw2;}

if(switch_3_down){
sei();One_wire_Tx_char = 'G'; UART_Tx_1_wire();}}
  
  
  

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
void centi_Seconds_to_display(long num){
One_wire_Tx_char = 'N';                           //Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){
One_wire_Tx_char = num >> (8 * (3 - m));        //Split the number into 4 chars
UART_Tx_1_wire();}}                             //and send them individually




  

/************************************************************************************************************/
