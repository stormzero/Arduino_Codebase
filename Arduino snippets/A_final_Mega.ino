// Saved by Simulator for Arduino V0.98.B.5 refer to arduino.com.au
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
 
#define   DHTPIN                  2   // what pin we're connected to
#define   DHTTYPE             DHT22   // DHT 22  (AM2302)
 
// Adjustable vars
float     RHsensorValue     =     0;  // Initial value for humidity
float     temp1sensorValue  =     0;  // Initial value for temp sensor 1
float     lightLevel        =     0;  // Initial value for light level
long      previousMillis    =     0;  // will store last time heartbeat LED was updated
long      interval          =  2000;  // interval at which to blink heartbeat (milliseconds)
boolean   debug             =  false;  // make true to show on terminal status messages
boolean   ledState          =   LOW;  // ledState used to set the  heatbeat LED
 
// Ethernet variables
byte      mac[]             =   {0x90, 0xA5, 0xDA, 0x02, 0x00, 0x4C};
char      serverName1[]     =   "mail.davestowe.co.uk";
int       port1             =   110;
char      user1[]           =   "dave@davestowe.co.uk";
char      password1[]       =   "d24299886d";
String    answer            =    "";
int       reply             =     0;
unsigned long intervall     =    60; // in seconds
unsigned long timecounter   =     0;
 
// Constants
const int ldrPin            =    A0;  // Pin number for the LDR
const int boardledPin       =    13;  // the number of the LED pin
const int blue              =     5;
const int green             =     6;
const int red               =     7;
const int cls               =    12;  // Clear the screen character
 
EthernetClient client;
DHT dht(DHTPIN, DHTTYPE);
 
// Main Setup-----------------------------------------------------
void setup(){
  if (Ethernet.begin(mac)==0) while(true) flashError();
  pinMode (16,OUTPUT);                                          // Setup pin 16 as the LCD ground
  pinMode (17, OUTPUT);                                         // Setup pin 17 as the LCD power
  digitalWrite(16,LOW);                                         // and write it
  digitalWrite(17,HIGH);                                        // and write it, turning on LCD
  pinMode(boardledPin, OUTPUT);                                 // Set pin 13 as output
  pinMode(green, OUTPUT);                                       // green pin for mail
  pinMode(blue,  OUTPUT);                                       // blue pin for mail
  pinMode(red,   OUTPUT);                                       // red pin for mail
  if(debug) Serial.begin(9600);       // turn on serial port1 if needed
  if(debug) Serial.println("Started....");
 
  Serial1.begin(9600);                                          // Start Serial port1 1 for the LCD
  delay(3000);                                                  // Let the LCD Start
  Serial1.write(cls);                                           // Clear the screen
  Serial1.println("ARDUINO MEGA2560");                          // Status to LCD
  Serial1.println("  IS NOW READY  ");
  delay(1000);
}
 
// Main Loop------------------------------------------------------
void loop(){
  checkforMail();
  unsigned long currentMillis = millis();                    // Set cuurent to now
  if(currentMillis - previousMillis > interval) {            // is it more than interval?
    previousMillis = currentMillis;                          // set previous to now
    readSensors();                                           // Read the humidity
    heartBeat();                                             // do the heartbeat led
    blinkmailCount();                                        // Blink the count of emails
    displayResults();                                        // Show messages on LCD
  }
}
 
//----------------------------------------------------------------
void displayResults() {
  Serial1.write(cls);
  Serial1.print(reply);
  Serial1.print(" mails in box 1");
  Serial1.print("H=");
  Serial1.print(RHsensorValue);
  Serial1.print(" T=");
  Serial1.print(temp1sensorValue);
}
 
// Read Sensors---------------------------------------------------
void readSensors(){
  RHsensorValue = dht.readHumidity();               // Read the humidity value and calibrate
  temp1sensorValue = dht.readTemperature();         // Read the temperature sensor 1
  lightLevel = analogRead(A1);                      // Read the light level
  if(isnan( temp1sensorValue ) || isnan( RHsensorValue )) {
    if (debug) Serial.println("Failed to read DHT");
  }
  else
  {
    if(debug) {
      Serial.print("Relative Humidity %  = ");
      Serial.println(RHsensorValue);                // show if debug on
      Serial.print("Temperature Sensor 1 = ");
      Serial.println(temp1sensorValue);             // show if debug on
      Serial.print("Light Level percent  = ");              
      Serial.println(lightLevel);                   // show if debug on
    }
  }
}
 
// LED on pin 13 shows we are running ok--------------------------
void heartBeat(){
  if ( ledState == LOW ) ledState = HIGH; else ledState = LOW; // toggle led state
  digitalWrite( boardledPin, ledState );                       // set the LED with the ledState of the variable:
}
// ---------------------------------------------------------------
void checkforMail() {
  if ( timecounter < millis() ) {
    // davestowe.co.uk
    if ( client.connect( serverName1, port1 ) > 0 ) {
      client.print("USER ");
      client.println( user1 );
      delay(200);
      isanswerOk();
      client.print("PASS ");
      client.println( password1 );
      delay(500);
      isanswerOk();   
      client.println("STAT");
      delay(500);
      if (client.find("+OK")) {
        reply = client.parseInt();
        if (debug) {
          Serial.print(reply);
          Serial.println(" mails in davestowe.co.uk inbox");
        }
      }
      delay(500);
      client.println("QUIT");
      client.stop(); 
      timecounter = millis() + (intervall*1000);
    } 
  }
}
 
void isanswerOk() {
  char c; 
  answer = "";
  while (client.available())  {
    c = client.read();
    answer += c;
    if(debug) Serial.print(c);
  };
}
 
void flashError() {
  digitalWrite(green,HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(red,  HIGH);
  delay(50);
  digitalWrite(green,LOW);
  digitalWrite(blue, LOW);
  digitalWrite(red,  LOW);
  delay(500);
}
 
void blinkmailCount() {
  int hundreds = (int)(reply / 100);
  int tens     = (int)(reply / 10)-(hundreds*10);
  int ones     = (int)(reply)-(tens*10)-(hundreds*100);
  for (int count=0; count<10; count++) {
    if (hundreds>0) digitalWrite(green ,HIGH);
    if (tens>0)     digitalWrite(blue ,HIGH);
    if (ones>0)     digitalWrite(red ,HIGH);
    delay(100);
    digitalWrite(green,LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red,  LOW);
    delay(200);  
    hundreds--;
    tens--;
    ones--;
    if (hundreds<1 && tens<1 && ones<1) break;
  }
}
