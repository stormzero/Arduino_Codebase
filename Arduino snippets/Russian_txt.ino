{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Times New Roman;}}
\viewkind4\uc1\pard\f0\fs-24 // Simulate(Due) link sketch to Arduino board here\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
\tab pinMode(DAC0,OUTPUT);\par
\tab pinMode(DAC1,OUTPUT);\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
int i;\par
\tab i++;\par
\tab analogWrite(DAC0,4095);\par
\tab analogWrite(DAC1,2047);\par
\}\par
\par
\par
\par
\par
\par
}
 