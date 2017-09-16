// Simulate(Uno)

#include <time.h>

const char* s_wkdy[] = {"?","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
long time;


//#define  STATEA     1
#define  STATEA   HIGH 

void setup() {
  // put your setup code here, to run once:


 pinMode(1,OUTPUT);
 digitalWrite(1,STATEA);
 Serial.begin(9600);

 setTime(1,2,3,4,10,2013);

 time = now();
 time += 10;
 setTime(time);


}

void loop() {
  // put your main code here, to run repeatedly:


 Serial.print(hour(),DEC);
 Serial.print(":");
 Serial.print(minute(),DEC);
 Serial.print(":");
 Serial.print(second(),DEC);
 Serial.print(" ");
 Serial.print(s_wkdy[weekday()]);
 Serial.print(" ");
 Serial.print(day(),DEC);
 Serial.print("-");
 Serial.print(month(),DEC);
 Serial.print("-");
 Serial.print(year(),DEC);
 Serial.print(" Unix seconds=");
 Serial.print(now(),DEC);
 Serial.println("");
 delay(600);
}
