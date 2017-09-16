

int b; /* Text */
/* Text */ long c; 
byte d; /* Te
xt */ char c;
xt */ bool b1; /* Te */
int y = 23 ;

char x = 1;
int y = 23 ;
long fd = 34;
String r ="1234";
#define dghs 3456 
// pinMode(13,OUTPUT) ; // this line should produce an error if uncommented

// BreakPoint(30)

void setup() {
 pinMode(13,OUTPUT) ;
 pinMode(12,INPUT) ; digitalWrite(12,HIGH) ; // this line should produce an error
 Serial.begin(9600) ;
}

void loop() {
 y = digitalRead(12) ;
 Serial.print(y) ;
 digitalWrite(13,y) ;
 if (y==HIGH) Serial.println("Hi") ;
 if (y==LOW)  Serial.println("Lo") ;
 delay(500) ;
}


