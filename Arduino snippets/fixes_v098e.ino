{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 // Simul1ate1(Uno) link sketch to Arduino board here\par
\par
\par
int i,left,leftChannel;\par
\par
void setup() \{\par
  // put your setup code here, to run once:1\par
\tab leftChannel = 0;\par
\tab left = analogRead(leftChannel);\par
\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
\tab for (int ledpin=70; ledpin<=77; ledpin) \{pinMode(ledpin,OUTPUT);\}\par
\}\par
\par
}
 