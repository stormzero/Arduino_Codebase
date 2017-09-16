
boolean myFlag = HIGH;

#if defined(ARDUINO)
 int j= 23;
#endif

char multiChar[] = {"Hello World"};
char multiChar2[] = {"test"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("OUTPUT=");Serial.println(OUTPUT,HEX);
  Serial.print("INPUT=");Serial.println(INPUT,HEX);
  Serial.print("INPUT_PULLUP=");Serial.println(INPUT_PULLUP,HEX);
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
