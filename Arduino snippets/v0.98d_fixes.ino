{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}{\f1\fswiss\fcharset204{\*\fname Arial;}Arial CYR;}}
\viewkind4\uc1\pard\f0\fs16 // Simulate(Uno) link sketch to Arduino board here\par
\par
//\f1\'cf\'f0\'e8\'e2\'e5\'f2, \'ea\'e0\'ea \'e4\'e5\'eb\'e0. \'df\'e2\'eb\'ff\'fe\'f2\'f1\'ff \'eb\'e8 \'ee\'ed\'e8 \'e2\'e0\'f8\'e8\'ec\'e8 \'e4\'f0\'f3\'e7\'fc\'ff\'ec\'e8 \'e8\'eb\'e8 \'f2\'ee, \'f7\'f2\'ee \'f2\'e0\'e9\'ed\'e0\'ff \'ef\'ee\'eb\'e8\'f6\'e8\'ff \'f1\'eb\'e5\'e4\'f3\'e5\'f2 \'e7\'e0 \'e2\'e0\'ec\'e8\f0\par
\par
boolean flagej,b;\par
int data1,i;\par
string s = "123";\par
float f,sensorValue = 1023;\par
char c = '1';\par
#define N_RTX 2\par
int d,dc,t=1;\par
byte ttime[3];\par
#define PIN_DC 4\par
short short_int=1234;\par
int valore =23;\par
signed short int s = 2;\par
\par
int wct2ttime(byte a) \par
\{\par
\tab return 3;\par
\}\par
\par
int sbr(void)\par
\{\par
  if (t<wct2ttime(ttime[0])) return N_RTX-1;\par
  return 5;\par
\}\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
\tab float voltage = sensorValue*(5.0/1023.0);\par
      pinMode(PIN_DC,OUTPUT);\par
      dc = 1;\par
      digitalWrite(PIN_DC,dc);\par
      dc = 0;\par
      digitalWrite(PIN_DC,dc);\par
\tab b = (flagej==1);\par
\tab data1 = 100;\par
\tab float data = data1 *(5.0/1023.0)*2.33;\par
\tab Serial.begin(9600);\par
\tab Serial.println('a');\par
\tab Serial.println("test"+s);\par
  Serial.println(F("Ready"));\par
  Serial.println(valore);\par
\tab f = log(sensorValue);\par
      c = '0';\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly\par
\par
  if (c=='0') \{\par
      Serial.println("Here");\par
      c++;\par
  \}\par
\par
  d = sbr();\par
\}\par
\par
}
 