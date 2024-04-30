# PCB111000_CP2102

PCB111000 has beeen developed as a learning aid for the C language when applied to AVR devices.
It consists of a USB bridge to communicate with a PC, an 8 digit display and two AVR devices. One of the AVR devices hosts a miniOS which drives the display and the other, the user device, hosts user projects.

There are three PCB111000 projects pcbs:

PCB-111000_V2 The initial version in which the miniOS has been rewritten to make it more readable. An Atmega328 hosts the miniOS, this includes a programmer for the user device, an Atmega 168. An FTDI chip FT230X acts as the uSAB bridge.

PCB111000_UNO_V2 A cut down version in which the a UNO provides the PC comms and an Atmega 328 to hosts the user projects.

PCB111000_CP2102 This uses a CP2102 module for comms with a PC, an ATtiny1606 to drive the display and user projects run on an Atmega328 which is programmed using a bootloader. 


PCB111000_CP2102 is assembled using the following steps:

	Prior to assembly a UNO loaded with "UNO_AVR_Programmer" is used to
	program an Atmega328:
	
		With a routine that will be used to calibrate the internal 8MHz clock
		and will then be deleted.
		With a bootloader that will be used for all future programming operations
	
	Post assembly the UPDI programmer is uploaded to the Atmega328 which 
	enables the ATtiny1606 to be programmed with the miniOS.

	Calibration of the ATtiny1606 checked and adjusted if necessary
	
	The pcb is now ready to accept user projects.

	At any stage the UPDI programmer can be rienstated to upgrade the miniOS.



User projects can be compiled using Studio 7 or the Arduino development environment.
All communication between the PC and pcb goes via the terminal program Bray++.


UNO_AVR_Programmer :	see AVR freaks projects 9 Sept 2020 Slighytly modified 
UNO_UPDI_Programmer: 	Originally writen for the UNO but also runs with an 8MHz clock
			and can be used here 




