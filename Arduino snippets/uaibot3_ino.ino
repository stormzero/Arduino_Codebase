//
// Saved by Simulator for Arduino V0.96.A.3
//

#include <math.h>
#include <Servo.h> 

const int ledPin =  13;      // the number of the LED pin
const double lB2=400,lA2=400,iBA2=1/800;

Servo servo[6];  // create servo object to control a servo
byte servoPin[6] = {3,5,6,9,10,11};
byte sensorPin[6]={0,1,2,3,4,5}; // analog pin used to connect the potentiometer
int pos[6] = {900,900,900,900,900,900};    // variable to store the servo position 
int sensorValue;    // variable to read the value from the analog pin 
int sensorMax[6] = {0,0,0,0,0,0};
int sensorMin[6] = {1024,1024,1024,1024,1024,1024};
int sensorCen[6], sensorDis[6];
byte i,keys,actualPot;
double x,y,a,b,h2;


void setup() 
{ 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin, LOW);
}

void loop() 
{ 
  x=0.2;
  y=0.1;
  h2=square(x)+square(y);
  a=acos((lB2+lA2-h2)*(iBA2));
  b=acos((lB2-lA2+h2)/(2*lB2*sqrt(h2)))+atan2(y,x);
}
