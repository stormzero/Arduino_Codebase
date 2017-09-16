int pin = 13;
// Saved by Simulator for Arduino V0.98
int inp = 2;
volatile int state = LOW;

void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(inp, INPUT);
  attachInterrupt(0, blink, CHANGE);
}

void loop()
{
  digitalWrite(pin, state);
}

void blink()
{
  state = !state;
}
