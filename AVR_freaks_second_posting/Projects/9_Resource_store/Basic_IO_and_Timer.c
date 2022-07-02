#define T2_delay_10ms 	7,178


void setup_PC_comms_Basic (unsigned char, unsigned char);
void Timer_T2_10mS_delay_x_m(int);
void Timer_T2_sub(char, unsigned char);

char isCharavailable_Basic (int);
char isCharavailable_A (int);
char waitforkeypress_Basic(void);
char waitforkeypress_A(void);

char Char_from_PC_Basic(void);
void String_to_PC_Basic(const char*);
void Char_to_PC_Basic(char);

char decimal_digit (char);
char wait_for_return_key_A(void);




/**********************************************************************************************/
void setup_PC_comms_Basic (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
UCSR0B = 0;
UBRR0H = UBRROH_N; 
UBRR0L = UBRR0L_N;  
UCSR0A = (1 << U2X0);
UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);} 



/*********************************************************************/
void Timer_T2_10mS_delay_x_m(int m)
{for (int n = 0; n < m; n++){Timer_T2_sub(T2_delay_10ms);}}


/**********************************************************************************************/
void Timer_T2_sub(char Counter_speed, unsigned char Start_point){ 
TCNT2 = Start_point;
TCCR2B = Counter_speed;
while(!(TIFR2 & (1<<TOV2)));
TIFR2 |= (1<<TOV2); TCCR2B = 0;}



/**********************************************************************************************/
char isCharavailable_Basic (char m){int n = 0;
while (!(UCSR0A & (1 << RXC0))){n++; wdr();	
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}	
return 1;}
	
char isCharavailable_A (int m){int n = 0;
while (!(Serial.available())){n++;	wdr();			
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}	
return 1;}	


char waitforkeypress_Basic (void){
while (!(UCSR0A & (1 << RXC0)))wdr();	
return UDR0;}	


char waitforkeypress_A (void){
while (!(Serial.available()))wdr();	
return Serial.read(); }





/**********************************************************************************************/
char Char_from_PC_Basic(void)
{return UDR0;}




/**********************************************************************************************/
void String_to_PC_Basic(const char s[]){
int i = 0;
while(i < 200){
if(s[i] == '\0') break;
Char_to_PC_Basic(s[i++]);}}



/**********************************************************************************************/
void Char_to_PC_Basic(char data){
while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;}




/***************************************************************************************************************/
char decimal_digit (char data){
if (((data > '9') || (data < '0')) )return 0;
else return 1;}




/***************************************************************************************************************/
char wait_for_return_key_A(void){                  							//Detects \r\n, \r or \n
char keypress,temp;
while(1){
if (isCharavailable_A(8)){
keypress = Serial.read();
break;}}
if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable_A(1)){temp = Serial.read();}
keypress = '\r';}
return keypress;}


