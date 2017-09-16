// Assigning the Pins for Inputs.
// Input pins
const int DoorClose= 2;    
const int InsideChamber =  3;  
const int Spare_1_In = 5;  
const int Spare_2_In = 6;  
const int Spare_3_In = 7;

// Output pins
const int VacuumPump = 8;
const int InsideChamberSol = 9;
const int OutsideChamberSol = 10;
const int HeatElement = 11;
const int RedLED = 12;
const int GreenLED = 13;
//const int Spare_1_Out = 12;
//const int Spare_2_Out = 13;

//Analog inputs
int VacuumPot = A0;
int SealingPot = A1;


// setup const times for Vacuum and sealing

// setup variable to use in programs
long VacuumRawTime = 0;
long VacuuumSetTime = 0;
long SealingRawTime = 0;
long SealingSetTime = 0;
long seqnr = 0;
boolean door_bit = 0;
boolean door_ant = 0;
boolean door_act = 0;



//Setup for vacuum and sealing times.

// Pin assignments as in or outputs



void setup() 
{
  
    // initialize the LED pin as an inputs:
    pinMode(DoorClose, INPUT); 
    pinMode(InsideChamber, INPUT);
    pinMode(Spare_1_In, INPUT);
    pinMode(Spare_2_In, INPUT);
    pinMode(Spare_3_In, INPUT); 
        
    // initialize the pushbutton pin as an outputs:
    pinMode(VacuumPump, OUTPUT);   
    pinMode(InsideChamberSol, OUTPUT);
    pinMode(OutsideChamberSol, OUTPUT);
    pinMode(HeatElement, OUTPUT);
    pinMode(RedLED, OUTPUT);
    pinMode(GreenLED, OUTPUT);
    //pinMode(Spare_1_Out, OUTPUT); 
    //pinMode(Spare_2_Out,OUTPUT);
    
    // initialize the serial print output
    Serial.begin(9600);
      
}

void loop()
{ 
  
  VacuumRawTime = analogRead(VacuumPot);
  VacuuumSetTime = VacuumRawTime * 10;  
  SealingRawTime = analogRead(SealingPot);
  SealingSetTime = SealingRawTime * 10;
  
  // Create loop Rising edge of Door Switch
      door_ant=door_act;
      door_act=digitalRead(DoorClose);
      door_bit=door_act &&! door_ant;  
      
        
    
  Serial.println(seqnr);
  
      if (digitalRead(DoorClose) == HIGH) 
      {      
          
            
          seqnr = 1; // Start the sequence if the door is closed
          
                  switch (seqnr)
                  {
                  case 1: //Close the Solenoid for inside or outside chamber
                        ChamberControlOn();                        
                        Serial.println(seqnr);
                   break;    
                   
                  case 2: // Start the vacuum cycle
                       VacuumCycle(VacuuumSetTime);
                       Serial.println(seqnr);
                  break;
                  
                  case 3: //Start Sealing                            
                       SealingCycle(SealingSetTime);
                       Serial.println(seqnr);
                  break;    
                  
                  case 4:
                        ChamberControlOff();
                  
                  default:
                  Serial.print("Fine");  
                  
                  }
      }
  
  }  
 
 void ChamberSol()
{
  
}


  void ChamberControlOn()
  {
    if (digitalRead(InsideChamber) == HIGH) // Check if inside or outside control has been selected
    {
      digitalWrite(InsideChamberSol,HIGH);
      digitalWrite(OutsideChamberSol,LOW);
      delay(200);
      seqnr = 2;
    }
    else
    {
      digitalWrite(OutsideChamberSol,HIGH);
      digitalWrite(InsideChamberSol,LOW);
      delay(200);
      seqnr = 2;
    }
    //return;
  }  
  
  void VacuumCycle(long Vacuumtime)
  {  
      
      digitalWrite(VacuumPump, HIGH);
      delay(Vacuumtime);
      digitalWrite(VacuumPump,LOW);  
      seqnr = 3; 
      //return;
  }
  
  void SealingCycle(long Sealingtime)
  {
      digitalWrite(HeatElement, HIGH);
      delay(Sealingtime);
      digitalWrite(HeatElement,LOW);  
      delay(200);
      seqnr = 4; 
     // return;
  }
  
  void ChamberControlOff()
  {
      digitalWrite(InsideChamberSol,LOW);
      digitalWrite(OutsideChamberSol,LOW);
      delay(200);
      seqnr = 0;
    //  return;
  }
  
 



