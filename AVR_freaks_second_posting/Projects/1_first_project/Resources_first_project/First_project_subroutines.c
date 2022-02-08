
void print_eep_address (unsigned int);



void One_wire_Tx_2_integers(unsigned int NUM_1, unsigned int NUM_2){	//Transaction: Send type and two 16 bit words to the ATtiny1608
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'a';  UART_Tx_1_wire();								//Transaction type is 'a'
One_wire_Tx_char = NUM_1;  UART_Tx_1_wire(); 							//Send lower 8 bits
One_wire_Tx_char = NUM_2;  UART_Tx_1_wire(); 

One_wire_Tx_char = NUM_1 >> 8;  UART_Tx_1_wire();						//Send upper 8 bits 
One_wire_Tx_char = NUM_2 >> 8;  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt_on_PC5;}


unsigned int PRN_16bit_GEN(unsigned int start, unsigned char *PRN_counter){							//Pseuo random numbrer generation: Google  LFSR for details
unsigned int bit, lfsr, eep_address;
unsigned char eep_offset;

eep_offset = eeprom_read_byte((uint8_t*)(0x3ED));

if(!(*PRN_counter)) 
{lfsr = (eeprom_read_byte((uint8_t*)(0x3F2 - eep_offset)) << 8) + 
eeprom_read_byte((uint8_t*)(0x3F3 - eep_offset));}

else lfsr = start;
bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
lfsr = (lfsr >> 1) | (bit << 15);

*PRN_counter += 32;

if(!(*PRN_counter))
{eeprom_write_byte((uint8_t*)(0x3F2 - eep_offset),(lfsr>>8));
eeprom_write_byte((uint8_t*)(0x3F3 - eep_offset),lfsr);

print_eep_address(0x3F3);
Char_to_PC(' ');
print_eep_address(0x3F2);
String_to_PC("\r\n");
Toggle_LED_1;
}

return lfsr;}

void print_eep_address (unsigned int eep_address)
{char num_string[10];
eep_address -= eeprom_read_byte((uint8_t*)(0x3ED));
itoa (eep_address, num_string, 16 );
{int m = 0; while (num_string[m])Char_to_PC(num_string[m++]);}}




/*
if(!(start)) lfsr = (eeprom_read_byte((uint8_t*)(0x3F3)) << 8) 
+ eeprom_read_byte((uint8_t*)(0x3F2));
else lfsr = start;
bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
lfsr = (lfsr >> 1) | (bit << 15);
if(!(start)){
eeprom_write_byte((uint8_t*)(0x3F3),(lfsr>>8));
eeprom_write_byte((uint8_t*)(0x3F2),lfsr);}

return lfsr;}
*/

/*void I2C_Tx_any_segment_clear_all(void){
char segment = 'a'; char digit_num = 0;
char s[2]; char num_bytes=2; char mode = 'A';
s[0] = segment;
s[1] = digit_num; 
I2C_Tx(num_bytes,mode, s);}*/

void One_wire_comms_any_segment(char letter, char digit_num){
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'b';			UART_Tx_1_wire();
One_wire_Tx_char = letter;		UART_Tx_1_wire(); 
One_wire_Tx_char = digit_num;	UART_Tx_1_wire();
reinstate_pin_change_interrupt_on_PC5;}