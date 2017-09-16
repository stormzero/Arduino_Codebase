// Simulate(Uno) link sketch to Arduino board here

void setup() {

	float f = (3.45/2.3);
      Serial.begin(9600);
    int x = 100 / 20 / 5;
      Serial.println(x);

  // put your setup code here, to run once:
long arcMillis;
long windowMillis;

    arcMillis = 1000;
    windowMillis = 10000;

// these lines always produce 0 in workCycle
 float workCycle = arcMillis / windowMillis;
 float workCycle = (float)arcMillis / (float)windowMillis;

// but this works...
float x = arcMillis;
float y = windowMillis;
float workCycle = x / y;
}

void loop() {
  // put your main code here, to run repeatedly:

}
