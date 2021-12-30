


#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

#define fast 2
#define slow 3
char cal_speed = fast; 

#include "Resources\Recal_328.h"
#include "Resources\ASKII_subroutines.c"
