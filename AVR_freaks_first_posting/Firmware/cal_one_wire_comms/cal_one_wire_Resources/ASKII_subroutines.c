

char decimal_digit (char);
char wait_for_return_key(void);




/**********************************************************************************************/
char waitforkeypress(void) {
  while (!(Serial.available()));
  return Serial.read();}
 

/**********************************************************************************************/ 
char isCharavailable (int m){int n = 0;                       //For m = 1 waits a maximun of 7.8mS
while (!(Serial.available())){n++;                            //before returning zero
if (n>4000) {m--; n = 0;}if (m == 0)return 0;}                //Returns 1 immediately that a char is received
return 1;}



/***************************************************************************************************************************************************/
int Int_from_KBD(void){                                       //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char display_buffer[8];
char array_ptr = 0;

for(int n = 0; n<=7; n++) display_buffer[n] = 0;              //Clear the buffer used for the string

while(1){
keypress = waitforkeypress();
if ((!(decimal_digit(keypress)))
&& (keypress != '-'))continue;                                //Ignore keypress if it is not OK
display_buffer[array_ptr++] = keypress;
break;}
 
while(1){
if ((keypress = wait_for_return_key())  =='\r')break;         //Detect return key press (i.e \r or\r\n)
if (decimal_digit(keypress))
{display_buffer[array_ptr++] = keypress;}}                                      
return atoi(display_buffer);}


/************************************************************************************************************/
char wait_for_return_key(void){                  				//Detects \r\n, \r or \n
char keypress,temp;
keypress = waitforkeypress();
if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable(1)){temp = Serial.read();}keypress = '\r';}
return keypress;}



/************************************************************************************************************/
char decimal_digit (char data){
if ((data <= '9') && (data >= '0'))return 1;
else return 0;}