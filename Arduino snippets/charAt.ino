// Simulate(Uno) link sketch to Arduino board here
String osS="A string object";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(osS);
Serial.println(osS.substring(0));
Serial.println(osS.substring(2,4));
Serial.println(osS.charAt(4));
}
void loop() {
  // put your main code here, to run repeatedly:
}
 
//And here is the serial output :
//A string object
//A string object
//st
//-1