// Saved by Simulator for Arduino V0.98B
const int lowestPin = 3;
const int highestPin = 6;
const int ledPin =  9;      // the number of the LED pin
boolean lightState = false;
boolean lightSet = false;
boolean tast_Merker=false;
boolean dim=false;
long sensorValue = analogRead(A1);
int i;
int casevar;
int ledState = LOW;
const int led1 = 3;      // red         
const int led2 = 5;      // green
const int led3 = 6;      // yellow
int led1_level = 20;
int led2_level = 20;
int led3_level = 20;
boolean led1_dir = LOW;
boolean led2_dir = LOW;
boolean led3_dir = LOW;
int tast_anz = 0;
unsigned long currentMillis;
long previousMillis = 0;
long previousbutton = 0;       
long interval = 20000;           // interval time to hold the push-button (milliseconds)
long timebutton = 600;  // interval time between the switches (milliseconds)
 
void setup() {
  // 5 Volt on bridge 2x 6k resistor
  digitalWrite(ledPin, HIGH);
  // set pins 3 through 6 as outputs:
  for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++ ) {
    pinMode(thisPin, OUTPUT);
  }
  Serial.begin(115200);
  lightState = LOW;
}
void loop() {
  unsigned long currentMillis = millis();
  for (int i=0; i < 4; i++){
    sensorValue = sensorValue + analogRead(A1);
  }
  sensorValue = sensorValue/20;
  // Taster gedrueckt und erster Durchlauf
  if(sensorValue < 127 && tast_Merker == 0)
  {
    previousMillis = currentMillis;  //Zeit ruecksetzen
    tast_Merker=1;    //Merker setzen
    tast_anz=tast_anz++;   //Anzahl erhoehen
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);
  }
  if(currentMillis - previousMillis < interval && sensorValue > 127 && tast_anz == 1)
  {
    casevar=2;     //EIN bzw. AUS schalten
  }
  if(currentMillis - previousMillis > interval && tast_anz == 1 && sensorValue < 127)
  {
    casevar=3;     //Dimmen runter und wieder rauf
    dim=HIGH;
  }
  switch(casevar){
  case 1:
    if(currentMillis - previousMillis > interval && sensorValue > 127)
    {
    previousMillis = currentMillis;  //Zeit ruecksetzen
    }
    casevar=0;
    break;
  case 2: //EIN/AUS
    casevar=1;
    tast_anz=0;
    tast_Merker=0;
    dim=LOW;   
    lightState = !lightState;
    if(lightState == true)
    {
      for(int L1=1;L1 < led1_level; L1++)
      {
        analogWrite(led1,L1);
        analogWrite(led2,L1);
        analogWrite(led1,L1);
        delay(40);        
      }
      analogWrite(led1,led1_level);
      analogWrite(led2,led2_level);
      analogWrite(led1,led3_level);
      digitalWrite(13,lightState);
    }     
    else
    {
      for(int L1=led1_level;L1 > 0; L1--)
      {
        analogWrite(led1,L1);
        analogWrite(led2,L1);
        analogWrite(led1,L1);
        delay(40);
      }    
      delay(10);           
      analogWrite(led1,0);
      analogWrite(led2,0);
      analogWrite(led1,0);
      // neu lightState = LOW;
      digitalWrite(13,lightState);
    }   
    break;
  case 3: //DIMMEN
    if(sensorValue > 127)
    {
      //casevar=0;
      digitalWrite(13,lightState);
    }
    break;
  default:
    break;       
  }
}
 