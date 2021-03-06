{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Simulate(LCD)\par
// Saved by Simulator for Arduino V0.97.B.2\par
// Arduino Shields LCD Shield demo code\par
// www.arduino.com.au\par
// v1.02 21-Sept-2011 - markup comments, add version number \par
// tested on Arduino Uno,Mega\par
\par
#include <LiquidCrystal.h> // necessary to access LCD library\par
\par
\par
// initialize the library with the numbers of the interface pins\par
LiquidCrystal lcd(8, 9, 10, 4,5,6,7); // use 4 pin interface so serial can be used\par
const int BeeperPin = 11;      // piezo beeper pin\par
const int BacklightPin = 12;   // backlight for LCD pin\par
\par
const int switch1 = 0; // left switch\par
const int switch2 = 1;\par
const int switch3 = 2;\par
const int switch4 = 3; // right switch\par
\par
byte serialin; // read in serial data to be sent to LCd\par
unsigned long time; // note time needs to be unsigned longs\par
int i=0;  \par
\par
void setup() // standard arduino setup initializing loop\par
\{\par
  \par
  Serial.begin(9600);        // initialize the serial communication:\par
  Serial.print("LCD Shield for Arduino Version 1.02");\par
  pinMode(BeeperPin, OUTPUT);   // initialize Beeper output\par
  pinMode(BacklightPin, OUTPUT); // initialize backlight output\par
  digitalWrite(BacklightPin, 1); // turn on backlight\par
  lcd.begin(16,2); // set LCD to 16chars x 2 rows\par
  //         0123456789012345 - count 16 characters on display\par
  lcd.print("Arduino Shields!"); // print on both lines\par
  lcd.setCursor(0,1);\par
  //         0123456789012345 - count 16 characters on display\par
  lcd.print("Version 1.02");\par
  time = millis(); // load timer to turn off in 1 second\par
\}\par
\par
\par
\par
void loop() // standard arduino loop\par
\{\par
    lcd.backlight(100-i);\par
\tab i += 5;\par
    if (i>100) \{\par
    \tab i = 0;\par
    \} \par
\par
  if (millis()>(time+2000)) \{ // if 2 seconds have passed\par
    digitalWrite(BacklightPin, 0); // turn off backlight\par
    lcd.home();              /// return invisible cursor to top left\par
    lcd.print("                 ");// clear LCD top line\par
    lcd.setCursor(0,1);\par
    time = millis()+4000; // repeat every 5 seconds\par
  \}\par
  \par
  if (Serial.available()) \{   // check if data has been sent from the computer:\par
    serialin = Serial.read(); // read in 9600 character\par
    lcd.write(serialin); // copy serial char to LCD line 2\par
    digitalWrite(BacklightPin, 1); // turn on backlight\par
    time = millis(); // set to clear in 10 seconds\par
  \}\par
\par
  if (analogRead(switch1)<10) \{    // check switch1 left\par
    digitalWrite(BacklightPin, 1);\par
    lcd.home();\par
    lcd.print("Switch1 - 1kHz");\par
    tone(BeeperPin,1000,20);\par
    time = millis();      \par
  \}\par
\par
  if (analogRead(switch2)<10) \{    // check switch2 second from left\par
    digitalWrite(BacklightPin, 1);\par
    lcd.home();\par
    lcd.print("Switch2 - 2kHz");\par
    tone(BeeperPin,2000,20);\par
    time = millis();      \par
  \}\par
\par
  if (analogRead(switch3)<10) \{    //  check switch3 second from right\par
    digitalWrite(BacklightPin, 1);\par
    lcd.home();\par
    lcd.print("Switch3 - 3kHz");\par
    tone(BeeperPin,3000,20);\par
    time = millis();      \par
  \}\par
\par
  if (analogRead(switch4)<10) \{    // check switch4 right\par
    digitalWrite(BacklightPin, 1);\par
    lcd.home();\par
    lcd.print("Switch4 - 4kHz");\par
    tone(BeeperPin,4000,20);\par
    time = millis();      \par
  \}\par
\}\par
\par
\par
}
 