#include <LiquidCrystal.h>

//#include "EmonLib.h"             // Include Emon Library
//EnergyMonitor emon1;             // Create an instance
//EnergyMonitor emon2;

// Generator control code for Skaterdad


// TIMEOUTS
const long STARTDELAY = 3000; // startup delay
const long COOLDOWN = 120000;  // 2 min; should increase to probably 5 min.
const long SHORTCOOLDOWN = 120000; // 2 min, this is only if load never applied.

const long TRANSFER2GENDELAY = 10000;  // delay between power restoration and transfer 
const long TRANSFER2ACDELAY = 10000;
const long WEEKLYTESTDELAY = 604800000;  // weekly
const long WEEKLYTESTRUNTIME = 900000;  // 15 minutes

const long DAILYCHARGETIME = 2000000;   // 1 hour
const long DAILYCHARGEDELAY = 86400000;  // every day


// STATES
#define UNKNOWN  0   // unknown state.
#define LINEPOWER   1    // running on line power
#define LINEPOWERLOSS  2 // line power loss, waiting to start
#define GENSTART  3      // generator start, waiting for power
#define GENRUN   4       // on generator power
#define GENCOOL  5      // Power restored, cooldown
#define floatcharge 10
#define genteststart 11
#define gentestrun 12


// set pin numbers:
const int ledPin =  13;      // the number of the LED pin
const int GenAC1 = 2;        // Generator power available; sensing wire E1 or E2
//const int GenAC2 = 2;        // Generator power available (not used! not attached)
              // Note in above, HIGH = no generator power; low=gen power is availble
const int LineAC1 = 3;       // AC Line Input 1st Phase (from N1A/F1/N1) Utility Sense
const int ChargeRelay = 4;
//const int LineAC2 = 4;      // AC Line input 2nd phase (from N1A/F2/N2)  Could be used, attached.
              // but probably not needed; and makes the states needlessly complex...  Since there is only 1 phase
              // on the pole, if one goes out so does the other...
              // Note in above, HIGH = loss of power; low= line power available
const int ControlTransferRelay = 5;  // Toggle this HIGH/LOW for transfer!  Low = Transfer, High = line power
const int GeneratorRun = 6;    // turn this ON (LOW) to get a generator to start 
const int Button = 1;       // 5 buttons on resistor's  on A1 (see http://www.r3cube.com/driver/LCDshield_v1_1.pdf)
const int GenBatt = 2;      // Generator battery level in A3  
const long Week = 604800000;  // Mills in a week

unsigned long waitUntil = 0;   // important that this stay unsigned long per examples of 
              // how to avoid rollover problems every 49 days...
unsigned long waitUntilCharge = DAILYCHARGEDELAY; // initial value
unsigned long waitUntilTest = WEEKLYTESTRUNTIME; // initial value
unsigned long LostMillis = 0;
unsigned long CoolStartMillis = 0;
unsigned long CM = 0;

// Variables will change:
int  ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long LastGenRun = 0;        // Last time the generator was test run
long LastChargeRun = 0;
int  PowerState = 0;              // power state
int LastPowerState = 0;
// system states


// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() 
{
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);    
  pinMode(GenAC1, INPUT);       // Generator power available; sensing wire E1 or E2
  digitalWrite(GenAC1, HIGH);
//  pinMode(GenAC2, INPUT);        // Generator power available (not used!)
  pinMode(LineAC1, INPUT);        // AC Line Input 1st Phase (from N1A/F1/N1) Utility Sense
  digitalWrite(LineAC1, HIGH);
//  pinMode(LineAC2, INPUT);       // AC Line input 2nd phase (from N1A/F2/N2)
  pinMode(ControlTransferRelay, OUTPUT);   // Toggle this HIGH/LOW for transfer!
    digitalWrite(ControlTransferRelay, HIGH); 
  pinMode(GeneratorRun, OUTPUT);    // turn this ON(LOW) to get a generator to start
    digitalWrite(GeneratorRun, HIGH); 
  //pinmode(GenLoad1, INPUT);     // Generator load comes in A1
  //pinmode(GenLoad2, INPUT);     //Generator load comes in A2
  //pinmode(GenBatt, INPUT);    // Generator battery level in A3  


  Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("Startup");
    
// source:emonlib 
 // emon1.voltage(2, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
 // emon1.current(1, 111.1);       // Current: input pin, calibration.
  //emon1.voltage(2, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
 //
}  // end of SETUP

void loop()
{
   delay(500);

// energymonitor  -- prototype area to monitor current in 2 legs... main intent here is if current nearing 
// capacity of the generator, shut down certain loads.
// Need to build the hardware first to see what thresholds are needed, and calibrate.
// unfinished.
// source:emonlib

//  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//  emon1.serialprint();           // Print out all variables
//  emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//  emon2.serialprint();           // Print out all variables



switch (PowerState) 
{
  case 0:   // unknown power state at power-up.
      waitUntilCharge = DAILYCHARGEDELAY; // initial value
      waitUntilTest = WEEKLYTESTRUNTIME; // initial value
     
      if (digitalRead(LineAC1) == LOW)
        PowerState = 1;
      else
        {
           CM = millis();    
           waitUntil =  CM + STARTDELAY;
           PowerState = 2;  // if AC power not present, then must be no power...
        }
      break;

  case 1:  // 1 = line power
      //     digitalWrite(ledPin, HIGH);
      if (digitalRead(LineAC1) == HIGH)      // lost power
        {
           PowerState = 2;
           CM = millis();    
           waitUntil =  CM + STARTDELAY;
         }
      CM=millis(); 
      if ((long)(CM - waitUntilCharge) >= 0) 
         {
            CM = millis();    
            waitUntil =  CM + DAILYCHARGETIME;
            PowerState = 10;    // charging
         }
      CM=millis(); 
      if ((long)(CM - waitUntilTest) >=0)
         {
            PowerState = 11;    // weekly test
         }     
  break;
  
  case 2:     // 2 = loss of line power, waiting to confirm
      CM=millis(); 
      if ((long)(CM - waitUntil) > 0)
          {  // 5 seconds have elapsed, so we will move to state 3 to start gen.
            PowerState = 3;
            digitalWrite(GeneratorRun, LOW);  // start generator attempt
          }        
      
      if (digitalRead(LineAC1) == LOW)    // power restored
      { 
          PowerState = 1; 
      }                         // so go back to state  1 as we have not started gen.
  break;
  
  
  case 3:     // 3 = Previous state already turned on generator, 
              // waiting for it to come online...
 
      if (digitalRead(GenAC1) == LOW)    // Generator power has come up...
      {
          CM = millis();    
          waitUntil =  CM + TRANSFER2GENDELAY;
          PowerState = 4;  // Generator is now on; wait for delay before starting.
          waitUntilCharge = CM + DAILYCHARGEDELAY; // Reset next generator charge time
          waitUntilTest = waitUntilTest + WEEKLYTESTRUNTIME; // Reset next generator test to + 1 week
      }
      if (digitalRead(LineAC1) == LOW)
      {
          CM = millis();    
          waitUntil =  CM + SHORTCOOLDOWN;
          PowerState = 7;   // cooldown
      } 
      
  case 4:    // Generator ONLINE, wait until TRANSFER2GENDELAY expires, then transfer
     CM=millis(); 
     if ((long)(CM - waitUntil) >= 0)
     {
       if (digitalRead(LineAC1) == LOW)  // power was arelady restored
             {
                 waitUntil =  CM + SHORTCOOLDOWN;
                  PowerState = 7;                // go to cooldown cycle
             }
       else
             {
                 digitalWrite(ControlTransferRelay, LOW);    // Hit the transfer relay!
                 PowerState = 5;
             }
     }
  break;
  
  case 5:     // 5 = on generator power
      if (digitalRead(LineAC1) == LOW)     // Power restored...
      {
          CM = millis();    
          waitUntil =  CM + TRANSFER2ACDELAY;
          PowerState = 6;
      }
          
  case 6:   // AC Line is on... wait for a while to see if it stays on before entering cooldown.
      CM=millis(); 
      if ((long)(CM - waitUntil) >= 0) 
      {    
           digitalWrite(ControlTransferRelay, HIGH);
           PowerState = 7;  // cooldown
           // COOLDOWN;
      }
      if (digitalRead(LineAC1) == HIGH)   // power lost again
      {
          PowerState = 5;
      }
  break;
  
  case 7:     // 7 = power restored, start cooldown
      CM=millis(); 
      if ((long)(CM - waitUntil) >= 0) 
      {
          PowerState = 1;
          digitalWrite(GeneratorRun, HIGH);    // Shutdown generator
          digitalWrite(ControlTransferRelay, HIGH);  // just ensure the relay is on AC power
      }
      if (digitalRead(LineAC1) == HIGH) // Lost Power during Cooldown
      {
           PowerState = 5;        //
           digitalWrite(ControlTransferRelay, LOW);  // transfer back to GEN power
      } 
  break;

  case 10:    //  CHARGE MODE
      if (digitalRead(LineAC1) == HIGH)   // lost AC Power : Cancel the charge!
      {
        digitalWrite(ChargeRelay, HIGH);   // shutdown charger
        PowerState = 2;
        waitUntilCharge = waitUntilCharge + DAILYCHARGEDELAY;
       }
       CM=millis(); 
       if ((long)(CM - waitUntil) >=0 )
       {
           PowerState = 1;
           waitUntilCharge = waitUntilCharge + DAILYCHARGEDELAY;
       }
  break;



  
 default:    // invalid!!
   Serial.println ("PowerState is INVALID... BUG!!!");
  break;  
}


// SHOW THE CURRENT STATE IN SERIAL PORT, and Print on LCD screen...
if (LastPowerState != PowerState)
{
    Serial.print("NewPowerState "); 
    Serial.print (PowerState) ;
    switch (PowerState) 
    {
      case 0: 
        Serial.println (" UnknownState"); 
      break;
      case 1: 
        Serial.println (" OnACPower");
        lcd.setCursor(0, 1);
        //lcd.print((CM=millis())/1000); 
        lcd.print("1 LINE POWER    ");
      break;
      case 2: 
        Serial.println ("InitialLossOfACPower"); 
        lcd.setCursor(0, 1);
        //lcd.print((CM=millis())/1000); 
        lcd.print("2 Lost Line    ");
      break;
      case 3: 
        Serial.println ("Waiting for Generator to power up");
        lcd.setCursor(0, 1);
        //lcd.print((CM=millis())/1000); 
        lcd.print("3 Gen Start    "); 
      break;
      case 4: 
        Serial.println ("Generator On"); 
                lcd.setCursor(0, 1);
        //lcd.print((CM=millis())/1000); 
        lcd.print("4 GEN PWR ON    "); 
      break;
      case 5: 
        Serial.println ("AC Restored; Cooldown cycle"); 
                        lcd.setCursor(0, 1);
        //lcd.print((CM=millis())/1000); 
        lcd.print("5 Cool Down    "); 
      break;
    }
      LastPowerState = PowerState;
}

} // loop
