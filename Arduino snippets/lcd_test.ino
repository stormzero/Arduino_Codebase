// SimulateLCD(39,50,480,163,3,4,8388608,16777215,16711680)
// Saved by Simulator for Arduino V0.97.B.2
// x,y,w,h,pixel w,p-

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
 lcd.begin(20,4);


}

void loop() {
  // put your main code here, to run repeatedly:

    lcd.home(); 
   for (int i=32; i<52; i++)
        lcd.write(i);
    lcd.setCursor(0,1);
    for (int i=52; i<72; i++)
        lcd.write(i);
    lcd.setCursor(0,2);
    for (int i=72; i<92; i++)
        lcd.write(i);
    lcd.setCursor(0,3);
    for (int i=92; i<112; i++)
        lcd.write(i);
    lcd.setCursor(0,0);
    for (int i=112; i<132; i++)
        lcd.write(i);

}
