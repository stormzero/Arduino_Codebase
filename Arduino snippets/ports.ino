
// Saved by Simulator for Arduino V0.96
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Ethernet.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
EthernetServer server(80);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 SPI.begin();
 lcd.begin(2,16);
 Wire.begin();
 Ethernet.begin();
 server.begin();
 Serial.end();


}

void loop() {
  // put your main code here, to run repeatedly:

}
