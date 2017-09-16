 // Simulate(Mega)
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2
// SerialIn(This is some new input data)
 
 
 unsigned long ulong;
 String inData = "123456";
 const float Power_15_expected = 4.1;
 int sensorValue = 10;
 float distanza,durata;
 byte i=5;
int canal = 177;
byte a1?0 = 123;


String stringOne = "This is line one"; //generates an error only on the Simulator 
 
 #define HSFGHJK 5
 
#define CHECK

 void setup() {

a1?0 = 99;


#ifdef CHECK
// Simulate(Mega)
Serial.begin(9600);// 9600 baud for the serial port 0
Serial1.begin(9600); // 9600 baud for the serial port 1
Serial2.begin(9600); // 9600 baud for the serial port 2
Serial3.begin(9600); // 9600 baud for the serial port 3
 Serial.println(A0,DEC);
 Serial.end(); 
 Serial1.end(); 
 Serial2.end(); 
 Serial3.end(); 
#endif


pinMode(3,INPUT);

// Simulate(Mage75)


 Serial.begin(9600);

float fV = 3.14;
    int output = int(fV); //'output' should be 3, actual 0

 Serial.println(output,DEC);
 Serial.println(A0,DEC);
 Serial.println('\a',HEX);
 Serial.println('\b',HEX);
 Serial.println('\e',HEX);
 Serial.println('\f',HEX);
 Serial.println('\n',HEX);
 Serial.println('\r',HEX);
 Serial.println('\t',HEX);
 Serial.println('\v',HEX);

 Serial.write(176|canal); Serial.write(65);
 
 
 if (i==5) {i=7;};;;
 for (i=0; i<8; i++) { pinMode(i,OUTPUT);};
 pinMode(60,OUTPUT);
 // pinMode(6,INPUT);
 
     float voltage = sensorValue * (5.0 / 1023.0);
     ulong = atof(inData);
 
  pinMode(HSFGHJK,INPUT);
  durata = 1.23;
 distanza = (0.034 * durata + 0.0001) / 2;
 }
 
 void loop() {
   // put your main code here, to run repeatedly:
 
  i = digitalRead(6);
  
 // for (int i=13; i<=53; i++) {
 //   pinMode(i,OUTPUT);}
 

 }
