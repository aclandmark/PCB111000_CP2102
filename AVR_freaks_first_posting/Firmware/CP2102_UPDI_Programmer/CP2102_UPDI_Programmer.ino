
/*
UNO_UPDI programmer modified for use with Project "PCB111000_CP2102"
A simple user application is tagged onto the end of it for test purposes
The programmer and user app run with a baud rate of 14400.
The bootloader runs at 57600

PINB4 is used for the one wire comms
PINC5 is used for the vertical switch
PINB3 for programming
*/



#include "Resources_User_app.h"                                //Contains resources used by template and shared with programmer
#include "Resources_UPDI_programmer.h"                          //Only contains resources used by the programmer

void One_wire_comms_any_segment(char, char);


int main (void){ 
char letter=0, digit_num=0, seg_counter = 0,direction = 0;


setup_328_HW;    

/************************Programmer code starts here and can be removed************************************/
FlashSZ = 0x2000;                                      //Amount of flash availale in ATtiny 1606
User_prompt;

sendString("\r\nPress 'a' to program target or AOK to run test application");
if(waitforkeypress() == 'a'){

//********************************Programmer target connection sequence************************************
Timer_T1_sub_with_interrupt(T1_delay_100ms);          //Generates a timeout if contact with the target fails
sei();
contact_target;
configure_updi;                                       //Increases UPDI clock to 16MHz and reduce guard band to 2 cycles
print_out_SIB;
if(UPDI_timeout)
{sendString("Power Cycle Required\r\n");
while(1);}
else{cli();TCCR1B = 0;
TIMSK1 &= (~(1 << TOIE1));}

initialise_NVM_programming;
sendString("Programming fuses\r\n");
write_fuse (WDTCFG, 0x0);                             //Default value: WDT under program control
write_fuse (BODCFG,0x0);                              //Default value: BOD dissabled
write_fuse (OSCCFG, 0x01);                           //select the 16MHz internal clock with factory cal
write_fuse (SYSCFG0, 0xF7);                           //UPDI enabled, EEPROM preserved at chip erase
write_fuse (SYSCFG1, 0xFD);                           //16mS SUT
write_fuse (APPEND, 0);                               //No area of flash is partitioned off 
write_fuse (BOOTEND, 0);                              //for data or a bootloader


sendString("\r\nProgram flash with hex? -y- or AOK");
if (waitforkeypress() == 'y')
{ mode = 'H';                                         //Text mode is not included in this version of the programmer
sendString("\r\nSend file  ");
Program_Flash_Hex();}

Verify_Flash_Hex();
sendString("\r\nFuses:\tWDT, BOD, OSC,SYS0\tSYS1, APPEND, BOOTEND\r\n\t");
read_out_fuses();

UPDI_reset; 
Dissable_UPDI_sesion;}


//************Code for a test user applicationis presented in the next section *************************

sendString("\r\n\r\nRunning trial application (POR may be required)? \r\n\r\n");
/************************Programmmer code ends here*******************************************************************/

sei();
comms_cal;
set_up_pin_change_interrupt;                                    //Set up PCI on PC5 for SM switch
set_up_one_wire_comms;                                           //One way comms for template requires port to be set to Tri state 
//set_up_activity_leds;
Set_LED_ports;
LEDs_off;
Reset_ATtiny1606;                                                     //Command to reset 1606
_delay_ms(500);

while(1){

One_wire_Tx_char = 'c';  UART_Tx_1_wire();                     //Command to display arbitary segments
while(1){                                                      //Generate pattern
while(seg_counter < 56){                                       //There are 56 segments in total
letter = (PRN_16bit_GEN (0)%7) + 'a';
digit_num = (PRN_16bit_GEN (0)%8);
               
if ((!(direction)) 
&& (display_bkp[letter - 'a'] & (1 << digit_num)))
continue;                                                     //Continue statements skip back to the top of the while-loop
if ((direction)
&& (!(display_bkp[letter - 'a'] & (1 << digit_num))))
continue;                                                     //to prevent segments being turned-off before they have all been turned on.

One_wire_comms_any_segment(letter, digit_num);

backup_the_display(letter, digit_num);                        //keep backup up to date
seg_counter += 1;}

direction ^= 1;                                                //Toggle the direction_counter value
seg_counter = 0;
_delay_ms(250);}}                                             //Just pause before toggling LEDs off one at a time


SW_reset;
return 1;}
