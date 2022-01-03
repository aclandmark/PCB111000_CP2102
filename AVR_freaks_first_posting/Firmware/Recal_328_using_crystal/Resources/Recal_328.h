



char isCharavailable (int);
char receiveChar(void);
char measure_cal_error(unsigned char, unsigned char, long *);
void num_to_PC(long);
void print_cal_result(unsigned char, long, char);

#define wdr()  __asm__ __volatile__("wdr")



/**********************************************************************************/
 #define setup_328_HW \
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
Serial.begin(115200);\
while (!Serial);



/**********************************************************************************/
#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}

/**********************************************************************************/
#define initialise_IO \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;



/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}


/**********************************************************************************/
#define initialise_crystal \
ASSR = (1 << AS2);\
initialise_timers_for_cal_error();\
start_timers_for_cal_error();\
if(cal_speed == 2){\
for (int m = 0; m < 256; m++){\
while(!(TIFR2 & (1 << TOV2)));\
TIFR2 |= (1 << TOV2);}}\
else{\
for (int m = 0; m < 32; m++){\
while(!(TIFR2 & (1 << TOV2)));\
TIFR2 |= (1 << TOV2);}} 


