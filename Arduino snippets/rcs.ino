// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
// Simulate Uno
// Saved by Simulator for Arduino V0.98A



#include "rcs.ino" // doesn't include already included files now!

int i;
float f;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

 i = 1;
 i = 10/0;
 i /=0;

 f = 1.0;
 f = 1.0/0.0;
 f /= 0.0;

// 40 times recursion internal Simulator check
 i = 1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17+18+19+20+21+22+23+24+25+26+27+28+29+30+31+32+33+34+35+36+37+38+39+40; // test for 40x recursive check

  
}
