{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\f0\fs-24 // Simulate(Uno) link sketch to Arduino board here\par
\par
String mystring = "10,20,30,40";\par
\par
\par
\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
\tab Serial.begin(9600);\par
\pard int commaA = mystring.indexOf(',');\par
int commaB = mystring.indexOf(',', commaA+1);\par
\pard int commaC = mystring.lastIndexOf(',');\par
Serial.println("A:" + commaA);\par
Serial.println("B:" + commaB);\par
Serial.println("C:" + commaC);\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
\}\par
\par
}
 