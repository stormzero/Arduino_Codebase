{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 /*\par
  LiquidCrystal Library - setCursor\par
 \par
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal\par
 library works with all LCD displays that are compatible with the \par
 Hitachi HD44780 driver. There are many of them out there, and you\par
 can usually tell them by the 16-pin interface.\par
 \par
 This sketch prints to all the positions of the LCD using the\par
 setCursor(0 method:\par
 \par
  The circuit:\par
 * LCD RS pin to digital pin 12\par
 * LCD Enable pin to digital pin 11\par
 * LCD D4 pin to digital pin 5\par
 * LCD D5 pin to digital pin 4\par
 * LCD D6 pin to digital pin 3\par
 * LCD D7 pin to digital pin 2\par
 * LCD R/W pin to ground\par
 * 10K resistor:\par
 * ends to +5V and ground\par
 * wiper to LCD VO pin (pin 3)\par
 \par
 Library originally added 18 Apr 2008\par
 by David A. Mellis\par
 library modified 5 Jul 2009\par
 by Limor Fried (http://www.ladyada.net)\par
 example added 9 Jul 2009\par
 by Tom Igoe \par
 modified 22 Nov 2010\par
 by Tom Igoe\par
 \par
 This example code is in the public domain.\par
 \par
 http://www.arduino.cc/en/Tutorial/LiquidCrystal\par
 */\par
\par
// include the library code:\par
#include <LiquidCrystal.h>\par
\par
// these constants won't change.  But you can change the size of\par
// your LCD using them:\par
const int numRows = 2;\par
const int numCols = 16;\par
\par
// initialize the library with the numbers of the interface pins\par
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);\par
\par
void setup() \{\par
  // set up the LCD's number of columns and rows: \par
  lcd.begin(numCols,numRows);\par
\}\par
\par
void loop() \{\par
  // loop from ASCII 'a' to ASCII 'z':\par
  for (int thisLetter = 'a'; thisLetter <= 'z'; thisLetter++) \{\par
    // loop over the columns:\par
    for (int thisCol = 0; thisCol < numRows; thisCol++) \{\par
      // loop over the rows:\par
      for (int thisRow = 0; thisRow < numCols; thisRow++) \{\par
        // set the cursor position:\par
        lcd.setCursor(thisRow,thisCol);\par
        // print the letter:\par
        lcd.write(thisLetter);\par
        delay(50);\par
      \}\par
    \}\par
  \}\par
\}\par
\par
\par
}
 