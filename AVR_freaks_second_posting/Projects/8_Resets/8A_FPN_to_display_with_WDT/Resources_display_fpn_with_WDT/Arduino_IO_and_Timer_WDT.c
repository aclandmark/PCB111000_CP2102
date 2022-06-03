

#define T2_delay_10ms 	7,178


void Timer_T2_10mS_delay_x_m(int);
void Timer_T2_sub(char, unsigned char);
char isCharavailable (int);
char isCharavailable_with_WDT (int);
char waitforkeypress(void);
char decimal_digit (char);
char wait_for_return_key(void);
char wait_for_return_key_with_WDT(void);


/***************************************************************************************************************/
void Timer_T2_10mS_delay_x_m(int m)
{for (int n = 0; n < m; n++){Timer_T2_sub(T2_delay_10ms);}}



/***************************************************************************************************************/
void Timer_T2_sub(char Counter_speed, unsigned char Start_point){ 
TCNT2 = Start_point;
TCCR2B = Counter_speed;
while(!(TIFR2 & (1<<TOV2)));
TIFR2 |= (1<<TOV2); TCCR2B = 0;}



/***************************************************************************************************************/
char isCharavailable (int m){int n = 0;										//For m = 1 waits a maximun of 7.8mS
while (!(Serial.available())){n++;											//before returning zero
if (n>4000) {m--;n = 0;}if (m == 0)return 0;}								//Returns 1 immediately that a char is received
return 1;}



char isCharavailable_with_WDT (int m){int n = 0;
while (!(Serial.available())){n++;										//Increments "n" from zero to 8000
if (n>8000) {m--;n = 0;wdr();}if (m == 0)return 0;}						//Checks the receiver at each increment
return 1;}																//Returns a 1 as soon as a character is received
																		//If no character is sent it pauses a while (10m mS)
																		//and eventually returns zero.
																		//Note: this subroutine enables us to reset the WDT (wdr();)
																		//in a way that is not possible with "waitforkeypress()"



/***************************************************************************************************************/
char waitforkeypress(void)
{while(!(Serial.available())); 
return Serial.read();  }



/***************************************************************************************************************/
char decimal_digit (char data){
if (((data > '9') || (data < '0')) )return 0;
else return 1;}



/***************************************************************************************************************/
char wait_for_return_key(void){                  							//Detects \r\n, \r or \n
char keypress,temp;
keypress = waitforkeypress();
if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable(1)){temp = Serial.read();}keypress = '\r';}
return keypress;}




char wait_for_return_key_with_WDT(void){                  							//Detects \r\n, \r or \n
char keypress,temp;
//keypress = waitforkeypress();

while(1){
if (isCharavailable_with_WDT(8)){
keypress = Serial.read();
break;}}

if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable(1)){temp = Serial.read();}keypress = '\r';}
return keypress;}


