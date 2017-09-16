
void setup()
{
  Serial.begin(9600);
 
  int a = 258;
  int b = 0;
 
  byte Hint = highByte(a);
  byte Lint = lowByte(a);
 
  b = word(Hint,Lint);
  Serial.println(a);
  Serial.println(Hint);
  Serial.println(Lint);
  Serial.println(b);
}
// test
 

void loop()
{
int j;
float f;
    j = int(123.456);
   f = float(234);
}
