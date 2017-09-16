// Simulate Uno
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D

//SimulateLCD(126,80,360,127,3,3,65407,0,12632256) 

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int backLight = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(20,4);              // columns, rows.  use 20,4 for a 20x4 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(6,0);
  lcd.print("Spd  Ltd");    // This Item Passes Fine
  lcd.setCursor(5,1);
  lcd.print("Electronic");  // This Item Passes Fine
  lcd.setCursor(2,2);
  lcd.print("Throttle Control");    // This Item Throws an error???
  lcd.setCursor(4,3);
  lcd.print("Version  1.0");   // This Item Throws an error also???
}

void loop() {
  // put your main code here, to run repeatedly:

}
