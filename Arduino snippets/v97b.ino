// Simulate(Uno)
// Saved by Simulator for Arduino V0.98B
// Saved by Simulator for Arduino V0.97.B.2

// Error in Simulator but works well on Hardware
#define EINGANG  A0

// Alternative Version for Simulator and Hardware
// const int EINGANG = A0;

#define AUSGANG 3

int value;

void setup() {
  pinMode(AUSGANG, OUTPUT);
}

void loop() {
  value = analogRead(EINGANG);
  value /= 4;
  analogWrite(AUSGANG, value);
}
