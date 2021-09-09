# PCB111000_CP2102

PCB111000 has beeen developed as a learning aid for the C language when applied to AVR devices.
It consists of a USB bridge to communicate with a PC, an 8 digit display and two AVR devices. One of the AVR devices hosts a miniOS which drives the display and the other, the user device, hosts user projects.

There are three PCB111000 projects pcbs:

PCB111000_New The initial version in which the miniOS has been rewritten to make it more readable. An Atmega328 hosts the miniOS, this includes a programmer for the user device, an Atmega 168. An FTDI chip FT230X acts as the uSAB bridge.

PCB111000_UNO A cut down version in which the a UNO provides the PC comms and an Atmega 328 to hosts the user projects.

PCB111000_CP2102 This uses a CP2102 module for comms with a PC, an ATtiny1606 to drive the display and user projects run on an Atmega328 which is programmed using a bootloader. 


For PCB111000_CP2102 

Projects are compiled using Studio 7 or the Arduino development environment.
A combined UPDI programmer plus boootloader is written for the user device.
This is loaded using the UNO_AVR_Programmer (see AVR freaks projects 9 Sept 2020)
Post assembly the ATtiny1606 is programmed using the UPDI programmer.
For normal operation the bootloader runs an loads user projects.

All communication between the PC and pcb goes via the terminal program Bray++.


