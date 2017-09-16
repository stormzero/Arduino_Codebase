// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// SerialIn(13) // blink digital pin 13 since there is a led attached
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Due Blink v0.90" );
  Serial.println(F("Ready - Enter 2 digit pin number?"));
}

// the loop routine runs over and over again forever:
void loop() {
  
  if (Serial.available()>1) {
    led = (Serial.read()-'0')*10;
    led += (Serial.read()-'0');
    pinMode(led, OUTPUT); 
    Serial.print("Blink led = ");
    Serial.println(led,DEC);
  }
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}


