

#define T2_delay_10ms 	7,178


void Timer_T2_10mS_delay_x_m(int);
void Timer_T2_sub(char, unsigned char);
char isCharavailable (int);
char waitforkeypress(void);
char decimal_digit (char);
char wait_for_return_key(void);



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


