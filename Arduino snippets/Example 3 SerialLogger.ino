//Simulate(Uno) link sketch to Arduino board here


void setup() {
// put your setup code here, to run once:
 Serial.begin(9600);
}

int i,j,x,y;
float f;

void loop() {
 i = 1;

 for (f=0.0; f<100.0; f+=0.01) {
  y=(int)sin(PI*f)*120;
  Serial.print(y);
  Serial.print(',');
 Serial.println(i++);
 }

//put your main code here, to run repeatedly:

  for (int i=0; i<100;i++) {
        Serial.println(i);
  }

  for (int i=50; i>-20;i--) {
      Serial.println(i);
  }
}



