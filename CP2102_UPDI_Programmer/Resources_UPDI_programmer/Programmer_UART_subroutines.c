





/*******************************************************************************************************************************/
void UART_Tx(unsigned int data_byte_T){               //starts Hi Z
  unsigned char parity = 0;
  Prog_DD_Reg |= (1 << Prog_DD_bit);                                //start bit
  clock_delay_T;

for (int n = 0; n <= 7; n++){
  if (data_byte_T & (1 << n))
  {Prog_DD_Reg &= (~(1 << Prog_DD_bit)); parity += 1;}
 else {Prog_DD_Reg |= (1 << Prog_DD_bit);}clock_delay_T;}           //clock data out

if (parity%2){Prog_DD_Reg &= (~(1 << Prog_DD_bit));} 
else {Prog_DD_Reg |= (1 << Prog_DD_bit);}
  clock_delay_T;                                      //clock parity bit
  Prog_DD_Reg &= (~(1 << Prog_DD_bit));                             //initiate stop bit 
  clock_delay_T;                                      //Stop bits
  clock_delay_T;}


/************************************************************************************************/
unsigned char UART_Rx(void){
  unsigned char data_byte_R = 0;
    char parity = 0;
                          
  while (Prog_IO_Port & (1 << Prog_pin));                        //wait for start bit
  clock_delay_R;                                      //The full delay is required 
  for (int n= 0; n <= 7; n++){clock_delay_R;
    if (Prog_IO_Port & (1 << Prog_pin))
    {data_byte_R |= (1 << n); parity += 1;}}
    clock_delay_R;

 if ((Prog_IO_Port & (1 << Prog_pin)) && (parity%2)); 
 else P_counter++;                                      //Parity often received in error?????
 
 clock_delay_R;                                         //stop bit
 clock_delay_R;                                         //stop bit  
 return data_byte_R;}


/*********************************************************************************/
ISR(USART_RX_vect){if (mode =='H')upload_hex();}
                    
ISR(TIMER1_OVF_vect) {
  if(!(T1OVFM)){UPDI_timeout = 1;TCCR1B = 0;}
  
  if(T1OVFM == 1){
    if(text_started == 3){T1OVFM = 0;
    endoftext -= 1; 
  TCCR1B = 0; TIMSK1 &= (~(1 << TOIE1));       
  inc_w_pointer; store[w_pointer] = 0;                         
  inc_w_pointer; store[w_pointer] = 0;}}}
