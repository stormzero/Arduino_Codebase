// Saved by Simulator for Arduino V0.98D refer to virtronics.com.au
// Saved by Simulator for Arduino V0.98D refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98D refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98D refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
/* +---------------+
   | SKETCH HEADER |
   +---------------+ */
/* Sketched by: A.G. Student
   Sketch name: TrafLite2.ino
   Revision:# 1.0        Date:  / /     */
 
/* +--------------------+
   | SKETCH DESCRIPTION |
   +--------------------+ */
/* Interactive Traffic Lights */
 
/* +-------------------+
   | SKETCH PROTOTYPES |
   +-------------------+ */
void changeLights(void);
 
/* +------------------+
   | SKETCH CONSTANTS |
   +------------------+ */
   const int roadRed = 12; // assign the road lights
   const int roadAmb = 11;
   const int roadGrn = 10;
   const int pedRed  = 9;  // assign the pedestrian lights
   const int pedGrn  = 8;
   const int pedBut  = 2;  // pedestrian button pin
 
/* +------------------+
   | SKETCH VARIABLES |
   +------------------+ */
   int xTime = 5000; // 5 sec time allowed to cross
   unsigned long cTime; // time since button pressed
 
/* +--------------+
   | SKETCH SETUP |
   +--------------+ */
void setup()  // this function is executed once.
{
   pinMode(roadRed, OUTPUT);
   pinMode(roadAmb, OUTPUT);
   pinMode(roadGrn, OUTPUT);
   pinMode(pedRed, OUTPUT);
   pinMode(pedGrn, OUTPUT);
   pinMode(pedBut, INPUT);     // button on pin 2
// turns ON green light and turns ON red pedestrian light
   digitalWrite(roadGrn, HIGH); // Green lite is ON
   digitalWrite(pedRed, HIGH); // Ped red light is on
}
 
/* +-------------+
   | SKETCH LOOP |
   +-------------+ */
void loop()   // the loop routine runs over and over again forever
{            
   int state = digitalRead(pedBut);
/* check if button is pressed and if is over
   5 seconds since last button press */
//   if (state == HIGH && (millis() - cTime) > 5000)
// for the Arduino Simulator change the 5000 as follows
 if (state == HIGH && (millis() - cTime) > 0.5)
   {
// Call the function to change the lights
   changeLights();
   }
}
 
/* +------------------+
   | SKETCH FUNCTIONS |
   +------------------+ */

void changeLights()
{
   digitalWrite(roadGrn, LOW);  // green OFF
   digitalWrite(roadAmb, HIGH); // amber ON
   delay(2000);                 // wait 2 seconds
   digitalWrite(roadAmb, LOW);  // amber OFF
   digitalWrite(roadRed, HIGH); // red ON
   delay(1000);                 // wait 1 second till  safe
   digitalWrite(pedRed, LOW);   // ped red off
   digitalWrite(pedGrn, HIGH);  // ped green on
   delay(xTime);                // wait for preset time period
   for (int x=0; x<10; x++)     // flash the ped green lite
   {
      digitalWrite(pedGrn, HIGH);
      delay(250);
      digitalWrite(pedGrn, LOW);
      delay(250);
   }
 
   digitalWrite(pedRed, HIGH);  // turn ped red on
   delay(500);
   digitalWrite(roadAmb, HIGH); // yellow on
   digitalWrite(roadRed, LOW);  // red off
   delay(1000);
   digitalWrite(roadGrn, HIGH);
   digitalWrite(roadAmb, LOW);  // yellow off
// record the time since last change of lights
   cTime = millis();
// then return to the main program loop
}
 
