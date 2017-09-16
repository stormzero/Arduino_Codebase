// Simulate(Uno)
// Saved by Simulator for Arduino V0.98A

int Tseq = 0;
int ledpins[2] = {2,3};

void setup() {
  // put your setup code here, to run once:
	pinMode(ledpins[0],OUTPUT);
	pinMode(ledpins[1],OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if ((Tseq & 1)==1) {digitalWrite(ledpins[0], HIGH);} else {digitalWrite(ledpins[0],LOW);}
if ((Tseq & 2)==2) {digitalWrite(ledpins[1],HIGH);} else {digitalWrite(ledpins[1] ,LOW);}


if (Tseq & 1==1) {digitalWrite(ledpins[0], HIGH);} else {digitalWrite(ledpins[0],LOW);}
if (Tseq & 2==2) {digitalWrite(ledpins[1],HIGH);} else {digitalWrite(ledpins[1] ,LOW);}

Tseq++;
}
