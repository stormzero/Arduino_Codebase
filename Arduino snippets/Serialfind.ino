// Simulate(Uno) link sketch to Arduino board here
boolean b;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
// SerialIn(1234)
    b = Serial.find("12");
// SerialIn(134)
    b = Serial.find("12");
// SerialIn(1234fg)
    b = Serial.findUntil("12","fg");
// SerialIn(13fg12)
    b = Serial.findUntil("12","fg");
}
