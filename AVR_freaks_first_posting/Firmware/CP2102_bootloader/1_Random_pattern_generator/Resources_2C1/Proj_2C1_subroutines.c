



void One_wire_comms_any_segment(char letter, char digit_num){
One_wire_Tx_char = 'b';			UART_Tx_1_wire();
One_wire_Tx_char = letter;		UART_Tx_1_wire(); 
One_wire_Tx_char = digit_num;	UART_Tx_1_wire();}



/*************************************************************************************************************/
void backup_the_display(char segment, char digit_num){
display_bkp[segment - 'a'] = display_bkp[segment - 'a'] ^ (1 << digit_num);}


/*************************************************************************************************************/
unsigned int PRN_16bit_GEN(unsigned int start){		//Google LFSR  (Note: zero start is not used in the default application)
unsigned int bit, lfsr;								//Removing unwanted lines does not free up and additional page and has not been done

if(!(start)) lfsr = (eeprom_read_byte((uint8_t*)(0x3F2)) << 8) + eeprom_read_byte((uint8_t*)(0x3F3));	//unwanted line
else 																									//unwanted line
lfsr = start;
bit = (( lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
lfsr = (lfsr >> 1) | (bit << 15);
if(!(start)){																							//unwanted line
eeprom_write_byte((uint8_t*)(0x3F2),(lfsr>>8));															//unwanted line
eeprom_write_byte((uint8_t*)(0x3F3),lfsr);}																//unwanted line

return lfsr;}
 



 
