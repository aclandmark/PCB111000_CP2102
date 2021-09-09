# PCB111000_CP2102

PCB111000 has beeen developed as a learning aid for the C language when applied to AVR devices.
It consists of a USB bridge to communicate with a PC, an 8 digit display and two AVR devices. One of the AVR devices hosts a miniOS which drives the display and the other, the user device, hosts user projects.

There are three PCB111000 projects pcbs:

PCB111000_New The initial version in which the miniOS has been rewritten to make it more readable. An Atmega328 hosts the miniOS, this includes a programmer for the user device, an Atmega 168. An FTDI chip FT230X acts as the uSAB bridge.

PCB111000_UNO A cut down version in which the a UNO provides the PC comms and an Atmega 328 to hosts the user projects.

PCB111000_CP2102 This uses a CP2102 module for comms with a PC, an ATtiny1606 to drive the display and user projects run on an Atmega168/328.


When PCB111000_CP2102 is being set up the Atmega 328 hosts the UPDI programmer which is used to program the ATtiny1606 with the miniOS.
The UPDI programmer is then replaced with a bootloader (not the UNO bootloader).
The bootloader is then used to upload user projects.
The miniOS is developed using Atmel studio.
User projects can be developed using Atmel studio or Arduino.
In either case the resulting hex file is uploded using Bray++.

