{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Simulate(Uno) link sketch to Arduino board here\par
\par
    int ledPin[] = \{5,6,7,8,9,10,11\};\par
int in1Pin = 13;\par
int i,j,k;\par
String s;\par
\par
void zeroServo()\{\par
 int i = 4;\par
\}\par
\par
void set_5(void) \{\par
 return(5);\par
\}\par
\par
void test_rtn(void) \{\par
 return(set_5());\par
\}\par
\par
\par
void setup() \{\par
    int j1 = set_5();\par
    j = test_rtn();\par
    \{\par
        s = "12345";\par
        j = atoi(s);\par
    \}  \par
\par
    zeroServo();\par
    Serial.begin(1200);\par
char inChar = (char)Serial.read();\par
\par
    pinmode(in1Pin,OUTPUT);\par
    DigitalWrite(in1Pin, ! FALSE);\par
    pinMode(in1Pin,OUTPUT);\par
    digitalWrite(in1Pin, ! FALSE);\par
\par
    do \par
    \{\par
        i++;\par
        k = k+3;\par
    \} while (k<35);\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
\}\par
\par
}
 