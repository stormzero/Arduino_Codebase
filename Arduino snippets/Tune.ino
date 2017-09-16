#include <SimpleTimer.h>
// Saved by Simulator for Arduino V0.97A
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SimpleTimer timer;


//------------------------------------------------------------------------------------------------

void setup() 
{
 lcd.begin(16, 2);    // lcd setup
 lcd.print("NA7KR / GW1NGL"); // Print a message to the LCD.
 
}
//------------------------------------------------------------------------------------------------

void loop()
{

  lcd.print("  YT-100  ");  // Print a message to the LCD.
  delay(1000);     // delay boot msg

}

//------------------------------------------------------------------------------------------------
