{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // SimulateLCD(39,50,480,163,3,4,8388608,16777215,16711680)\par
\par
// x,y,w,h,pixel w,p-\par
\par
// include the library code:\par
#include <LiquidCrystal.h>\par
\par
// initialize the library with the numbers of the interface pins\par
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
 lcd.begin(20,4);\par
\par
\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
    lcd.home(); \par
   for (int i=32; i<52; i++)\par
        lcd.write(i);\par
    lcd.setCursor(0,1);\par
    for (int i=52; i<72; i++)\par
        lcd.write(i);\par
    lcd.setCursor(0,2);\par
    for (int i=72; i<92; i++)\par
        lcd.write(i);\par
    lcd.setCursor(0,3);\par
    for (int i=92; i<112; i++)\par
        lcd.write(i);\par
    lcd.setCursor(0,0);\par
    for (int i=112; i<132; i++)\par
        lcd.write(i);\par
\par
\}\par
\par
}
 