{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}{\f1\fnil\fcharset204{\*\fname Courier New;}Courier New CYR;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Simulate(Due) link sketch to Arduino board here\par
// \f1\'ef\'f0\'e8\'e2\'e5\'f2\par
\f0 int \f1\'ef\'f0\'e8\'e2\'e5\'f2 =12;\par
\f0\par
void setup() \{\par
  // put your setup code here, to run once:\par
\par
    pinMode(DAC0,OUTPUT);\par
    pinMode(DAC1,OUTPUT);\par
    Serial.begin(9600);\par
    Serial.println("\f1\'ef\'f0\'e8\'e2\'e5\'f2");\par
\f0\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
int i;\par
    i++;\par
 \f1\'ef\'f0\'e8\'e2\'e5\'f2++;\par
\f0     \par
    analogWrite(DAC0,4095);\par
    analogWrite(DAC1,2047);\par
\}\par
\par
\par
}
 