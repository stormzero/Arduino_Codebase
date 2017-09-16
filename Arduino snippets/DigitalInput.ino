/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
int LED = 13;
int BUTTON = 15;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(LED , OUTPUT);     
  pinMode(BUTTON,INPUT);     
}

void loop() {

    int state = digitalRead(BUTTON);
    if (state>0) {
          digitalWrite(LED , HIGH);   // set the LED on
    } else {
          digitalWrite(LED , LOW);    // set the LED off
    }
}
