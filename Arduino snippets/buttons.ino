{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 int buttonPins[] =\{0,1,2,3,4,5,6,7,8,9,10,11,12,13\};\par
\par
int ledPin =13;\par
\par
int buttonStates[12];\par
\par
int i;\par
\par
void setup()\par
\par
\{\par
\par
  for(i=2;i<13;i++)// DI 0and 1 did not need to be pulled up.\par
\par
    pinMode(buttonPins[i],INPUT_PULLUP);\par
\par
  Serial.begin(9600);\par
\par
\}\par
\par
void loop()\{\par
\par
  for (int i=2;i<13;i++)\{\par
\par
    Serial.print(digitalRead(buttonPins[2]));\par
\par
    Serial.print(digitalRead(buttonPins[3]));\par
\par
    Serial.print(digitalRead(buttonPins[4]));\par
\par
    Serial.print(digitalRead(buttonPins[5]));\par
\par
    Serial.print(digitalRead(buttonPins[6]));\par
\par
    Serial.print(digitalRead(buttonPins[7]));\par
\par
    Serial.print(digitalRead(buttonPins[8]));\par
\par
    Serial.print(digitalRead(buttonPins[9]));\par
\par
    Serial.print(digitalRead(buttonPins[10]));\par
\par
    Serial.print(digitalRead(buttonPins[11]));\par
\par
    Serial.print(digitalRead(buttonPins[12]));\par
\par
    Serial.println(digitalRead(buttonPins[13]));\par
\par
\par
    \{\par
\par
      Serial.write(13);\par
\par
      delay(20);\par
\par
    \}\par
\par
  \}\par
\par
\}\par
\par
}
 