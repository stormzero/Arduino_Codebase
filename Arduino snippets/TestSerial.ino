{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Simulate(Uno) link sketch to Arduino board here\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
    Serial.begin(9600);\par
\}\par
\par
byte incomingByte;\par
\par
\par
void loop() \{\par
\par
        // send data only when you receive data:\par
        if (Serial.available() > 0) \{\par
                // read the incoming byte:\par
                incomingByte = Serial.read();\par
\par
                // say what you got:\par
                Serial.print("I received: ");\par
                Serial.println(incomingByte, DEC);\par
        \}\par
\}\par
\par
\par
}
 