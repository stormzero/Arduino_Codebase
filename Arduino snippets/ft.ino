int forcePin = 2; // select the input pin for the force sensor
// Saved by Simulator for Arduino V0.97.A.5
int val = 0; // variable to store the value coming in from the sensor
 unsigned long  tempsPrecedent = 0, tempsActuel = 0,tempsTotal = 0; // mes variables de temps
unsigned long centitot1 = 0;            // centieme to display
unsigned long secotot1 =0;              // seconds  to display
void setup() //run one time when the Arduino first powers up
{Serial.begin(9600); //starts serial communication, only used for debgugging
pinMode(forcePin, INPUT); 
}
void loop() //This next bit of code runs continuously
{
val = digitalRead(forcePin); // read the value from the sensor
if (val==LOW){ //if the value is maxed out or greater than 250
tempsTotal=tempsActuel - tempsPrecedent;
centitot1 = (tempsTotal%1000)/10 ;       //centieme to display
secotot1 = (tempsTotal/1000)%60 ;        // second to display
    Serial.print(secotot1);
    Serial.print(":");
     Serial.println(centitot1);
   tempsPrecedent = tempsActuel;
delay(100); 
}
else{
tempsActuel = millis();
}
