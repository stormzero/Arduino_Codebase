{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 // Pin 13 has an LED connected on most Arduino boards.\par
// give it a name:\par
int led = 13;\par
\par
\par
// the setup routine runs once when you press reset:\par
void setup() \{                \par
  // initialize the digital pin as an output.\par
  pinMode(led, OUTPUT); \par
  Serial.begin(9600);\par
  Serial.println("Due Blink v0.90" );\par
  Serial.println(F("Ready"));\par
\}\par
\par
// the loop routine runs over and over again forever:\par
void loop() \{\par
  \par
  if (Serial.available()>1) \{\par
    led = (Serial.read()-'0')*10;\par
    led += (Serial.read()-'0');\par
    pinMode(led, OUTPUT); \par
    Serial.print("Blink led = ");\par
    Serial.println(led,DEC);\par
  \}\par
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)\par
  delay(100);               // wait for a second\par
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW\par
  delay(100);               // wait for a second\par
\}\par
\par
\par
\par
}
 