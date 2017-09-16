// Simulate(Uno) link sketch to Arduino board here

#include <avr/io.h>

int i,j; // auto sets these variables to 0
float f;
long long1;
unsigned long ulong1;
byte sensin[2] = {0,1};
byte port = 0;

void     PrintStr(String s)
{
    Serial.println(s);
}


void setup() { // not fixed stuff

//pinMode(sensin [port], INPUT);
    Serial.begin(9600);
    PrintStr("String1");
    PrintStr("Test 2");
    f = 1e+3;
    f = 2E-5;
    long1 = 345l;
    ulong1 = 456ul;

//MCUCR1 = 1;
}



void loop() { // fixed stuff so check later

    DDRC 
    = 
   0xff;

    int i1 = 2; int i2=3;int i3
 = 4;


    while (i<7)
    {
        j+=2;
           i++;
    }

    for (i=0; i<3; i++) 
        j--;

    while (i++<7)
    {
        j++;
    }
}
