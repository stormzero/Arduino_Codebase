{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 // Simulate(Uno) link sketch to Arduino board here\par
// Saved by Simulator for Arduino V0.98\par
// Saved by Simulator for Arduino V0.98\par
\par
// SerialIn(abc\\n);\par
\par
int i;\par
boolean BTAvailable = true;\par
void setup() \{\par
 // put your setup code here, to run once:\par
 Serial1.begin(9600);\par
\}\par
\par
void loop() \{\par
 // put your main code here, to run repeatedly:\par
 while (Serial1.available()> 0 && BTAvailable) \{\par
  i = Serial1.read();\par
  Serial1.print(i,HEX);\par
 \}\par
\}\par
}
 