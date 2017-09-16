
// Saved by Simulator for Arduino V0.98.A.6
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.96.A.3
// Simulate(screw_terminal)

const int dly = 25;
int i;

void setup() {
  // put your setup code here, to run once:
  for (i=0; i<14; i++)
    pinMode(i,OUTPUT);
}

void   pulse(int i) {
    digitalWrite(i,HIGH);
    delay(dly);
    digitalWrite(i,LOW);
    delay(dly);
}

void loop() {
  for (i=0; i<14; i++) 
    pulse(i);
  for (int i=13; i>=0; i--) 
    pulse(i);
}
