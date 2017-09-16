// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = A0;    // select the input pin for the potentiometer
int valvePin = 7;      // select the pin for the LED
int buttonPin = 6;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int buttonState = 0;
unsigned long timer = 0;
unsigned long lastMillis = 0;
int openDelay = 5000;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  // declare the ledPin as an OUTPUT:
  pinMode(valvePin, OUTPUT);
   // Turn on the display:
  lcd.display();
  Serial.begin(57600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // Print a message to the LCD.
  lcd.home();
  
  //check humidity sensor or button
  if ((sensorValue>10)||(buttonState == HIGH)) {
    timer=millis()+openDelay;
  }
  
  //timer implementation
  if (timer>millis()) {
      digitalWrite(valvePin, HIGH);
      displayOpenValve();
  } else {
      digitalWrite(valvePin, LOW);  
      displayClosedValve();
  }
  
  //case overflow
  if (millis()<lastMillis) {
    timer=0;
  }
  lastMillis=millis();
}

void displayOpenValve() {
  lcd.setCursor(0,0);
  lcd.print("Open:");
  float pos=(float) (timer-millis())/openDelay;
  pos=pos*11;
  lcd.setCursor(5,0);
  lcd.print("***********");
  for (int c=5+pos; c<=16-(pos); c++) {
    lcd.setCursor(c,0);
    lcd.print(" ");
    Serial.println(c);
  }
}

void displayClosedValve() {
       lcd.print("Closed:" + String(sensorValue) + "   ");
}
