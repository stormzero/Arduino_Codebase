// Simulate Uno
byte test[7];

float f=2.34;
float f = 1.2e4;
float f1 = 1.5e-5;


void setup() {
  // put your setup code here, to run once:
    f = (float)1;

}

void loop() {
  // put your main code here, to run repeatedly:

int V = 1;
float fV = (float)V;
    fV = 1.2 * 1.2;  // = 1.44
    fV = 1.44 / 1.2; // = 1.2
    fV = 1.44 + 1.2; // = 2.64
    fV = 1.44 - 1.2; // = 0.24

    fV = 1.2;
    fV *= 1.2;   // =1.44  
    fV /= 1.2;   // =1.2
    fV += 1.2;   // =2.4
    fV -= 1.44;  // =0.96

    if (fV>0.80) {
       f = 3.2;   // here
    }
 
    if (f!=3.1) {
      fV = 2.0; // here
    }

}
