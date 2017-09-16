// Simulate(Uno)
// Saved by Simulator for Arduino V0.97
// Saved by Simulator for Arduino V0.97
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93
// Saved by Simulator for Arduino V0.93

#define FanOnLed 1
byte RHavg[8] = {0,1,2,3,4,5,6,7};
string s = ",";
float temperatureF = 12.3;
float RH=34.5;
float RHaverage = 56.7;
float RHoldVaule = 67.8;

int OnThreshold = 200;
int LookBackCnt;


//CODE: SELECT ALL
int TempInput = 0;
int TempQAvg[] = {0,0,0,0};

void setup(){

	Serial.begin(9600);
   Serial.print(millis()/1000);   Serial.print(s);   
   Serial.print(temperatureF);      Serial.print(s);
   Serial.print(RH);            Serial.print(s);
   Serial.print(RHaverage);      Serial.print(s);
   Serial.print(RHoldVaule);      Serial.print(s);

LookBackCnt = abs((OnThreshold/100)-18);         // Fails
LookBackCnt = abs((OnThreshold / 100)-18);      // Fails
LookBackCnt = abs((OnThreshold/100 )-18);      // Fails   

LookBackCnt = abs((OnThreshold / 100) - 18);      // Passes
LookBackCnt = abs((OnThreshold/100) -18);      // Passes
LookBackCnt = abs((OnThreshold/100)- 18);      // Passes

if(FanOnLed==1){digitalWrite(13,LOW);} 

   TempQAvg[0] = 1;
   TempQAvg[1] = 2;
   TempQAvg[2] = 3;
   TempQAvg[3] = 4;
   
   TempInput =   (TempQAvg[0] + TempQAvg[1] + TempQAvg[2] + TempQAvg[3]) / 4;   // Fails
                
   TempInput =   TempQAvg[0];                  // Passes
   TempInput =   TempQAvg[1];                  // Passes
   TempInput =   TempQAvg[0] + TempQAvg[1];   // Fails
   TempInput =   TempQAvg[1] - TempQAvg[0];   // Fails
   TempInput =   TempQAvg[0] * TempQAvg[1];   // Fails
   TempInput =   TempQAvg[1] / TempQAvg[0];   // Fails
}

void loop() {
  // put your main code here, to run repeatedly:

    RHavg[4] = RHavg[3];
}
