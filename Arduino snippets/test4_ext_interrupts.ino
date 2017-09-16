// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
// Simulate(Mega)
// Saved by Simulator for Arduino V0.98B

#define MEGA 1
int pin = 13;
int pin2 = 12;

volatile int state = LOW;
volatile int state1 = LOW;
volatile int state2 = LOW;
volatile int state3 = LOW;
volatile int state4 = LOW;
volatile int state5 = LOW;



void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
#ifdef (MEGA)
  pinMode(21, INPUT);
  pinMode(20, INPUT);
  pinMode(19, INPUT);
  pinMode(18, INPUT);
#endif
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  attachInterrupt(0, blink, FALLING);
  attachInterrupt(1, blink2, CHANGE);
#ifdef MEGA
  attachInterrupt(2, blink3, RISING);
  attachInterrupt(3, blink4, CHANGE);
  attachInterrupt(4, blink5, RISING);
  attachInterrupt(5, blink6, FALLING);
#endif
}

void loop()
{
  digitalWrite(pin, state);
  digitalWrite(pin2, state1);
  digitalWrite(6, state2);
  digitalWrite(7, state3);
  digitalWrite(8, state4);
  digitalWrite(9, state5);
}

void blink()
{
  state = !state;
}

void blink2()
{
  state1 = !state1;
}

void blink3()
{
  state2 = !state2;
}

void blink4()
{
  state3 = !state3;
}

void blink5()
{
  state4 = !state4;
}

void blink6()
{
  state5 = !state5;
}



