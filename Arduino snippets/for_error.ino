// Simulate(Uno)
// Saved by Simulator for Arduino V0.98.A.7
// Saved by Simulator for Arduino V0.98.A.6

int fwd = 3;
int speedUp = 250;
int minS = 5;

void fGo(){ //go fwd until full speed
  for(int i=minS; i<256; i++){  //count from min speed to 255
    analogWrite(fwd,i);
    delay(speedUp);
  } 
}

void setup() {
  // put your setup code here, to run once:
 fGo();

}

void loop() {
  // put your main code here, to run repeatedly:

}
