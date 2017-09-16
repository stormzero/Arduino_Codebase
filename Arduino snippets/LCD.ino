// Simulate(LCD)
// Saved by Simulator for Arduino V0.97.B.2
// Arduino Shields LCD Shield demo code
// www.arduino.com.au
// v1.02 21-Sept-2011 - markup comments, add version number 
// tested on Arduino Uno,Mega

#include <LiquidCrystal.h> // necessary to access LCD library


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 4,5,6,7); // use 4 pin interface so serial can be used
const int BeeperPin = 11;      // piezo beeper pin
const int BacklightPin = 12;   // backlight for LCD pin

const int switch1 = 0; // left switch
const int switch2 = 1;
const int switch3 = 2;
const int switch4 = 3; // right switch

byte serialin; // read in serial data to be sent to LCd
unsigned long time; // note time needs to be unsigned longs
  
void setup() // standard arduino setup initializing loop
{
  
  Serial.begin(9600);        // initialize the serial communication:
  Serial.print("LCD Shield for Arduino Version 1.02");
  pinMode(BeeperPin, OUTPUT);   // initialize Beeper output
  pinMode(BacklightPin, OUTPUT); // initialize backlight output
  digitalWrite(BacklightPin, 1); // turn on backlight
  lcd.begin(16,2); // set LCD to 16chars x 2 rows
  //         0123456789012345 - count 16 characters on display
  lcd.print("Arduino Shields!"); // print on both lines
  lcd.setCursor(0,1);
  //         0123456789012345 - count 16 characters on display
  lcd.print("Version 1.02");
  time = millis(); // load timer to turn off in 1 second
}



void loop() // standard arduino loop
{

  if (millis()>(time+2000)) { // if 2 seconds have passed
    digitalWrite(BacklightPin, 0); // turn off backlight
    lcd.home();              /// return invisible cursor to top left
    lcd.print("                 ");// clear LCD top line
    lcd.setCursor(0,1);
    time = millis()+4000; // repeat every 5 seconds
  }
  
  if (Serial.available()) {   // check if data has been sent from the computer:
    serialin = Serial.read(); // read in 9600 character
    lcd.write(serialin); // copy serial char to LCD line 2
    digitalWrite(BacklightPin, 1); // turn on backlight
    time = millis(); // set to clear in 10 seconds
  }

  if (analogRead(switch1)<10) {    // check switch1 left
    digitalWrite(BacklightPin, 1);
    lcd.home();
    lcd.print("Switch1 - 1kHz");
    tone(BeeperPin,1000,20);
    time = millis();      
  }

  if (analogRead(switch2)<10) {    // check switch2 second from left
    digitalWrite(BacklightPin, 1);
    lcd.home();
    lcd.print("Switch2 - 2kHz");
    tone(BeeperPin,2000,20);
    time = millis();      
  }

  if (analogRead(switch3)<10) {    //  check switch3 second from right
    digitalWrite(BacklightPin, 1);
    lcd.home();
    lcd.print("Switch3 - 3kHz");
    tone(BeeperPin,3000,20);
    time = millis();      
  }

  if (analogRead(switch4)<10) {    // check switch4 right
    digitalWrite(BacklightPin, 1);
    lcd.home();
    lcd.print("Switch4 - 4kHz");
    tone(BeeperPin,4000,20);
    time = millis();      
  }
}

