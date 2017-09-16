// Simulate(Mega75)
// Saved by Simulator for Arduino V0.97
// Saved by Simulator for Arduino V0.96.A.3


#define OUTPUT 2
#define inPuT 3  

void setup() {
  // put your setup code here, to run once:
 pinMode(4,OUTPUT);
 pinMode(5,INPUT);

 for (int i=0; i<54; i++) {
   analogWrite(i,i*3);
 }
}

void loop() {
  // put your main code here, to run repeatedly:

}
