// Simulate Uno
// Saved by Simulator for Arduino V0.96.1.1
// Saved by Simulator for Arduino V0.96.1.1
#include <EEPROM.h>

int x,y;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 x = 0;
 y = 1;
}

void loop() {
  // put your main code here, to run repeatedly:

 EEPROM.write(((x*22)+1),0);
 
 Serial.print(EEPROM.read((x*22)+y)); 
 x++;
 y++;

}
