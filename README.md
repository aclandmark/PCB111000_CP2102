# PCB111000_CP2102


PCB111000 has beeen developed as a learning aid for the C language when applied to AVR devices.  
It consists of a USB bridge to communicate with a PC, an 8 digit display and two AVR devices. 
One of the AVR devices (Atmega 328) hosts a programmer and miniOS which drives the display, 
the other (Atmega168), the user device, hosts user projects.

An I2C bus is used to link the two devices.
All user projects are compiled using Arduino, system projects use Arduino or Studio 7 if needed.
The boards are set up using the UNO to host a bespoke programer.  See repository "UNO_as_an_AVR_programer". 

See repository "PCB-111000/1_Documentation/1_PCB 111000 leaflet.pdf" for general information and a block diagram of the original development. 

There are three versions of PCB111000:

PCB_111000_V2 using two Atmega devices and the FTDI FT230XS USB bridge
PCB_111000_UNO_V2 A simplified plug in version for use with the UNO
PCB_111000_CP2102 Using one Atmega one ATtiny and a CP2102 module for USB connectivity.

In PCB_111000_UNO_V2 and PCB_111000_CP2102 the user device is an Atmega328 which hosts
a bootloader as well as the user projects.

In PCB_111000_CP2102 the I2C bus is replaced with a one wire firmware UART.



PCB111000_CP2102 is assembled using the following steps:

	Prior to assembly a UNO loaded with "UNO_AVR_Programmer" is used to
	program an Atmega328:
	
		With a routine that will be used to calibrate the internal 8MHz clock
		and will then be deleted.
		With a bootloader that will be used for all future programming operations
	
	Post assembly a UPDI programmer is uploaded to the Atmega328 which 
	enables the ATtiny1606 to be programmed with the miniOS.

	Calibration of the ATtiny1606 checked and adjusted if necessary
	
	The pcb is now ready to accept user projects.

	At any stage the UPDI programmer can be rienstated to upgrade the miniOS.


SW used to configure PCB_111000_CP2102  
UNO_AVR_Programmer :	see AVR freaks projects 9 Sept 2020 Slighytly modified  
UNO_UPDI_Programmer: 	Originally writen for the UNO but also runs with an 8MHz clock  
			and can be used here 




