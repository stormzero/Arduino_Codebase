// Blink : Turns on an LED on for one second, then off for one second, repeatedly.
// Saved by Simulator for Arduino V0.98


 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
char s[20];

// SerialIn(+-+-+++---+-)

// variable timing
long dur = 1000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
  Serial.begin(9600); 
  Serial.println("+ pour diminuer la frequence");
  Serial.println("- pour augmenter la frequence");
  
  ltoa(dur,s,10);
}

// the loop routine runs over and over again forever:
void loop() {

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("Allumee pour ");Serial.println(s);
  delay(dur);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.print("Eteinte pour ");;Serial.println(s);
  delay(dur);               // wait for a second
  
  // check for dur variation request from serial
  if(Serial.available())
  { char c = Serial.read();
    switch(c)
    { case '+':
         if (dur < 5000)
         {dur*=2;}
         else
         {dur+=1000;}
         ltoa(dur,s,10);
         Serial.print("Augmente a ");Serial.println(s);
         break;
      case '-':
         if (dur >= 5000)
         {dur-=1000;}
         else
         {dur/=2;}
         if (dur==0) {dur=1;}
         ltoa(dur,s,10);
         Serial.print("Diminue a ");Serial.println(s);
         break;
    }
  }   
  
}
