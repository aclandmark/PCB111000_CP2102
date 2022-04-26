
/************Define clock memory locations********************/
#define HoursH digits[7]
#define HoursL digits[6]
#define MinsH digits[5]
#define MinsL digits[4]
#define SecsH digits[3]
#define SecsL digits[2]
#define msecsH digits[1]
#define msecsL digits[0]



/***********Define clock display functions and modes***************/
#define reset_clock_1   {digits[0] = 0; for (int m = 1; m < 8; m++)digits[m] = '0'; }
#define reset_clock_2   {for (int m = 0;  m < 8; m++)\
{if ((m==2) || (m== 5))digits[m] = ' '; else digits[m] = '0'; }\
I2C_Tx_8_byte_array_plus_mode(7, digits);I2C_Tx_3(8, '2');}

#define AT_clock_mode 7
#define AT_exit_stop_watch 10, '1'
#define AT_mode_1 4

#define display_clock 8, '1'
#define hide_clock 8, '2'
#define pause_clock 8, '3'
#define increment_seconds 8, '5'
#define decrement_minutes 8, '6'
#define decrement_seconds 8, '7'
#define increment_minutes 8, '8'

#define display_current_time 9, '1'
#define display_stored_times 9, '4'
#define store_time 9, '2'
#define one100ms_mode 9, '1'
#define ten_ms_mode 9, '2'