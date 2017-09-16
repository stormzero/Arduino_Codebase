/*
 PWM Motor control skech, frequentie en dutycycle bestuurd.
 Frequentie is een vaste variabele in deze skech en dutycycle is instelbaar middels een potmeter via de analoge input. 
 Potmeter aansluiting, een zijde aan de ground, de ander zijde aan de +5V en de loper aan de analoge input A0.
 De libary staat een frequentie range toe tussen 1Hz - 2MHz met gebruik van de 16 bit timers en 31Hz - 2 MHz op de 8 bit timers. 
 Wanneer "SetPinFrequency()/SetPinFrequencySafe()" wordt uigevoerd, zal een bool als antwoord terug komen en is er een verificatie dat de daadwerkelijk frequentie is aangepast..

 Deze scech draat zowel op een Uno als Mega.
 */

#include <PWM.h>

  int sensorPin = A0;    // select de input pin voor de potentiometer
  int potmeter = 254;  // variable, tijdelijke variabele van de A0 input
  int motor = 9;                // de pin waar de motor aan zit
  int32_t frequency = 1055; //frequency (in Hz)
 // --------------- //
  int inp_wissel_01 = A1; // pin waar wissel 1 input aankomt
  int out_wissel_01L = 3; // wissel 1 output links
  int out_wissel_01R = 4; // wissel 1 output rechts
  int wissel_01 = 0;
 // --------------- //
 // int inp_wissel_02 = A2; // pin waar wissel 2 input aankomt
 // int out_wissel_02L = 6;  // wissel 2 output links
 // int out_wissel_02R = 7;  // wissel 2 output rechts
   // --------------- //
// int inp_sein_01 = A3;  // Sein 1 bediening 
// int out_sein_01R = 10;  // sein 1 rood.
// int out_sein_01G = 11;  // sein 1 groen
  // --------------- //
//  int inp_sein_02 = A4;  // sein 2 bediening.
//  int out_sein_02R = 12;  // sein 2 rood
//  int out_sein_02G = 13;  // sein 2 groen

void setup()
{
  // pinMode(inp_wissel_01, INPUT);  // init pin 2 als input
  pinMode(out_wissel_01L, OUTPUT); // init pin 3 als output
  pinMode(out_wissel_01R, OUTPUT); // init pin 4 als output
     
  //Initialisatie alle timers behalve  0, deze wordt gebruikt voor tijd besparende functies.
  InitTimersSafe(); 

  //Zet de ingestelde frequentie voor de gespecificeerde PWM output pin.
  bool success = SetPinFrequencySafe(motor, frequency);
  
  //Bool return, bij succesvolle frequentie aanpassing zet LED 13 aan. 
  if(success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);    
  }
 Serial.begin(9600);  //seriele communicatie naar PC

}

void loop()
{
    Serial.println(potmeter);    // print de waarde potmeter naar de PC
    potmeter = analogRead(sensorPin);    // Lees de waarde van de analoge input. 
    potmeter = potmeter / 4;     // Deel de 1024 analoge stappen door 4 om max 255 analoge stappen te bereiken. 
    // Deze functie gebruiken in plaats van analogWrite ON op de PWM poort.
    pwmWrite(motor, potmeter);      // Schrijf de (analoge waarde) dutycycle naar de PWM output.
///--------------------///
    wissel_01 = analogRead(inp_wissel_01);
    wissel_01 = wissel_01 / 4;
    Serial.println(wissel_01);    // print de waarde potmeter naar de PC
   if (wissel_01 < 245)
    {
    digitalWrite(3, HIGH);
//    delay(500);
//    digitalWrite(3, LOW);
    digitalWrite(4,LOW);
    }
    else
    {
   digitalWrite(3, LOW);
   digitalWrite(4, HIGH);
//    delay(500);
//    digitalWrite(4, LOW);
}
}
/////---------------////
// switch (getal)
//  {
//    case 3: ledbesturing();
//     break;
//    case 2: drukknop();;
//     break;
//  }

