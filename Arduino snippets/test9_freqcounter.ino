#include <FreqCounter.h>

unsigned long frq;
int cnt;
int pinLed =13;

void setup() {
  pinMode(12,INPUT);
  pinMode(pinLed,OUTPUT);
  Serial.begin(115200);                    // connect to the serial port
  Serial.println("Frequency Counter");
}

long int frq;
void loop() 
{

 FreqCounter::f_comp= 10;             // Set compensation to 12
 FreqCounter::start(100);            // Start counting with gatetime of 100ms
 while (FreqCounter::f_ready == 0);         // wait until counter ready
 frq=FreqCounter::f_freq;            // read result
 Serial.print(cnt++);                // print result
 Serial.print("  Freq:  ");                // print result
 Serial.println(frq);                // print result
 delay(20);
digitalWrite(pinLed,!digitalRead(12));
}
