
// Saved by Simulator for Arduino V0.97A
// Saved by Simulator for Arduino V0.97

// include the library code:

#include <LiquidCrystal.h> // ander display
// #include <LiquidCrystal_I2C.h>
// #include <Wire.h> 

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int getal = 1;          // variabele getal
int led = 9;            // variabele led

void setup()                    // eenmalige loop
{ 
 // lcd.init();       // nodig voor mijn display
 // lcd.backlight();  // nodig voor mijn display
  
  pinMode(led, OUTPUT);          // set led poort als output
  lcd.begin(16, 2);              // set up de LCD's aantal kolommen en rijen
  lcd.clear();                     // lcd wissen.
}


void loop() 
{ 
  lcd.clear();                     // lcd wissen.
  lcd.setCursor(1, 0);             // cursor positie
  lcd.print("Arduino, nieuw");     // lcd txt
  lcd.setCursor(0, 1);             // cursor positie.
  lcd.print("Getal=");             // lcd txt
  lcd.setCursor(7, 1);     // nieuwe cursor positie
  lcd.print(getal);        // print variabele op LCD
  delay(1000);                      // wacht loop
  
switch (getal)
  {
    case 5: ledbesturing();
    break;
    case 2: drukknop();;
    break;
  }
  getal++;         // variabele met 1 ophogen
}

////////////////  funktie 1 /////////////////
void drukknop()
{
//lcd.clear();
lcd.setCursor(0, 1);     // cursor positie
lcd.print("sub_routine");       // txt lcd
delay(1000);
}

////////////////  funktie 2 /////////////////
void ledbesturing ()
{
delay(1000);             // wacht laat getal 20 zien
     getal = 0;               // variabele getal wordt weer 1
     digitalWrite(led, HIGH); // poort led wordt hoog.
     lcd.setCursor(0, 1);     // cursor positie
     lcd.print("LED rood aan");       // txt lcd 
     delay(1500);             // wacht loop voor lcd txt
     digitalWrite(led, LOW);          // poort led laag
     lcd.setCursor(0, 1);     // cursor positie
     lcd.print("LED rood uit");       // txt lcd
     delay(1500);                     // wacht loop voor lcd txt  
}
