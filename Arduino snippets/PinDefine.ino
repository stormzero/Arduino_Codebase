
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96.0.1
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 */

#ifdef butterfly
//      Butterfly doesn't number pins as Arduino, so direct register must be accesed
#define pinLlamar PB2
#else
//      we're compiling for Arduino, so Arduino numbering applies.
#define pinLlamar 13
#endif

string stri1= "test";
int i1 = 2;
int i2 = 4;
string s2;



void setup() {                
  pinMode(pinLlamar, OUTPUT);     

 stri1 = "1234";
 s2 = stri1.substring(2,4);
}

void loop() {
  digitalWrite(pinLlamar, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(pinLlamar, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
