int key_s6 = 2;
const int ledPin = 13;
const int E1 = 5;
const int M1 = 4;
const int E2 = 6;
const int M2 = 7;
const int Bsense = 11; //8,9,10,11
const int Lsense = 10;
const int Rsense = 8;
const int Csense = 9;



// Setup

void setup() 
{
  Serial.begin(19200);
  
  //Pins
      // OUTPUT
      pinMode(M1, OUTPUT);
      pinMode(E1, OUTPUT);
      pinMode(M2, OUTPUT);
      pinMode(E2, OUTPUT);
      pinMode(ledPin, OUTPUT);
 
      // INPUT
      pinMode(Bsense, INPUT);
      pinMode(Lsense, INPUT);
      pinMode(Rsense, INPUT);
      pinMode(Csense, INPUT);
      pinMode(key_s6, INPUT);
      
   digitalWrite(M1, LOW);
   digitalWrite(E1, LOW);
   digitalWrite(M2, LOW);
   digitalWrite(E2, LOW);
}

//Commands

  //Stop
  void stop(void)
  {
    digitalWrite(E1,LOW);
    digitalWrite(E2,LOW);
  }

  //Advance
  void advance(char a, char b)
  {
    analogWrite(E1,a);
    digitalWrite(M1,LOW);
    analogWrite(E2,b);
    digitalWrite(M2,LOW);
  }

  //Turn Right
  void turn_R(char a, char b)
  {
    analogWrite(E1,a);
    digitalWrite(M1,HIGH);
    analogWrite(E2,b);
    digitalWrite(M2,LOW);
  }

  //Turn Left
  void turn_L(char a, char b)
  {
    analogWrite(E1,a);
    digitalWrite(M1,LOW);
    analogWrite(E2,b);
    digitalWrite(M2,HIGH);
  }

  //Back
  void back_off(char a, char b)
  {
    analogWrite(E1,a);
    digitalWrite(M1,HIGH);
    analogWrite(E2,b);
    digitalWrite(M2,HIGH);
  }
   
//Sensors
int BsenseValue,RsenseValue,LsenseValue,CsenseValue;

  //Sensor Allocation
  
    void readSensors() 
   {
    BsenseValue=digitalRead(Bsense);
    RsenseValue=digitalRead(Rsense);
    LsenseValue=digitalRead(Lsense);
    CsenseValue=digitalRead(Csense);
   }
  
  //Sensor Test
     
     void printDebug()
     {
       Serial.println("Bsense");
       Serial.println(BsenseValue);
       Serial.println("Rsense");
       Serial.println(RsenseValue);
       Serial.println("Lsense");
       Serial.println(LsenseValue);
       Serial.println("Csense");
       Serial.println(CsenseValue);
       delay(100);
     }
     
     //Motor Speed
    char l=255,r=255;

void program()
{
  if (BsenseValue == 0 && RsenseValue == 0 && CsenseValue == 0 && LsenseValue == 0)      // all false
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 0 && RsenseValue == 0 && CsenseValue == 1 && LsenseValue == 0)    //true: c
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 1 && RsenseValue == 0 && CsenseValue == 1 && LsenseValue == 0)    //true: c, b
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 1 && RsenseValue == 0 && CsenseValue == 0 && LsenseValue == 0)    //true: b
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 0 && RsenseValue == 1 && CsenseValue == 1 && LsenseValue == 1)    //true: r,c,l
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 1 && RsenseValue == 1 && CsenseValue == 1 && LsenseValue == 1)    //all true
  {
    advance(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 0 && RsenseValue == 1 && CsenseValue == 1 && LsenseValue == 0)    //true: c,r
  {
    turn_R(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 0 && RsenseValue == 0 && CsenseValue == 1 && LsenseValue == 1)    //true: c,l
  {
    turn_L(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 1 && RsenseValue == 1 && CsenseValue == 1 && LsenseValue == 0)    //true: b,c,r
  {
    turn_R(l,r);
    delay(10);
  }
  
  else if (BsenseValue == 1 && RsenseValue == 0 && CsenseValue == 1 && LsenseValue == 1)    //true: b,c,l
  {
    turn_L(l,r);
    delay(10);
  }
  else if (BsenseValue == 0 && RsenseValue == 0 && CsenseValue == 0 && LsenseValue == 1)    //true: l
  {
    turn_L(l,0);
    delay(10);
  }
  else if (BsenseValue == 1 && RsenseValue == 0 && CsenseValue == 1 && LsenseValue == 1)    //true: r
  {
    turn_R(0,r);
    delay(10);
  }
  else
  {
    stop();
    delay(10);
  }
}
  
void loop()
{
int val = 0;
  //readSensors();
  //printDebug();
  if(digitalRead(key_s6)==0)
  { 
    val = 1;
    delay(2000);
    while(val == 1){  
    
    program();}
  }
  else 
  {
    stop();
    delay(10);
  }
}
  
