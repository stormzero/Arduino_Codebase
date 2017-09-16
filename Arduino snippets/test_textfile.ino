// Simulate(Due) link sketch to Arduino board here
// Saved by Simulator for Arduino V0.98.D.1
// ??????
int ?????? =12;

#include "unicode.ino"
#include "test2.ino"
#include "test3.ino"

void setup() {
  // put your setup code here, to run once:

	pinMode(DAC0,OUTPUT);
	pinMode(DAC1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int i;
	i++;
 ??????++;
	
	analogWrite(DAC0,4095);
	analogWrite(DAC1,2047);
}




