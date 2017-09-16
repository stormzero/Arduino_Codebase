// Simulate Uno

#define NUM_PINS 4
 
struct Pinfo
{
  int pinNum;
  boolean lastValue;
  boolean thisValue;
//  boolean lastPinState;
//  boolean pinState;
  unsigned long changeTime;
};

Pinfo pins1= {20, false, false, 0};   // ShowTime pin
Pinfo pins2;   // ShowTime pin
Pinfo pins3[2];   



 
Pinfo pins[NUM_PINS] = {{20, false, false, 0},   // ShowTime pin
                        {19, false, false, 0},   // Calibration pin
                        {18, false, false, 0},   // C/F pin
                        {17, false, false, 0}};  // OK pin

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
