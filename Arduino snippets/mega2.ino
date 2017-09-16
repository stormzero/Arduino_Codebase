
// Saved by Simulator for Arduino V0.98B
    int direction = 1;
    int LED = 1;
    int LED2 = 0;

void setup()
{
    DDRF = 255;
    PORTF = 255;
    delay(200);
    PORTF = 0;
    delay(500);



}

void loop()
{
    if (LED > 128) {LED = 1};

    PORTF = LED;

    LED = LED << 1;

    delay(500);

/*
    if (direction == 1) {LED2 = LED-1};
    if (LED2 < 1) {LED2 = LED};

    if (direction == -1){LED2 = LED+1};
    if (LED2 > 13) {LED2 = LED};

    digitalWrite(ledPin[LED], HIGH);
    digitalWrite(ledPin[LED2], HIGH);
    delay(2000);
    digitalWrite(ledPin[LED], LOW);
    digitalWrite(ledPin[LED2], LOW);
    delay(1000);

    LED = LED+direction;

    if (LED == 13) {direction = -1};
    if (LED == 0) {direction = 1};

  digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);              // wait for a second
*/

}
