# PCB111000_CP2102

There are three PCB111000 projects pcbs:

PCB111000_New         The initial version in which the miniOS has been rewritten to make it more readable.
PCB111000_UNO         A cut down version in which the a UNO provides the PC comms and Atmega 328 that hosts the user projects.
PCB111000_CP2102      This uses a CP2102 module for comms with a PC, an ATtiny1606 to drive the display and user projects run on an Atmega328.


Wen PCB111000_CP2102 is being set up the Atmega 328 hosts the UPDI programmer which is used program the ATtiny1606 with the miniOS.
The UPDI programmer is then replaced with a bootloader (not the UNO bootloader).
The bootloader is then used to upload user projects.

The miniOS is developed using Atmel studio.
User projects can be developed using Atmel studio or Arduino.
In either case the resulting hex file is uploded using Bray++.

