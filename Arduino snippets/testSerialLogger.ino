{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Calibri;}}
\viewkind4\uc1\pard\f0\fs16 //Simulate(Uno) link sketch to Arduino board here\par
\par
//#include  "test.h"\par
long l = 4000000000;\par
\par
void setup() \{\par
// put your setup code here, to run once:\par
 Serial.begin(9600);\par
\}\par
\par
int i,j,x,y;\par
float f;\par
\par
void loop() \{\par
 i = 1;\par
\par
 for (f=0.0; f<100.0; f+=0.01) \{\par
 l++;\par
  y=sin(pi*f)*120;\par
  Serial.print(y);\par
  Serial.print(',');\par
 Serial.println(i++);\par
 if (i>120) i = -120;\par
 \}\par
\par
//put your main code here, to run repeatedly:\par
\par
  for (int i=0; i<100;i++) \{\par
        Serial.println(i);\par
  \}\par
\par
  for (int i=50; i>-20;i--) \{\par
      Serial.println(i);\par
  \}\par
\}\par
\par
\par
\par
\par
}
 