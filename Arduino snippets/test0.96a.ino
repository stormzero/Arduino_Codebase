// Simulate Uno
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96A

#include <math.h>

float average,f;

int a,b,c;
#define tDc 3

void setup() {
  // put your setup code here, to run once:
 
    Serial.begin(9600);
    Serial.println(1.23);
    f = 3.45;
    Serial.println(f);
    pinMode (tDc, INPUT);


    average = 0.0;
    b = 5;
    a = b*2 + 3;
    c = 8/4-1; 

    if (b==5) {a=3;}
    if (a==3) b=1;
    if (c==12) {a=25;}
}

void loop() {
  // put your main code here, to run repeatedly:
 average = average+((0.0742 * analogRead(A0)-37.88)/100);

retry: //Goto loop
    int readtDc = digitalRead(tDc);

    if (readtDc == LOW) { 
        Serial.println("tDc = LOW");
    }
    else{
        Serial.println("tDc = HIGH");
        goto retry;
    }

}




