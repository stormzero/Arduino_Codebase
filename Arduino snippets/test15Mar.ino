// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
// Simulate(Uno)

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

int a=5;
  for(int i=0;i<a;i++){
    for(int j=0;j<a;j++){
      if((i==0) || (i==a-1)){
     Serial.print("*");
      }else{
        if((j==0) || (j==a-1)){
       Serial.print("*");
     }else{
          Serial.print(" ");
        }
      }
    }
    Serial.println();
  }
}
  
