
void Check_num_for_to_big_or_small(float);




/******************************************************************************************/
unsigned long Unsigned_Int_from_PC(char * num_as_string,char next_char)
{char strln;
int num;

pause_WDT;
Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
resume_WDT;
num_as_string[strln] = 0;

if(next_char){
Serial.write(num_as_string);
Serial.write(next_char);}

num = atoi(num_as_string);
return (unsigned int )num;}



/******************************************************************************************/
long Int_Num_from_PC(char * num_as_string,char next_char)
{char strln;

pause_WDT;
Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
resume_WDT;
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
return atol(num_as_string);}






/******************************************************************************************/
void Unsigned_Int_to_PC(unsigned long Int_num, char * num_as_string, char next_char)
{
ultoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);
Serial.print(next_char);
}



/******************************************************************************************/
void Int_Num_to_PC(long Int_num, char * num_as_string, char next_char)
{
ltoa(Int_num, num_as_string, 10);
Serial.print(num_as_string);Serial.print(next_char);
}






/*****************************************************************************************/
void Sc_Num_to_PC(float num, char pre_dp, char post_dp, char next_char)
{int A = 1;
char keypresses[12];
char sign = '+';
int Exp = 0;

Check_num_for_to_big_or_small(num);

if (num < 0){sign = '-'; num = num * (-1);}

while(--pre_dp){A = A*10;}
while (num >= A){num = num/10.0; Exp += 1;}
while (num <= A){num = num*10.0; Exp -= 1;}

if(sign == '-')num = num * (-1);

Serial.print(num, post_dp);
if(Exp) {Serial.write ('E'); Serial.print(Exp);}
Serial.write(next_char);}




/******************************************************************************************/
float Sc_Num_from_PC(char * num_as_string,char next_char)
{char strln;

pause_WDT;
Serial.flush();   
strln = Serial.readBytesUntil('\r',num_as_string, 20);
resume_WDT;
num_as_string[strln] = 0;
Serial.write(num_as_string);
Serial.write(next_char);
return atof(num_as_string);}











