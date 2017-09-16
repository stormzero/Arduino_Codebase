
// Saved by Simulator for Arduino V0.98.B.1
#define __AVR__

#include <OneWire.h>
// Saved by Simulator for Arduino V0.97B
#include <DallasTemperature.h>
#include <PID_v1.h>

const int RelayPin = 13;  //digital output pin connected to relay
const int ONE_WIRE_BUS = 2;  //Temp Probe on pin 2

OneWire oneWire(ONE_WIRE_BUS); //Setup oneWire instance
DallasTemperature sensors(&oneWire);  //reference Dallas probe

double Temperature1; // My variable to hold current temperature and Input
double Setpoint, Input, Output;  //PID Variables we'll be connecting to

PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT); //Specify the links and initial tuning parameters
int WindowSize = 5000;
unsigned long windowStartTime;

void setup()
{     
  pinMode(RelayPin, OUTPUT);  //I added this hopefully, relay was not turning on
  digitalWrite(RelayPin,LOW);
  //Output = RelayPin;  // I added because Output didn't seem to be defined
  
  // PID setup -----------
  windowStartTime = millis();
  Setpoint = 30; //initialize the variables we're linked to, (Target temperature?), sample had 100
  myPID.SetOutputLimits(0, WindowSize); //tell the PID to range between 0 and the full window size
  myPID.SetMode(AUTOMATIC);   //turn the PID on

  // Temperature setup ------------
  sensors.begin(); // Starts the library, IC Default 9 bit. 
  //If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement

  Serial.begin(9600); 
}

void loop()
{   // Temperature loop -------------
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.print("Temperature for Device 1 is: ");
    Serial.print("windowStartTime    = "); Serial.println(windowStartTime);
      Serial.print("PinOutput  = ");Serial.println(digitalRead(13));
        Serial.print("millis    = ");Serial.println(millis());
                Serial.print("Input    = ");Serial.println(Input);
                        Serial.print("Output    = ");Serial.println(Output);
                                Serial.print("Setpoint    = ");Serial.println(Setpoint);
        Serial.println("");
  Temperature1 = sensors.getTempCByIndex(0);

  // PID loop ----------
  Input = sensors.getTempCByIndex(0);
  myPID.Compute();

  if(millis() - windowStartTime>WindowSize) //turn the output pin on/off based on pid output
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if(Output >( millis() - windowStartTime)) digitalWrite(RelayPin,HIGH);
  else digitalWrite(RelayPin,LOW);

}





