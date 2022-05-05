


void Format_time_and_display(void){
	Hours =     deci_sec_counter/36000;
	Minutes =   (deci_sec_counter%36000)/600;
	Seconds =   ((deci_sec_counter%36000)%600)/10;
	deci_Secs = ((deci_sec_counter%36000)%600)%10;

	timer_utoa(Hours); 
	display_buffer[7] = charH; 
	display_buffer[6] = charL | 0x80;
	timer_utoa(Minutes); 
	display_buffer[5] = charH; 
	display_buffer[4] = charL | 0x80;
	timer_utoa(Seconds); 
	display_buffer[3] = charH; 
	display_buffer[2] = charL | 0x80;
	timer_utoa(deci_Secs * 10); 
	display_buffer[1] = charH; 
	display_buffer[0] = charL; }






/**********************************************************************************************************************/
void timer_utoa(char n){                //converts an unsigned number to a string of digits
	if (n>=10)
	{charL = n%10;
		charH = (n-charL)/10;
		charL = charL + '0';
	charH = charH + '0';}
	else
	{charH = '0'; charL = n + '0';}}

