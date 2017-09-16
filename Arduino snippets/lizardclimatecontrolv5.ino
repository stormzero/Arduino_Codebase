
// Saved by Simulator for Arduino V0.97B
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.96.A.3

/*

Software coding started on 3/5/2012
Revision 1 - initial
Revision 2 - adds Minute on time specification, simplified rule definitions
Revision 3 - adds Weekend On Time Delay, changes day/night rule handling


This is the software for controlling a simple time and temp constrained environment for our bearded dragon.
Temps are checked constantly and compared to a high and low temp.
Light use is defined by a On and Off schedule.
Items are on/off based on the hour and minute from the RTC.
5/21/2012 Added ShiftBright v2 for visual status of system.

Rule Definitions:
DAY
1 Day if temp is ok turn all on
2 Day if temp is too high 
  Condition 1 rock off/light on condition existed for < overTempFirstAction
  Condition 2 rock off/light on condition existed for > overTempFirstAction && < overTempSecondAction
  Condition 3 delay turning all on until temp has dropped to 5 below high temp threshold
NIGHT
1 Night if temp is ok turn all off
2 Night if temp is too low
  Condition 1 rock on/light off condition existed for < underTempFirstAction
  Condition 2 rock on/light off condition existed for > underTempFirstAction && < underTempSecondAction
  Condition 3 rock on/light on condition existed for > underTempSecondAction
  Condition 4 rock on/light on condition existed for > underTempSecondAction + 5 Min Sound Alarm


*/

#include <Wire.h>
#if (0)
#include "PCD8544.h"
#include <DHT.h>
//#include "Tone.h"
#include "Time.h"
#include "DS1307RTC.h"
#endif

//pins for the temp sensors
#define DHTPIN1 8
#define DHTPIN2 9

//type of temp sensors
#define DHTTYPE DHT22

//the AC switch digital pins
#define SW1 10 //light
#define SW2 11 //heat lamp

//setup for the ShiftBright LED status
//int datapin  = 12; // DI
//Int latchpin = 13; // LI
//int enablepin = 1; // EI
//int clockpin = 2; // CI
//unsigned long SB_CommandPacket;
//int SB_CommandMode;
//int SB_BlueCommand;
//int SB_RedCommand;
//int SB_GreenCommand;

//set the HOUR and MINUTES (24 HR Format) for lights on/off
#define LightsOnHr 5
#define LightsOnMin 45
#define LightsOffHr 20
#define LightsOffMin 5
#define WeekendDelay 2
int isDay = 0; //global variable to indicate day/night period

//set the high and low temp thresholds in F
#define HighTempF 108
#define LowTempF 75

//setup time stamps for condition changes
static unsigned long overTempFirstAction = 600000; //10 minutes
static unsigned long overTempSecondAction = 1200000; //20 minutes
unsigned long overTempStart;
unsigned long overTempDuration;
static unsigned long underTempFirstAction = 600000; //10 minutes
static unsigned long underTempSecondAction = 1200000; //20 minutes
unsigned long underTempStart;
unsigned long underTempDuration;
String stringDateTime;  //used to print the date/time properly
int inByte = 0;         // incoming serial byte
int DEBUG = 1;
//int DEBUGsim = 0;
#define aref_voltage 5.0

//setup the two temp/humid probes as objects
//DHT dht1(DHTPIN1, DHTTYPE);
//DHT dht2(DHTPIN2, DHTTYPE);

//config the lcd
//static PCD8544 lcd = PCD8544(7, 6, 5, 4, 3);
LiquidCrystal lcd(7, 6, 5, 4, 3);



void setup() { 
   Serial.begin(57600);
   Serial.println("Lizard Climate Control Starting Up...");
  
 
  //setup the lcd
  Serial.println("Setting up the Nokia LCD...");
  lcd.init();
  lcd.setContrast(21);
  lcd.clear();

  Wire.begin();
  Serial.println("Trying to get date from RTC...");
  setSyncProvider(RTC.get);   // the function to get the time from the RTC


  //turn off the AC devices while we set things up
  Serial.println("Turning off all AC devices as we get started...");
  pinMode(SW1, OUTPUT);
  pinMode(SW2, OUTPUT);
  digitalWrite(SW1, LOW);
  digitalWrite(SW2, LOW);

  
}


void loop() {
  if (DEBUG == 1) {Serial.println("Determining Day");}
  determineIsDay();
  if (DEBUG == 1) {Serial.println("Processing Schedule");}
  processSchedule();
  // Read the temperature (in celsius)...
  float temperatureC1 = dht1.readTemperature();
  float temperatureF1 = (temperatureC1 * 9.0 / 5.0) + 32.0;
  float humid1 = dht1.readHumidity();
  float temperatureC2 = dht2.readTemperature();
  float temperatureF2 = (temperatureC2 * 9.0 / 5.0) + 32.0;  
  float humid2 = dht2.readHumidity();

//output basics to the lcd screen 
  lcd.clear();
  lcd.setCursor(0, 0);
  
  printDateTimeNoYear(); //get properly formatted date/time into a printable string
  lcd.print(stringDateTime);
  if (DEBUG == 1) {Serial.println(stringDateTime);}
  lcd.setCursor(0, 8);
  lcd.print("Right:");
  lcd.println(temperatureF1, 2);
  if (DEBUG == 1) {Serial.print("Right: "); Serial.println(temperatureF1, 2);}
  lcd.setCursor(0, 16);
  lcd.print("Humid:");
  lcd.print(humid1, 2);
  lcd.println("%");
  if (DEBUG == 1) {Serial.print("Humid: "); Serial.print(humid1, 2); Serial.println("%");}  
  lcd.setCursor(0, 24);
  lcd.print("Left :");
  lcd.println(temperatureF2, 2);
  if (DEBUG == 1) {Serial.print("Left: "); Serial.println(temperatureF2, 2);}    
  lcd.setCursor(0, 32);
  lcd.print("Humid:");
  lcd.print(humid2, 2);
  lcd.println("%");
  if (DEBUG == 1) {Serial.print("Humid: "); Serial.print(humid2, 2); Serial.println("%");}    
  lcd.setCursor(0,40);
  lcd.print("SW1:");
  lcd.print(digitalRead(SW1));
  lcd.print(" SW2:");
  lcd.print(digitalRead(SW2));
  lcd.display();
  if (DEBUG == 1) {Serial.print("SW1: "); Serial.println(digitalRead(SW1));}
  if (DEBUG == 1) {Serial.print("SW2: "); Serial.println(digitalRead(SW2));}  
}


void processSchedule(){
  //turn the lights on/off based on the time schedule and temperature

  if (DEBUG == 1) {Serial.println("Running processSchedule function...");}
 
  // Read the temperature (in celsius) and convert to F...
  //if (DEBUG) {Serial.println("Getting Temp from dht1...");}
  float temperatureC1 = dht1.readTemperature();
  float temperatureF1 = (temperatureC1 * 9.0 / 5.0) + 32.0;  
  //if (DEBUG) {Serial.println(temperatureF1,2);}
//print this only if debugging has been called
  if (DEBUG == 1) {
    Serial.print("Process Run @ ");
    printDateTime(); //get properly formatted date/time into a printable string
    Serial.println();
  }
  
//**********day time rules**********
//SW1 UV light
//SW2 heat lamp

  
  if (isDay == 1){
    if (DEBUG == 1) {Serial.println("--DAY--");}
 
    if (temperatureF1 < HighTempF && overTempStart == 0) 
 {
       if (DEBUG == 1) {Serial.println("RULE 1 TRUE--NORMAL TEMP");}
       digitalWrite(SW1, HIGH); //uv on
       digitalWrite(SW2, HIGH); //heat lamp on
       //SB_SendGreen();    
 }     //END DAY RULE 1

    //if temp is too high and it's daytime  
    if (temperatureF1 > HighTempF + 1)
    { 
      if (DEBUG == 1) {Serial.println("RULE 2 TRUE--OVER TEMP");}
      
      //if overtempstart time is zero, set it to the current millis count, otherwise get the difference between now and when it was set
      if (overTempStart == 0) {overTempStart = millis();} else {overTempDuration = millis() - overTempStart;}
      
      //SB_SendYellow(); //set master indicator to yellow to indicate a temp issue.
      
      digitalWrite(SW2, LOW); //TURN OFF HEAT LAMP 
      
      if (DEBUG == 1) {Serial.println("--CONDITION 1 TRUE--OVER TEMP FOR "); Serial.print(overTempDuration,DEC); Serial.print(" ms");}
  
      //if the condition has existed for more than overTempFirstAction (HEAT LAMP OFF)
      // and less than overTempSecondAction keep lamp off 
      if (overTempDuration > overTempFirstAction && overTempDuration < overTempSecondAction) {digitalWrite(SW2, LOW); }//SB_SendYellow();} 
      if (DEBUG == 1) {Serial.print("--CONDITION 2 TRUE--OVER TEMP EFFECTIVE FOR OVER: "); Serial.print(overTempDuration,DEC); Serial.print(" ms");}
  
      //if the condition has existed for more than overTempSecondAction keep lamp off
      if (overTempDuration > overTempSecondAction) {digitalWrite(SW2, LOW);}// SB_SendRed();}
        if (DEBUG == 1) {Serial.println("--CONDITION 3 TRUE--OVER TEMP EFFECTIVE FOR OVER: "); Serial.print(overTempDuration,DEC); Serial.print(" ms");}
           
      if (temperatureF1 < HighTempF - 5) {overTempStart = 0; overTempDuration = 0; } else
      {
        //temp still too high, wait a while until it drops to 5 below HighTempF
        if (DEBUG == 1) {Serial.println("--WAITING FOR TEMP TO DROP 5 DEGREES BELOW HIGHTEMP THRESHOLD--CONDITION EXSTED FOR: "); Serial.println(overTempDuration,DEC); Serial.print(" ms");}
      }
    
    } else {overTempStart = 0; overTempDuration = 0;}

} //end of isDay group


//*********night time rules*********
//SW1 UV light
//SW2 heat lamp
  if (isDay == 0) {
  if (DEBUG == 1) {Serial.println("--NIGHT--");}
  //if temp is ok and it's outside LightsOn time keep it all off
  if (temperatureF1 >= LowTempF ) {
    if (DEBUG == 1) {Serial.println("RULE 1 TRUE--");}
    digitalWrite(SW1, LOW); 
    digitalWrite(SW2, LOW);
    //SB_SendGreen(); 
    }

//if temp is too low turn on the UV LAMP

  if (temperatureF1 < LowTempF - 1) {
    if (DEBUG == 1) {Serial.println("RULE 2 TRUE--UNDER TEMP");}
 
    //if underTempStart is zero set it otherwise get the difference between now and when it was set
    if (underTempStart == 0) {underTempStart = millis();} else {underTempDuration = millis() - underTempStart;}
    
    //SB_SendYellow(); //set master indicator to yellow to indicate a temp issue.
      
    digitalWrite(SW2, HIGH); //TURN ON HEAT LAMP 
    
    //if the condition has existed for less than underTempFirstAction keep lamp on
    if (underTempDuration <= underTempFirstAction) {digitalWrite(SW2, HIGH);} 
    if (DEBUG == 1) {Serial.println("--CONDITION 1 TRUE--UNDER TEMP FOR: "); Serial.print(underTempDuration,DEC); Serial.print(" ms");}

    //if the condition has existed for more than underTempFirstAction
    // and less than underTempSecondAction turn on lamp
    if (underTempDuration > underTempFirstAction && underTempDuration < underTempSecondAction) {digitalWrite(SW2, HIGH);}  
    if (DEBUG == 1) {Serial.println("--CONDITION 2 TRUE--UNDER TEMP FOR: "); Serial.print(underTempDuration,DEC); Serial.print(" ms");}

    //if the condition has existed for more than underTempSecondAction turn on lamp
    if (underTempDuration > underTempSecondAction) {digitalWrite(SW2, HIGH);}// SB_SendRed();}
      if (DEBUG == 1) {Serial.println("--CONDITION 3 TRUE--UNDER TEMP FOR: "); Serial.print(underTempDuration,DEC); Serial.print(" ms");}
    
    if (temperatureF1 > LowTempF + 5) {underTempStart = 0; underTempDuration = 0; } else
      {
        //temp still too high, wait a while until it drops to 5 below HighTempF
        if (DEBUG == 1) {Serial.println("--WAITING FOR TEMP TO RISE 5 DEGREES ABOVE LOWTEMP THRESHOLD--CONDITION EXSTED FOR: "); Serial.println(underTempDuration,DEC); Serial.print(" ms");}
      }
    
    }
  
  } else {underTempStart = 0; underTempDuration = 0;}   
  
  if (DEBUG == 1) {Serial.print("isDay=");}
  if (DEBUG == 1) {Serial.println(isDay);}
  if (DEBUG == 1) {Serial.println("*");}
  
}

void determineIsDay(){ //all the rules to decide if it's day or night according to the on/off times
//weekday()  1 = sunday 7 = saturday
 time_t t = now();

 if (hour(t) >= LightsOnHr && hour(t) < LightsOffHr && weekday(t) != 1 && weekday(t) != 7){
  if (hour(t) == LightsOnHr && minute(t) < LightsOnMin){isDay = 0;} //0 = night
  if (hour(t) == LightsOnHr && minute(t) >= LightsOnMin){isDay = 1;} //1 = day  
  if (hour(t) > LightsOnHr){isDay = 1;} //1 = day 
                //if (DEBUG) {Serial.println("isDay Rule 1 Used");} 
 }
 
 if ((hour(t) >= LightsOffHr) || (hour(t) < LightsOnHr)){
  if (hour(t) == LightsOffHr && minute(t) < LightsOffMin){isDay = 1;} //1 = day
  if (hour(t) == LightsOffHr && minute(t) >= LightsOffMin){isDay = 0;} //0 = night  
  if (hour(t) >= LightsOffHr || hour(t) < LightsOnHr){isDay = 0;} //0 = night
                //if (DEBUG) {Serial.println("isDay Rule 2 Used");}   
 }

 if ((hour(t) >= LightsOnHr + WeekendDelay && hour(t) < LightsOffHr) && (weekday(t) == 1 || weekday(t) == 7)){
  if (hour(t) == LightsOnHr + WeekendDelay  && minute(t) < LightsOnMin){isDay = 0;} //0 = night
  if (hour(t) == LightsOnHr + WeekendDelay && minute(t) >= LightsOnMin){isDay = 1;} //1 = day  
  if (hour(t) > LightsOnHr + WeekendDelay){isDay = 1;} //1 = day  
                //if (DEBUG) {Serial.println("isDay Rule 3 Used");} 
 }
 
 if ((hour(t) >= LightsOffHr || hour(t) < LightsOnHr + WeekendDelay) && (weekday(t) == 1 || weekday(t) == 7)){
  if (hour(t) == LightsOffHr && minute(t) < LightsOffMin){isDay = 1;} //1 = day
  if (hour(t) == LightsOffHr && minute(t) >= LightsOffMin){isDay = 0;} //0 = night  
  if (hour(t) >= LightsOffHr || hour(t) < LightsOnHr + WeekendDelay){isDay = 0;} //0 = night  
                //if (DEBUG) {Serial.println("isDay Rule 4 Used");} 
 }
}

void soundALARM() {
//SB_SendRed();


}


void serialEvent() { 
//serial output for Processing to use in updating a web page
// if we get a valid byte, read analog ins:
// get incoming byte:
  inByte = Serial.read();
  if (inByte != NULL) {
    switch (inByte){
      case 82: case 114: //"R or r" as ASCII DEC Byte Value
        outputDebugData();
        break;
        
      case 68: case 100://"D or d" as ASCII DEC Byte Value
        DEBUG = 1;
        outputDebugData();  
        processSchedule();  
        DEBUG = 0; 
        break;
      
      case 84: case 116: //"T or t" as ASCII DEC Byte Value
        printDateTime();
        Serial.println(stringDateTime);      
        break;
      
      default:
        break;                
    }
 }
 
}

void printDateTime(){
//print date/time with leading zeros    
    String dataOutput = "";
    if (month() < 10) {dataOutput += "0"; dataOutput += month(), DEC;} else {dataOutput += month(), DEC;}
    dataOutput += '/';
    if (day() < 10) {dataOutput += "0"; dataOutput += day(), DEC;} else {dataOutput += day(), DEC;}
    dataOutput += '/';
    dataOutput += year(), DEC;
    dataOutput += " ";
    if (hour() < 10) {dataOutput += "0"; dataOutput += hour(), DEC;} else {dataOutput += hour(), DEC;}
    dataOutput += ':';
    if (minute() < 10) {dataOutput += "0"; dataOutput += minute(), DEC;} else {dataOutput += minute(), DEC;}
    dataOutput += ':';
    if (second() < 10) {dataOutput += "0"; dataOutput += second(), DEC;} else {dataOutput += second(), DEC;}
    //Serial.println(dataOutput);
    stringDateTime = dataOutput;
}

void outputDebugData(){
    // Read the temperature (in celsius)...
    float temperatureC1 = dht1.readTemperature();
    float temperatureF1 = (temperatureC1 * 9.0 / 5.0) + 32.0;
    float humid1 = dht1.readHumidity();
    float temperatureC2 = dht2.readTemperature();
    float temperatureF2 = (temperatureC2 * 9.0 / 5.0) + 32.0;  
    float humid2 = dht2.readHumidity();
  
    printDateTime(); //get properly formatted date/time into a printable string
    Serial.print(stringDateTime);
    Serial.println();
    Serial.print("Right:");
    Serial.println(temperatureF1, 2);
    Serial.print("Humid:");
    Serial.println(humid1, 2);
    Serial.print("Left:");
    Serial.println(temperatureF2, 2);
    Serial.print("Humid:");
    Serial.println(humid2, 2);
    Serial.print("Switch 1:");
    Serial.println(digitalRead(SW1));
    Serial.print("Switch 2:");
    Serial.println(digitalRead(SW2));
    Serial.println("*");
}

void printDateTimeNoYear(){
//print date/time with leading zeros    
    String dataOutput = "";
    if (month() < 10) {dataOutput += "0"; dataOutput += month(), DEC;} else {dataOutput += month(), DEC;}
    dataOutput += '/';
    if (day() < 10) {dataOutput += "0"; dataOutput += day(), DEC;} else {dataOutput += day(), DEC;}
    //dataOutput += '/';
    //dataOutput += year(), DEC;
    dataOutput += " ";
    if (hour() < 10) {dataOutput += "0"; dataOutput += hour(), DEC;} else {dataOutput += hour(), DEC;}
    dataOutput += ':';
    if (minute() < 10) {dataOutput += "0"; dataOutput += minute(), DEC;} else {dataOutput += minute(), DEC;}
    dataOutput += ':';
    if (second() < 10) {dataOutput += "0"; dataOutput += second(), DEC;} else {dataOutput += second(), DEC;}
    //Serial.println(dataOutput);
    stringDateTime = dataOutput;
}









