#include <SoftwareSerial.h>
// Saved by Simulator for Arduino V0.95C
// Saved by Simulator for Arduino V0.95C
// Saved by Simulator for Arduino V0.95


/*
Blink
Turns on led on for one second, then off for one second, repeatedly
This example code is in public domain.
*/
void setup()
{
  Serial.begin(9600); // open the serial port at 9600 hps:
  loop_a();
}
void loop_a()
{
  int i;
  int N=7;
  DDRB =  DDRB | 0b00111111;
  for(i=0; i<N; i++)
  {
    PORTB = 0b00111111;
    delay(200); //Wait 2 seconds
    PORTB =0b00000000;
    delay(200);
    Serial.print((long)i);
  }
  Serial.print("FINISHED\n");
  
}
void loop()
{
  // this loop is not used
}
