

/*#define check_eep_addresses \
print_eep_address(0x3F3);\
Char_to_PC(' ');\
print_eep_address(0x3F2);\
String_to_PC("\r\n");

void print_eep_address (unsigned int);*/



/************************************************************************************************************************************************/
unsigned int PRN_16bit_GEN(unsigned int start, unsigned char *PRN_counter){				//Pseuo random numbrer generation: Google  LFSR for details
unsigned int bit, lfsr, eep_address;
unsigned char eep_offset;

eep_offset = eeprom_read_byte((uint8_t*)(0x3ED));										//Three pairs of eeprom registers are reserved for use by the EEPROM

if((!(*PRN_counter)) && (!(start)))														//Only read the EEPROM the first time a program calls this subroutine
{lfsr = (eeprom_read_byte((uint8_t*)(0x3F2 - eep_offset)) << 8) + 
eeprom_read_byte((uint8_t*)(0x3F3 - eep_offset));}

else lfsr = start;																		//Use previous PRN value to generate the next one
bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
lfsr = (lfsr >> 1) | (bit << 15);

*PRN_counter += 1;																		//Only write to EEPROM after generating 8 PRN values  
if(*PRN_counter == 16)

{eeprom_write_byte((uint8_t*)(0x3F2 - eep_offset),(lfsr>>8));
eeprom_write_byte((uint8_t*)(0x3F3 - eep_offset),lfsr);
Toggle_LED_1;
*PRN_counter = 0;}

return lfsr;}



/************************************************************************************************************************************************/
/*void print_eep_address (unsigned int eep_address)
{char num_string[10];
eep_address -= eeprom_read_byte((uint8_t*)(0x3ED));
itoa (eep_address, num_string, 16 );
{int m = 0; while (num_string[m])Char_to_PC_Basic(num_string[m++]);}}*/





