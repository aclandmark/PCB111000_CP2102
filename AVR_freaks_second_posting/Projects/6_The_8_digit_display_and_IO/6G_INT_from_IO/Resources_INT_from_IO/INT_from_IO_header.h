
/************Define clock memory locations********************/
/*#define HoursH digits[7]
#define HoursL digits[6]
#define MinsH digits[5]
#define MinsL digits[4]
#define SecsH digits[3]
#define SecsL digits[2]
#define deci_SecsH digits[1]
#define deci_SecsL digits[0]*/



/***********Define clock display functions and modes***************/
/*#define reset_clock_1   {digits[0] = 0; for (int m = 1; m < 8; m++)digits[m] = '0'; }


#define Display_time \
{One_wire_Tx_char = 'J'; UART_Tx_1_wire();\
for(int p = 0; p <= 7; p++){\
switch (p){\
  case 2:\
  case 4:\
  case 6: One_wire_Tx_char = digits[p] | 0x80; UART_Tx_1_wire(); break;\
  default: One_wire_Tx_char = digits[p]; UART_Tx_1_wire(); break;}}}


#define Inc_OS_time \
{One_wire_Tx_char = 'K'; UART_Tx_1_wire();}*/


/*********************************************************************/
#define shift_digits_left {for (int n = 0; n < 7; n++){display_buffer[7-n] = display_buffer[6-n];}}


#define Send_float_num_string \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define Send_int_num_string \
One_wire_Tx_char = 'A'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();


#define pause_PCI_and_Send_float_num_string \
pause_PCI;sei();Send_float_num_string;cli();reinstate_PCI;


#define initialise_display \
clear_display_buffer;\
display_buffer[0] = '0';\
pause_PCI_and_Send_float_num_string;\
sei();


#define f_number_from_mini_OS \
sei();One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){\
UART_Rx_1_wire(); *Char_ptr = One_wire_Rx_char;\
Char_ptr += 1;}\
f_number = *Flt_ptr;




