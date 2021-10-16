
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>


#define Prog_Port   	PORTB
#define Prog_pin		PINB3
#define Prog_DD_bit		DDB3
#define Prog_IO_Port	PINB
#define Prog_DD_Reg		DDRB


/*
//Prog port for FP display
#define Prog_Port     PORTC
#define Prog_pin    PINC4
#define Prog_DD_bit   DDC4
#define Prog_IO_Port  PINC
#define Prog_DD_Reg   DDRC
*/

#define input_h                (Prog_IO_Port & (1 << Prog_pin))
#define input_l        			(!(Prog_IO_Port & (1 << Prog_pin)))
#define output_h         		Prog_DD_Reg &= (~(1 << Prog_DD_bit));
#define output_l          		Prog_DD_Reg |= (1 << Prog_DD_bit);




#include "Resources_UPDI_programmer\UPDI_Programmer.h"
#include "Resources_UPDI_programmer\Basic_IO_and_Timer_subs.c"
#include "Resources_UPDI_programmer\ASKII_subroutines.c"
#include "Resources_UPDI_programmer\Hex_Programmer_subs.c"
#include "Resources_UPDI_programmer\Hex_Programmer.c"
#include "Resources_UPDI_programmer\UPDI_subroutines.c"
#include "Resources_UPDI_programmer\verify_flash.c"
#include "Resources_UPDI_programmer\Programmer_UART_subroutines.c"
