// Declaration
// Saved by Simulator for Arduino V0.98B

    byte ledPin[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int direction = 1;
    int LED = 0;
    int LED2 = 0;

void setup()
{
    for (int x=0; x<18; x++)
    {
     pinMode(ledPin[x], OUTPUT);
     digitalWrite(ledPin[x], LOW);
    }
}

void loop()
{
    LED2 = LED+1;

    if (LED2 > 17) {LED2 = LED};

    digitalWrite(ledPin[LED], HIGH);
    digitalWrite(ledPin[LED2], HIGH);
    delay(100);
    digitalWrite(ledPin[LED], LOW);
    digitalWrite(ledPin[LED2], LOW);
    delay(100);

    LED = LED+direction;

    if (LED == 17) {direction = -1};
    if (LED == 0) {direction = 1};

}
