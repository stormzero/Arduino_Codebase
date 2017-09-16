// Simulate Uno
// Saved by Simulator for Arduino V0.97
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.95
// Saved by Simulator for Arduino V0.94E

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("Test "+"This");

int con = 756;
byte b1 = (byte)(con & 255);
Serial.print(" b1 = ");
Serial.println(b1);
int i1 = con & 255;
Serial.print(" i1 = ");
Serial.println(i1);
byte b2 = (byte)i1;
Serial.print(" b2 = ");
Serial.println(b2);
delay(1000);
}
