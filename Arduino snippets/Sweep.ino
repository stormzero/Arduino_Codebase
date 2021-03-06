{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 // Sweep\par
// by BARRAGAN <http://barraganstudio.com> \par
// This example code is in the public domain.\par
\par
\par
#include <Servo.h> \par
 \par
Servo myservo;  // create servo object to control a servo \par
                // a maximum of eight servo objects can be created \par
 \par
int pos = 0;    // variable to store the servo position \par
 \par
void setup() \par
\{ \par
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object \par
\} \par
 \par
 \par
void loop() \par
\{ \par
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees \par
  \{                                  // in steps of 1 degree \par
    myservo.write(pos);              // tell servo to go to position in variable 'pos' \par
    delay(1);                       // waits 15ms for the servo to reach the position \par
  \} \par
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees \par
  \{                                \par
    myservo.write(pos);              // tell servo to go to position in variable 'pos' \par
    delay(1);                       // waits 15ms for the servo to reach the position \par
  \} \par
\} \par
\par
}
 