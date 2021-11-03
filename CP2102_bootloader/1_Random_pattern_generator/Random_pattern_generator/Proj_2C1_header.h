
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/delay.h>


#include "..\Resources_2C1\Proj_2C1_header_file.h"
#include "..\Resources_2C1\One_wire_transactions.c"
#include "..\Resources_2C1\Proj_2C1_subroutines.c"
