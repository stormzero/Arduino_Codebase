
// Saved by Simulator for Arduino V0.96
// Saved by Simulator for Arduino V0.96
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95B
// Saved by Simulator for Arduino V0.95B
// Saved by Simulator for Arduino V0.95
// Saved by Simulator for Arduino V0.94E
// Saved by Simulator for Arduino V0.94E
#define test 0

#ifdef test
 int x1=2;
#endif

#ifdef test1
 int x2=2;
#endif

#if (1)
  int x3=3;
#else
  int x4 = 4;
#endif

#if (test)
 int x5=5;
#elif (1)
 #if (TRUE)
  int x8a = 98;
 #else 
  int x6 = 6;
 #endif
#else
 int x7=7;
#endif

int y = 23 ;
long fd = 34;
String r ="1234";
#define dghs 3456
const int fred = 543;
const byte r1 = 45;
const unsigned static volatile byte x=123;
static int fy = -345;
char c;

#if (0)
 byte over = 511;
 unsigned int red = 131065;
 const unsigned int chk = -34000;
 byte test1 = -256;
 unsigned int test2 = -65534;
#else
 byte over = 111;
 unsigned int red = 13065;
 const unsigned int chk = 3000;
 byte test1 = 25;
 unsigned int test2 = 5534;
#endif

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = a0;  // Analog input pin that the potentiometer is attached to

// SerialIn(12345)

void setup() {
 int i = analogRead(analogInPin); 
   Serial.begin(19200);
   Serial.println(dghs);
   c = Serial.read();
   y = Serial.peek();
   Serial.flush();
   Serial.end();
   pinMode(12,INPUT) ;
   digitalWrite(12,y) ; // this line should not produce an error
}

void loop() {
    fred = 0;  // this line should produce an error
    r1 =10; // this line should produce an error
    over++;
    test1--;
    red += 10;
    test2 = test2 -4;

// i = 1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17+18+19+20+21; // test for recursive check


}
