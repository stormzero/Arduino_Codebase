/*--------- FC Custom House Alarm-----------------*/ 

#include <SoftwareSerial.h> // To drive the LCD
#include <EEPROM.h>         // To read & write to "permanent" storage 
 

//---------------------Parameters that can be set-------------------- 
const String         Version     = "V8.16";
const unsigned int   MessDelay   =  10000; //LCD display time (Max=65 535)
const unsigned long  AlarmTime   = 420000; //milli sec - Default Alarm2 time (Max=4 294 967 295)
const unsigned long  Trip1Length =   2000; //milli sec - Default Silent wait (set per case!)
const unsigned long  Trip2Length =  20000; //milli sec - Default Alarm1 wait (set per case!)
//-------------------------------------------------------------------
const byte   txLcdPin = 13; // From Pin 13 to LCD's Tx (Yellow)
const byte   rxLcdPin = 12; // From Pin 12 to LCD's RX (White)
                     
const byte NumSens = 10;
const byte RGate   = 2;
const byte MGate   = 3;
const byte Sen[]   = {RGate,MGate,4,5,6,7,17,16,15,14};  //Pin number eq Sen[0]=Pin 2
                                                         //Note: 17=A3; 16=A2; 15=A1; 14=A0
const String  AlarmType[] = {"PA",    
                             "RA",
                             "NR"};      //PA=Pre-Alarm; RA=Radio Alarm ; NR= Not Radio alarm;                                     

const String SenName[NumSens]  = {"Remote",    
                                  "Car-Gt",
                                  "House",
                                  "Spare",
                                  "Gate-E",
                                  "Atrium",
                                  "Carport",
                                  "CourtYd",
                                  "Stoep",
                                  "Wendy"};
                   
/*The Tripped array state each sensor behaviour when tripped:
   Tripped[0][0]=false :Sen[0] is not tripped (or true if tripped)
   Tripped[0][1]=true  :Sen[0] can be reset (or cannot be reset if tripped)
   Tripped[0][2]=true  :When Sen[0] is tripped, radio give response!         */
   
boolean Tripped[NumSens][3]    = {false,true,false,    
                                  false,true,true,     
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,false}; 
                                   
const byte    NMsgs = 5;           //Number of Trip history messages
byte          TripType;     //for each of NMsgs Trip history messages: The alarm type
byte          TripSen;      //for each of NMsgs Trip history messages: The sensor number
unsigned long TripTime;    //for each of NMsgs Trip history messages: The trip time ago

//Set the output pins
const byte    Radio       = 8;
const byte    Active      = 9;
const byte    Siren1      = 10;
const byte    Siren2      = 11;
const byte    butSB       = 19;    //=A5 analog: Button SetStatus: To set condition for LCD displaying
const byte    butSA       = 18;    //=A4 analog: Button SetArm   : To arm or disarm the alarm

byte          ni          = 200;   //Counter used to monitor display  
boolean       SB          =false;  //Used to monitor display status
boolean       CheckSB     =false;  //Used to monitor display status
boolean       SenTrip     =false;  //To monitor when sensor is tripped
boolean       WasTrip     =false;  //To monitor if a tripped happened
unsigned long SBPressTime = 0;     //To monitor time LCD is on since last button was pressed

byte SenNum;                       //The pin number that is tripped
byte  SenII;                       //The array number in the Sen[] array
byte     II;                       //Counter
byte      i;                       //Counter
int       j;                       //Counter

int Counter;                       //Counter
unsigned long Trip1Wait;           //Wait time for Trip1 (Silent)
unsigned long Trip2Wait;           //Wait time for Reset (Siren 1)
unsigned long Trip1Time;           //Time since a tripped sensor was detected for Phase 1 
unsigned long Trip2Time;           //Time since a tripped sensor was detected for Phase 2
unsigned long flickTime;           //Time when the Active LED was switch on or off
unsigned long WaitUntil;           //To wait until when a milli() was recorded
unsigned long AlarmSound;          //Time for sounding loud alarm (Alarm2)
boolean Tripped1 = false;          //Indicator that sensor was tripped (silent wait to start) 
boolean Tripped2 = false;          //Indicator that sensor was tripped (Siren 1 on)

boolean GateOpen = false;          //Indicator that gate was open by remote signal
boolean Armed    = true;           //Indicator that alarm is active and running
 
boolean T1       =false;           //Use to simplify complex booleans
boolean T2       =false;           //Use to simplify complex booleans
boolean T3       =false;
boolean T4       =false;
//Use to simplify complex booleans

unsigned long TheTime;             //The time lapse between now and when sensor was tripped
unsigned long DD;                  //The days factor in TheTime
unsigned long HH;                  //The hours factor in TheTime
unsigned long MM;                  //The minutes factor in TheTime
String Info;                       //TheTime in a string DDdHHhMMmSSs (and other)

SoftwareSerial myLcdSerial =  SoftwareSerial(rxLcdPin, txLcdPin);

// the setup routine runs once when you press reset:
void setup() {
  // Arduino's Tx as transmitter to LCD
  pinMode(txLcdPin, OUTPUT); 
  pinMode(rxLcdPin, INPUT);
  myLcdSerial.begin(9600);
  myLcdSerial.print("Begin LCD output");  //SIM
  
  Serial.begin(9600);                     //SIM
  Serial.println("Begin Serial output");  //SIM
  
  //Set Output & Input pins
  pinMode(Active, OUTPUT); 
  pinMode(Siren1, OUTPUT);
  pinMode(Siren2, OUTPUT);
  pinMode(Radio,  OUTPUT);
  pinMode(butSB,  INPUT);
  pinMode(butSA,  INPUT);
  
  //set the start conditions
  for (i=0; i<NumSens; i++) {
    pinMode(Sen[i], INPUT);
  }
  
  //To show alarm has started, flick Yellow LED (Active)
  for (i=0; i<6; i++) { 
    digitalWrite(Active, HIGH);
    delay(500);
    digitalWrite(Active, LOW);
    delay(500);
  }
      
  //Set the Trip history memory to 99=no message
  for (i=0; i<NMsgs; i++) {
    T1 = ReadTripLog(i);
    if (!T1) {
      //Set TripType & TripSen=99 (no trip)
      WriteTripLog(i,99,99,0);  
    }    
  }
// BreakPoin1t1(147)
  if (ReadTripLog(0)) {
    if (TripSen=!99) {
      WasTrip = true;
    }  
  }
  
  //Activate Active LED and note off time (+5000ms)
  digitalWrite(Active, HIGH);
  
  //Show Status of sensors
  byte Level;
  for (i=0; i<NumSens; i++) {
    Level = digitalRead(Sen[i]);
    Info = "Sen="+String(Sen[i]);
    Info = Info+"/"+"Level="+String(Level);
    PrintLCD(true,1,Info,1000,false);
    if (Level != 0) {
      Info = "Sen="+String(Sen[i]);
      Info = Info+" is open";
      while(1) {
        PrintLCD(true  ,1,Info,0,false);
        PrintLCD(false ,2,"Switch Off",1000,true);
        digitalWrite(Siren1,HIGH);
        delay(3);
        digitalWrite(Siren1,LOW);
        delay(1000);
      }  
    }
  }
  Info = "Started "+ Version; 
  PrintLCD(true ,1,Info,2000,true);
  flickTime = millis()+6000;
}

// the loop routine runs over and over again forever:
void loop() {
  if (digitalRead(butSA)==HIGH) {
    while(digitalRead(butSA)==HIGH) {
      delay(10);
    }
    ResetAlarm();
  }//(digitalRead(butSA)==HIGH)
    
  //Flick LED on and off to show armed
  if (Armed) {
//SIM    int flick = (unsigned long)((flickTime-millis()/1000 );
    int flick = RemTime(flickTime,millis() );
    if (flick<=0) {
      digitalWrite(Active, LOW);
      if (!WasTrip) { //No trips- single flick
        delay(400);
        digitalWrite(Active, HIGH);
      }
      else{  //Double flick
        delay(200);
        digitalWrite(Active, HIGH);
        delay(200);
        digitalWrite(Active, LOW);
        delay(200);
        digitalWrite(Active, HIGH);
      }
            
      flickTime = millis()+6000;
    } //if (flick<=0)
  }
  
  if (Armed) { 
    SenNum = 0;
    Tripped1 = false;
    
    //Check Remote on Gate
    if (!GateOpen) {
      if (digitalRead(RGate)==HIGH) {
        if (!GateOpen) { //Check for 250 times if gate is opened (max byte)
          i = 0; 
          while((!GateOpen) && (i<250) ) {
            if (digitalRead(MGate)==HIGH) {
              GateOpen = true;
              break;
            }  
            i++;
            delay(5);
          }
          //if Gate is Open by remote action, confirm or reset
          delay(1000);
          if (GateOpen) {
            if (digitalRead(MGate)==LOW) GateOpen = false;
          }  
        }//if !GateOpen
      }//if (digitalRead(RGate)==HIGH)
    }
    
    //Check the Gate Status
    if (!GateOpen) {
      if (digitalRead(MGate)==HIGH) {   
        if (!GateOpen) {  
          //Remote did not report GateOpen! Confirm gate open
          delay(1000);
          if (digitalRead(MGate)==HIGH) { 
            //Gate is found again open! Start alert action
            PrintLCD(false ,2,"Gate Forced!",1000,true);
            Tripped1 = true;
            SenII = 1;       //Gate pin is no 1 (2nd: 0,1) in Sen[] array
            SenNum = Sen[1]; //SenNum is now the value as defined in Sen[1] 
          } 
        }
      }
    }
    
    if (GateOpen) {
      if (digitalRead(MGate)==LOW) { //Reset GateOpen
        GateOpen      = false;
      }
    }  
    
    //if gate is OK (not Tripped), read rest of sensors but skip Sen[0]=Remote and Sen[1]=Gate
    if (!Tripped1) {    
      for (II=2; II<NumSens; II++) {
        //Call the Trip function 
        SenTrip = Trip(Sen[II]);
        delay(10);

        if (!SenTrip) {
          if (Tripped[II][0] && Tripped[II][1]) {
            Tripped[II][0] = false;  //reset old trip if OK
          }
        }
     
        if (SenTrip && !Tripped[II][0]) {
          SenII  = II;
          SenNum = Sen[II];
          Tripped[II][0] = true;  //set sensor as tripped
          Info = "Sen="+SenName[II];
          PrintLCD(true ,1,Info,2000,false);
          Tripped1 = true;
          digitalWrite(Active, LOW);
          break;
        }
        if (Tripped1) break;  //Skip the rest of sensors
      }//for (II=2; II<NumSens; II++)
    }//if (!Tripped1)  
  
    //First alarm is tripped! 
    if (Tripped1) {
      switch (SenNum) {
        //below noted cases are treated specially 
        case 3:  //Motorgate
          delay(2000);
          if (digitalRead(MGate)==HIGH) {
            Tripped2   = true;  //Motor gate forced! Set Tripped2 and
            Trip2Wait  = 0;     //do not wait normal wait period
            AlarmSound = AlarmTime;
            digitalWrite(Siren1, HIGH);
          }
        break;
        
        case 14:
          PrintLCD(true ,1,"Wendy trip",10,false);
          Trip2Wait = Trip2Length;
          Tripped2  = true; 
          AlarmSound = 10000; 
        break;
        
        case 15:
          PrintLCD(true ,1,"Stoep trip",10,false);
          Trip2Wait = Trip2Length;
          Tripped2  = true; 
          AlarmSound = AlarmTime; 
        break;
        
        case 16:  //Kitchen courtyard
          PrintLCD(true ,1,"Courtyard trip",10,false);
          Trip2Wait  = Trip2Length;
          Tripped2   = true; 
          AlarmSound = AlarmTime; 
        break;
        
        case 17:
          PrintLCD(true ,1,"Carport trip",10,false);
          Trip2Wait = Trip2Length;
          Tripped2  = true; 
         AlarmSound = AlarmTime; 
        break;
               
        //The default procedure for Tripped alarm
        //Wait a short while for informed person to go through sensor without tripping
        default:
          PrintLCD(true ,1,"Silent Trip!",0,false);
          Trip1Wait  = Trip1Length; //Default time
          AlarmSound = AlarmTime;
          WaitUntil  = millis()+Trip1Wait;
          T3 = true;
          while (T3) {
//SIM            int Val = (unsigned long)(WaitUntil-millis() )/1000;
            int Val = RemTime(WaitUntil,millis() );
            Info = String(Val)+"  ";
            PrintLCD(false ,2,Info,0,false);
            T1 = digitalRead(SenNum)==HIGH;
            T2 = (Val>0); 
            T3 = T1 && T2;
            delay(1000);       
          } 
          if (digitalRead(SenNum)==HIGH) {  //if still high, alert Siren1
            PrintLCD(true ,1,"Siren1 Active!",0,false);
            digitalWrite(Siren1, HIGH);
            Tripped2  = true;
            Trip2Wait = Trip2Length;
          }
          else {                           
            Tripped1 = false;  //else reset system
            Tripped2 = false;
            PrintLCD(true ,1,"Alarm Resetted",2000,true);
          } //default
      } //switch      
    }//if (Tripped1)
    
    //Alarm Phase 2: Sound small alarm to allow informed person to reset system!  
    if (Tripped2) {
      //Shift old down messages      
      for (j=NMsgs-2; j>-1; j--) {
        ReadTripLog(j);
        WriteTripLog(j+1,TripType,TripSen,TripTime);
      }
      //Note the trip data in log (Triptype=0)
      TripType = 0; 
      TripSen  = SenII;
      TripTime = millis()/1000;
      WriteTripLog(0,TripType,TripSen,TripTime);
      WasTrip = true;

      //Sound Alarm1 
      digitalWrite(Siren1, HIGH);
      
      WaitUntil = millis();
      WaitUntil = WaitUntil+Trip2Wait;
      if (Trip2Wait>0) {
        T1 = true;
        while (T1) {
//SIM          int Val = (unsigned long)(WaitUntil-millis() )/1000;
          int Val = RemTime(WaitUntil, millis() );  
          Info = String(Val)+"  ";
          PrintLCD(false ,2,Info,0,false);
          
          T1 = (Val>0);
          if (digitalRead(butSA)==HIGH) {
            ResetAlarm();
            T1 = false;
          }   
          delay(1000);
        }//while T1
      }//if (Trip2Wait>0)
    }//if (Tripped2)  
    
    if (Tripped2) {
      //Note trip message on LCD
      Info="Sen=";
      Info=Info+SenName[SenII];
      if (Tripped[SenII][2]) {     
        TripType = 1;
        Info = Info+":"+AlarmType[1];  //for Radio Alarm response
      }
      else {
        TripType = 2;
        Info = Info+":"+AlarmType[2];  //for No Radio Alarm response
      }
      PrintLCD(true,1,Info,10,false);

      //Radio response if Tripped[x][2]=True
      if (Tripped[SenII][2]) {      
        digitalWrite(Radio, HIGH);
        delay(2000);
        digitalWrite(Radio, LOW);
        delay(500); 
        PrintLCD(false,2,"Radio done!",2000,false);
      }
      
      //Update the trip data in log (Change TripType from PA to RA of NR)
      TripTime = millis()/1000;     //Time when Loud Alarm was sounded) 
      WriteTripLog(0,TripType,TripSen,TripTime);
      Tripped[SenII][0] = true;     //Note alarm was tripped for possible auto reset      
  
      //Switch on the loud alarm
      WaitUntil = millis();
      WaitUntil = WaitUntil + AlarmSound;
      digitalWrite(Siren2, HIGH);
      PrintLCD(true,1,"Siren2 Active!",0,false);
      T3 = true;
      T4 = true;
      while (T3) {
        //Toggle Siren1
        if (T4) {
          digitalWrite(Siren1, HIGH);
        }
        else {
          digitalWrite(Siren1, LOW);
        }
        T4 = !T4;
        //Check time to reset
//SIM        int Val = (unsigned long)(WaitUntil-millis() )/1000;
        int Val = RemTime(WaitUntil, millis() ); 
        Info = String(Val)+"     ";
        PrintLCD(false,2,Info,0,false);
        T3 = (Val>0);
        if (digitalRead(butSA)==HIGH) {
          ResetAlarm();
          T3 = false;
        }
        delay(1000);
      }   
      
      //Switch LCD off
      PrintLCD(true,1,"Alarm Off",2000,true);
      //Set LED's and Sirens to normal state
      digitalWrite(Active, HIGH);
      digitalWrite(Siren1, LOW);
      digitalWrite(Siren2, LOW);
      Tripped1 = false;
      Tripped2 = false;
      flickTime = millis()+6000;
    }//if (Tripped2) 
 
    Counter = 0;
    CheckSB = digitalRead(butSB);
    //Display button is pressed
    if (CheckSB) {
      //Check if button is hold down or not
      while ((digitalRead(butSB)!=LOW) && (Counter<205)) {      
        delay(10);
        ++Counter;
      }

      if (Counter>200) {
        //Button was hold down - delete history 
        DelMem();
        WasTrip = false;
        CheckSB = false; 
      }
    }
    
    //Button was not hold down - show history
    if (CheckSB) {
      SB = true;
      SBPressTime = millis();
      ni++;
      //if last message, start at 1 again 
      if (ni>NMsgs-1) {
        ni=0; 
      }
      
      ReadTripLog(ni);
      //SIM------------
      Info = "TripSen=";
      Info = Info+String(TripSen);
      PrintLCD(false,2,Info,1000,false);
      if (TripSen==99) {
        Info = "M";
        Info = Info+(ni+1);
        Info = Info+": None!";
        PrintLCD(true,1,Info,0,false);
        PrintLCD(false,2,"No Trip!   ",0,false);
      }
      else {
        Info = "M";
        Info = Info+(ni+1);
        Info = Info+"-";
        Info = Info+SenName[TripSen];
        Info = Info+":"+AlarmType[TripType];
        PrintLCD(true,1,Info,0,false);

        TheTime = (millis()/1000) - TripTime;      
        DD = TheTime / 86400;         //secs in a day
        TheTime = TheTime - DD*86400;  //remainder secs
        HH = TheTime / 3600;           //secs in hours
        TheTime = TheTime - HH*3600;   //remainder secs
        MM = TheTime / 60;             //secs in minute
        
        Info="AGO=";
        Info = Info+DD;
        Info = Info+"d";
        Info = Info+HH;
        Info = Info+"h";
        Info = Info+MM;
        Info = Info+"m";
        PrintLCD(false,2,Info,0,false);
      }
    }//if (CheckSB)
    
    if (SB) {
      //check time LCD is on and swith off when inactive
      if ((millis()-SBPressTime)>MessDelay) {
        PrintLCD(false,1,"Off",0,true);
        SB = false;
        ni =NMsgs;
      }
    }
  }//Armed
  if (!Armed) digitalWrite(Active, LOW);
}//loop


void ResetAlarm() {
  //Reset all parameters
  byte ns;
  byte A;
  boolean OK = true;
  Tripped1 = false;
  Tripped2 = false;
  GateOpen = false;
  for (i=0; i<NumSens; i++) {
    Tripped[i][0] = false;
  }
  Armed = !Armed;  //if armed set to disarm and vise versa

  if (Armed) {
    //Check that all sensors are closed
    for (ns=0; ns<NumSens; ns++) {
      T1 = Trip(Sen[ns]);
      OK = !T1;
      if(!OK) {
        A = 0; 
        OK = false;
        Info = SenName[ns];
        Info = Info+" Open!";
        while (!OK) {
          A++;
          PrintLCD(true,1,Info,1000,false);
          digitalWrite(Siren1,HIGH); 
          delay(300);
          digitalWrite(Siren1,LOW);
          T1 = Trip(Sen[ns]);
          if(!T1) OK = true;
          if(A>2) OK = true;
        }//while
        PrintLCD(false,1,Info,500,true);    
        T1 = Trip(Sen[ns]);
        OK = !T1;
        if (!OK) Armed = false;
      }//if
      if (!OK) break;
    }//for
  }//if 
  
  if (Armed) {  
    digitalWrite(Active, HIGH);
    //Give single beep 
    digitalWrite(Siren1, HIGH);
    delay(200);
    digitalWrite(Siren1, LOW);
    PrintLCD(true ,1,"Alarm Armed!",2000,true);
    flickTime = millis()+6000;
  }
    
  if (!Armed) {
    digitalWrite(Active, LOW);
    digitalWrite(Siren1, LOW);
    digitalWrite(Siren2, LOW);
    delay(500);
    //Give double beep 
    for (i=0; i<2; i++) {
      digitalWrite(Siren1, HIGH);
      delay(300);
      digitalWrite(Siren1, LOW);
      delay(300);
    } //for 
    PrintLCD(true ,1,"Alarm Disarmed!",2000,true);
  }
 PrintLCD(true ,1," ",0,true); 
}
  
boolean Trip(byte TheSen) {
  byte Trip1 = 0;
  delay(100);
  Trip1=digitalRead(TheSen);
  if (digitalRead(TheSen)==HIGH) {
    //confirm trip
    delay(1000);
    if (digitalRead(TheSen)==HIGH) {
      return true;
    }
    else { 
      return false;
    } 
  }
  else {
    return false;
  }
}

void DelMem()
{  
  PrintLCD(true ,1,"Release Button",10,false);
  PrintLCD(false,2,"to continue!" ,10,false);
  while (digitalRead(butSB)==HIGH) {
    delay(10);
  }
  PrintLCD(true ,1,"Press Button to",10,false);
  PrintLCD(false,2,"delete history" ,10,false);
  SB = false;
  WaitUntil = millis();
  WaitUntil = WaitUntil + 5000;
  T1 = true;
  while (T1) {  
//Sim    int Val = (unsigned long)(WaitUntil-millis() )/1000;
    int Val = RemTime(WaitUntil, millis() );
    if (digitalRead(butSB)==HIGH) {SB=true;}
    T1 = (!SB && (Val>0));
    delay(10); 
  }

  if (SB) {
    while (digitalRead(butSB)!=LOW) {
      delay(10);
    }
    for (byte i=0; i<NMsgs; i++) {
      WriteTripLog(i,99,99,0);
    }
    PrintLCD(true ,1,"Deleted!",2000,true);
  }
  else {
    PrintLCD(true ,1,"Not Deleted!",2000,true);
  }
}

void PrintLCD(boolean ClrScr1, byte Line, String S, int Delay, boolean ClrScr2) {
  String Message = S;
  if (Message.length()>16) Message = Message.substring(0,16);
  Message = "ss"+Message+";";
  if (ClrScr1) {myLcdSerial.print("sc;");    delay(10);}  //Screen clear 
  if (Line==1) {myLcdSerial.print("sd0,0;"); delay(10);}  //Line 0, Col 0
  if (Line==2) {myLcdSerial.print("sd1,0;"); delay(10);}  //Line 1, Col 0
  myLcdSerial.println(Message); delay(10);
  myLcdSerial.print("sb1;"); delay(10);    //Light on
  if (Delay>0) delay(Delay);
  if (ClrScr2) {myLcdSerial.print("sb0;");   delay(10);}  //Screen off
  if (ClrScr2) {myLcdSerial.print("sc;");    delay(10);}  //Screen clear

//  Serial.println(S);
//  if (ClrScr2) Serial.println("LCD Off");
}

void WriteTripLog(byte LNr, byte TType, byte TSen, unsigned long ValueIn)
{
  byte RNr;
  byte BT4, BT3, BT2, BT1;
  byte Address;
  
  Address = LNr*7;
  
  //Break TripTime into 4 bytes
  /*-----------------------EXPLANATION-------------------------
    Break ValueIn=200000 eq (32 bytes) into 4 values each 8 bytes:
    InValue = 00000000 00000011 00001101 01000000 (Dec=200000)
    BT4     = 00000000 (Dec=0)
    BT3     = 00000011 (Dec=3)
    BT2     = 00001101 (Dec=13)
    BT1     = 01000000 (Dec=64)
  ---------------------------------------------------------------*/
  BT1 = ValueIn;       
  BT2 = ValueIn >> 8;   
  BT3 = ValueIn >> 16; 
  BT4 = ValueIn >> 24;
  
  EEPROM.write(Address,LNr)    ;delay(4);
  EEPROM.write(Address+1,TType);delay(4);
  EEPROM.write(Address+2,TSen) ;delay(4);
  EEPROM.write(Address+3,BT1)  ;delay(4);
  EEPROM.write(Address+4,BT2)  ;delay(4);
  EEPROM.write(Address+5,BT3)  ;delay(4);
  EEPROM.write(Address+6,BT4)  ;delay(4);
  
  Serial.println("-----BEGIN WRITE-----");
  Serial.println("The data written are:");
  PrintDecBin("LNr="    ,LNr);
  PrintDecBin("TType="  ,TType);
  PrintDecBin("TSen="   ,TSen);
  PrintDecBin("ValueIn=",ValueIn);

  Serial.println("ValueIn (The four bytes written are:");
  PrintDecBin("BT1=",BT1);
  PrintDecBin("BT2=",BT2);
  PrintDecBin("BT3=",BT3);
  PrintDecBin("BT4=",BT4);
  Serial.println("-----END WRITE-------");
}//WriteTripLog

boolean ReadTripLog(byte LNr) 
{
  byte BT1, BT2, BT3, BT4, Nr;
  unsigned long TOut;
  int Address;
  
  Address = LNr*7;
  Nr       = EEPROM.read(Address);
  TripType = EEPROM.read(Address+1);
  TripSen  = EEPROM.read(Address+2);
  BT1      = EEPROM.read(Address+3);
  BT2      = EEPROM.read(Address+4);
  BT3      = EEPROM.read(Address+5);
  BT4      = EEPROM.read(Address+6);
  //Put for byte together for long
  TOut = 0; 
  for (byte k=0; k<8; k++) bitWrite(TOut,k,   bitRead(BT1,k));
  for (byte k=0; k<8; k++) bitWrite(TOut,k+8, bitRead(BT2,k)); 
  for (byte k=0; k<8; k++) bitWrite(TOut,k+16,bitRead(BT3,k)); 
  for (byte k=0; k<7; k++) bitWrite(TOut,k+24,bitRead(BT4,k)); // Sim
  TripTime = TOut;
  
  Serial.println("----BEGIN READ-------"); 
  Serial.println("The data read are:");
  PrintDecBin("Nr=",Nr);
  PrintDecBin("TripType=",TripType);
  PrintDecBin("TripSen=",TripSen);
  PrintDecBin("TripTime=",TripTime);
  Serial.println("ValueIn (The four bytes read are:");
  PrintDecBin("BT1=",BT1);
  PrintDecBin("BT2=",BT2);
  PrintDecBin("BT3=",BT3);
  PrintDecBin("BT4=",BT4);
  Serial.println("-----END READ--------");
  if (Nr==LNr) {
    return true;
  }
  else {
   return false;
  }   
}//ReadTripLog

int RemTime(unsigned long Time1, unsigned long Time2) {
  int RT;
  RT = (Time1-Time2)/1000; 
  return RT;
}

void PrintDecBin(String SValue, unsigned long AValue) {
 String VarName = SValue; 
 Serial.println(VarName+String(AValue,DEC)+"/Bin="+String(AValue,BIN)); 
}

