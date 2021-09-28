/*
UNO_as_UPDI_programmer modified for use with PCB111000_CP2102 
Step 1  Change programming pin from PC0 to PB3 (in both .h files)  done
Step 2  Change programmer IO definitions                done
Step 3 Change define "contact target" definition      done
Step 4 Change define "print out SIB" definition       done
Step 5 Change UART_Tx/Rx subroutines in this file   done
 */


#include "Resources_Template_V2.h"                              //Contains resources used by template and shared with programmer
#include "Resources_UPDI_programmer.h"                          //Only contains resources used by the programmer

void One_wire_comms(unsigned int, unsigned int);

/*
 * Programmer uses PC0 which is initialsed to Hi-Z input
 * Floating point display template uses PC4 for sinlge wire UART. It is also Hi-Z
 * All other ports are WPU

Note: Intensity can be changed after a reset and while the UNO is waiting for the user to type in anoter number 
*/
char display_bkp[7];

int main (void){ 
  
char keypress;
long int_num;
float FPN_1, FPN_2;
char FP_string[12];
char op;                                                //+, -, *, /, pow
char letter=0, digit_num=0, seg_counter = 0,direction = 0;


unsigned int PORT_1=1, PORT_2;
//int letter, digit_num;

setup_328_HW;                                           //see "Resources\ATMEGA_Programmer


/************************Programmer code starts here and can be removed************************************/
FlashSZ = 0x2000;                                      //Amount of flash availale in ATtiny 1606
User_prompt;

sendString("\r\nPress 'a' to program target or AOK to run taget code");
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
write_fuse (OSCCFG, 0x01);                            //select the 16MHz internal clock with factory cal
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


//************Code for the UNO Floating point display is presented in the next section *************************
//**********************It is combined with the 1606 programmer for convenience**********************************
//*****************When development is complete the two applications can be separated***********************



sendString("\r\n\r\nRun trial application? -y- or AOK (POR may be required)\r\n\r\n");
if(waitforkeypress() == 'y'){

/************************Programmmer code ends here*******************************************************************/


PCICR |= (1 << PCIE1); PCMSK1 |= (1 << PCINT11);          //Set up PCI for SM switch
PORTC &= (~(1 << PORTC4));                                //One way comms for template requires port to be set to Tri state 
One_wire_Tx_char = 'F'; UART_Tx_1_wire();                 //Command to reset 1606


while(1){

sei();                                                    //Required to control intensity
  
User_prompt_template;


if (User_response =='i'){
sendString("Segment display");

/*
One_wire_Tx_char = 'c';  UART_Tx_1_wire();
digit_num = 0;
while(digit_num <= 7){
for (int m = 'a'; m <= 'g'; m++){letter = m;
One_wire_Tx_char = 'b';  UART_Tx_1_wire();
One_wire_Tx_char = letter;  UART_Tx_1_wire(); 
One_wire_Tx_char = digit_num;  UART_Tx_1_wire(); 
_delay_ms(30);
waitforkeypress();}
digit_num += 1;}*/


One_wire_Tx_char = 'c';  UART_Tx_1_wire();
while(1){                                                      //Generate pattern
while(seg_counter < 56){                                       //There are 56 segments in total
letter = (PRN_16bit_GEN (0)%7) + 'a';
digit_num = (PRN_16bit_GEN (0)%8);
                                                              //Continue statements skip back to the top of the while-loop
                                                              //This is to ensure segments are not turned-off before
                                                              //they have all been turned on.
      
if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) continue;
if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) continue;

One_wire_Tx_char = 'b';  UART_Tx_1_wire();
One_wire_Tx_char = letter;  UART_Tx_1_wire(); 
One_wire_Tx_char = digit_num;  UART_Tx_1_wire();

backup_the_display(letter, digit_num);                        //keep backup up to date
//Timer_T0_10mS_delay_x_m(5);  wdr();                            //delay and reset watch dog
_delay_ms(30);
seg_counter += 1;}

direction ^= 1;                                                //Toggle the direction_counter value
seg_counter = 0;
//Timer_T0_10mS_delay_x_m(100);
_delay_ms(500);
}}                                 //Just pause before toggling LEDs off one at a time


}


}
   
                                                    //Only required if programmer code is included
/**********************************End to test code section*********************************************/
SW_reset;
return 1;}



void One_wire_comms(unsigned int PORT_1, unsigned int PORT_2){
One_wire_Tx_char = 'a';  UART_Tx_1_wire();
One_wire_Tx_char = PORT_1;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2;  UART_Tx_1_wire(); 

One_wire_Tx_char = PORT_1 >> 8;  UART_Tx_1_wire(); 
One_wire_Tx_char = PORT_2 >> 8;  UART_Tx_1_wire(); }




/*************************************************************************************************************/
void backup_the_display(char segment, char digit_num){
display_bkp[segment - 'a'] = display_bkp[segment - 'a'] ^ (1 << digit_num);}


/*************************************************************************************************************/
unsigned int PRN_16bit_GEN(unsigned int start){
unsigned int bit, lfsr;

if(!(start)) lfsr = (eeprom_read_byte((uint8_t*)(0x1FB)) << 8) + eeprom_read_byte((uint8_t*)(0x1FA));
else lfsr = start;
bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
lfsr = (lfsr >> 1) | (bit << 15);
if(!(start)){
eeprom_write_byte((uint8_t*)(0x1FB),(lfsr>>8));
eeprom_write_byte((uint8_t*)(0x1FA),lfsr);}

return lfsr;}
 
