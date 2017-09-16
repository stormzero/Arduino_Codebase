/*
  Software serial multple serial test
 
 
 */

#include <SoftwareSerial.h>


  #define IP_Flow_Pulse 10
  #define LED 13
 
unsigned char message [250];
unsigned char count;
unsigned char data;
unsigned long Pulse_Period;
unsigned long Flow_Rate;
unsigned int Flow_Rate1;
unsigned int Flow_Rate2;
unsigned int Flow_Rate3;
unsigned int Flow_Rate4;

volatile int Flow_Pulse = LOW;
volatile long Pulse_Time;
volatile long Last_Pulse_Time;

 int flowPin = A0;  // 4-20ma from flow meter


SoftwareSerial GPSserial(11,12); // Rx Tx

void setup()  
{
  
 pinMode(13, OUTPUT);
 pinMode(10, OUTPUT); // digital in for flow pulse

 
  
 
 
 // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial2.begin(9600); // GSM Model
  Serial3.begin(9600); // Bluetooth
  GPSserial.begin(4800);
  Serial.println("Serials Initialised");
  
  analogReference (DEFAULT);
   
  
  }


void loop() // run over and over
{

//
//  Pulse_Period = Pulse_Time - Last_Pulse_Time;
 // Pulse_Period = (Pulse_Period * 1000) / 800; // correction... needs sorting out... !!!!
  
// Pulses are 1 every litre  1000 litres in a cu tr
// pulse period is in milliseconds
// 1 hour is 1000 x 60 x 60 millisecs == 360,000



//   Flow_Pulse = digitalRead(10);
 //  digitalWrite (LED, Flow_Pulse);
// if (Flow_Pulse) digitalWrite (LED, LOW);
 //    else  digitalWrite (LED, HIGH);
  
  
     
       Flow_Rate4 = Flow_Rate3;
       Flow_Rate3 = Flow_Rate2;
       Flow_Rate2 = Flow_Rate1;
       Flow_Rate1 = Flow_Rate;
      // Flow_Rate = 360000 / Pulse_Period;
      
      Flow_Rate = analogRead(flowPin);
      
      
     
       Flow_Rate = (Flow_Rate4 + Flow_Rate3 + Flow_Rate2 + Flow_Rate1 + Flow_Rate)/5;
  
  if (GPSserial.available())
  {
    
  data = GPSserial.read();
//  if (message[5] == 71) Serial2.write(data);
  
//  Serial.write(count);
//  Serial.write(10);
    
  if (data == 36) count = 1; // detect start of message
  
  if (count)
    {
      message[count] = data; // append data to message string 
      count++;               // increment pointer
    }
    
    
    if ((data == 10) && (message[5] == 77))     // on each message terminator print message to serial port if 5th character of header M
    {                                           // capturing GPRMC
     
     // flow pulse generator
   //  digitalWrite (10, HIGH);
     
      int temp = 0;
      while (message[temp] != 10) 
        {
          Serial.write(message[temp]);  // write message to PC USB
          Serial3.write(message[temp]); // write message to bluetooth
        
          temp++;
        }
      
   
      
       
       Serial.print("SILfl,");
       Serial.print(Flow_Rate);
       Serial.print(",Z");
       Serial.write(10);  // lf/cr to PC USB
       
       Serial3.print("SILfl,");
       Serial3.print(Flow_Rate);
       Serial3.print(",Z");
       Serial3.write(10);  // lf/cr to PC USB
    }  

    if (data == 10) count = 0; // detect end of message and reset data array pointer
     
      // flow pulse generator
      digitalWrite (10, LOW);
  }  
}



