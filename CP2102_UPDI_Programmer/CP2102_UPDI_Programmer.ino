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


int main (void){ 
  
char keypress;
long int_num;
float FPN_1, FPN_2;
char FP_string[12];
char op;                                                //+, -, *, /, pow



unsigned int PORT_1=1, PORT_2;
int letter, digit_num;

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
/*while(1){

PORT_1 = 1;
PORT_2 = 0x8000;
for(int m = 0; m <=15; m++){
One_wire_comms(PORT_1, PORT_2);
_delay_ms(30);
PORT_1 = PORT_1 << 1;
PORT_2 = PORT_2 >> 1;}}*/


letter = 'a';
while(letter <= 'g'){


for (int m = 0; m <=7; m++){digit_num = m;
One_wire_Tx_char = 'b';  UART_Tx_1_wire();
One_wire_Tx_char = letter;  UART_Tx_1_wire(); 
One_wire_Tx_char = digit_num;  UART_Tx_1_wire(); 
_delay_ms(30);}

letter += 1;}

}
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




 
